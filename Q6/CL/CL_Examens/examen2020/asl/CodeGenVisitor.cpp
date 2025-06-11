//////////////////////////////////////////////////////////////////////
//
//    CodeGenVisitor - Walk the parser tree to do
//                     the generation of code
//
//    Copyright (C) 2020-2030  Universitat Politecnica de Catalunya
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU General Public License
//    as published by the Free Software Foundation; either version 3
//    of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public
//    License along with this library; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//
//    contact: José Miguel Rivero (rivero@cs.upc.edu)
//             Computer Science Department
//             Universitat Politecnica de Catalunya
//             despatx Omega.110 - Campus Nord UPC
//             08034 Barcelona.  SPAIN
//
//////////////////////////////////////////////////////////////////////

#include "CodeGenVisitor.h"
#include "antlr4-runtime.h"

#include "../common/TypesMgr.h"
#include "../common/SymTable.h"
#include "../common/TreeDecoration.h"
#include "../common/code.h"

#include <string>
#include <cstddef>    // std::size_t

// uncomment the following line to enable debugging messages with DEBUG*
//#define DEBUG_BUILD
#include "../common/debug.h"

// using namespace std;


// Constructor
CodeGenVisitor::CodeGenVisitor(TypesMgr       & Types,
                               SymTable       & Symbols,
                               TreeDecoration & Decorations) :
  Types{Types},
  Symbols{Symbols},
  Decorations{Decorations} {
}

// Accessor/Mutator to the attribute currFunctionType
TypesMgr::TypeId CodeGenVisitor::getCurrentFunctionTy() const {
  return currFunctionType;
}

void CodeGenVisitor::setCurrentFunctionTy(TypesMgr::TypeId type) {
  currFunctionType = type;
}

// Methods to visit each kind of node:
//
std::any CodeGenVisitor::visitProgram(AslParser::ProgramContext *ctx) {
  DEBUG_ENTER();
  code my_code;
  SymTable::ScopeId sc = getScopeDecor(ctx);
  Symbols.pushThisScope(sc);
  for (auto ctxFunc : ctx->function()) {
    subroutine subr = std::any_cast<subroutine>(visit(ctxFunc));
    my_code.add_subroutine(subr);
  }
  Symbols.popScope();
  DEBUG_EXIT();
  return my_code;
}

// FUNC ID '(' parameters? ')' (':' basic_type)? declarations statements ENDFUNC
std::any CodeGenVisitor::visitFunction(AslParser::FunctionContext *ctx) {
  DEBUG_ENTER();
  SymTable::ScopeId sc = getScopeDecor(ctx);
  Symbols.pushThisScope(sc);
  subroutine subr(ctx->ID()->getText());
  codeCounters.reset();

  // si té resultat/return
  if(ctx->basic_type()){ 
    TypesMgr::TypeId   t = getTypeDecor(ctx->basic_type());
    // afegim un nou parametre per guardar el resultat
    subr.add_param("_result", Types.to_string(t), false); // false: because is not an array
  }

  //std::cout << "Pre parameters -- " << std::endl;

  // si té parametres
  if (ctx->parameters()) {
    // recorrem tots els paràmetres
    for (auto & param : ctx->parameters()->parameter()) { 
      TypesMgr::TypeId   t1 = getTypeDecor(param->type());  // tipus del param
      bool isArray = Types.isArrayTy(t1); // comprovem si es array
      if (isArray) {
        TypesMgr::TypeId tElem = Types.getArrayElemType(t1); 
        // si es un array: afegim el parametre amb el tipus dels elements de l'array 
        subr.add_param(param->ID()->getText(), Types.to_string(tElem), true); // true: it is an array
      }else{
        // afegim el parametre amb el seu tipus
        subr.add_param(param->ID()->getText(), Types.to_string(t1), false);
      }
    }
  }

  std::vector<var> && lvars = std::any_cast<std::vector<var>>(visit(ctx->declarations()));
  for (auto & onevar : lvars) {
    // afegim les variables de la funció
    subr.add_var(onevar);
  }
  // visitem les statements entre les quals estarà el return (en cas de tenir)
  instructionList && code = std::any_cast<instructionList>(visit(ctx->statements()));

  // Per si el programador no fica return, en fiquem un perque ha de tenir-ne
  code = code || instruction(instruction::RETURN());

  subr.set_instructions(code);
  Symbols.popScope();
  DEBUG_EXIT();
  return subr;
}

// ident '(' (expr (',' expr)*)? ')'    # functionCall -> es una expr
std::any CodeGenVisitor::visitFunctionCall(AslParser::FunctionCallContext *ctx){
  DEBUG_ENTER();
  instructionList codeFuncCall;

  TypesMgr::TypeId tFunc = getTypeDecor(ctx->ident());
  std::vector<TypesMgr::TypeId> paramTypes = Types.getFuncParamsTypes(tFunc);

  // MIRAR ELS PARAMETRES + CODI DE CALCULAR-LOS (code)
  // PUSH buit per la varaible _return 
  codeFuncCall = instruction::PUSH(); // funciona buit perque te un valor per defecte
  // recorrem els parametres (expr())
  for (uint i = 0; i < ctx->expr().size(); ++i) {
    CodeAttribs     && codAtsE = std::any_cast<CodeAttribs>(visit(ctx->expr(i))); // la variable agafa aquella zona de memoria
    std::string           addr = codAtsE.addr;
    instructionList &     code = codAtsE.code;

    // COMPROVAR ELS TIPUS
    TypesMgr::TypeId t = getTypeDecor(ctx->expr(i));
    // apliquem coercio si el tipus del param es un integer i ens han passat un float
    if (Types.isFloatTy(paramTypes[i]) and Types.isIntegerTy(t)) {
      std::string temp1 = "%"+codeCounters.newTEMP();
      code = code || instruction::FLOAT(temp1, addr);
      code = code || instruction::PUSH(temp1);
      // si el param es un array i es variable LOCAL:
    } else if (Types.isArrayTy(t) and not Symbols.isParameterClass(ctx -> expr(i) -> getText())) {  // Quan ens passen un array per paràmetre per referencia
      std::string temp1 = "%"+codeCounters.newTEMP();
      code = code || instruction::ALOAD(temp1, addr); // aload per obtenir l'adreça de la variable
      code = code || instruction::PUSH(temp1);
    } else {
      // guardem a la pila el parametre 
      code = code || instruction::PUSH(addr);
    }

    // Afegim el codi del PUSH DELS PARAMS
    codeFuncCall = codeFuncCall || code;
  }
  // CALL DE LA FUNC
  codeFuncCall = codeFuncCall || instruction::CALL(ctx->ident()->getText());

  // FER POP DELS PARAMS -> en ordre invers a com s'han ficat
  for (uint i = 0; i < ctx->expr().size(); ++i) {
    // POP
    // pop buits perque no volem guardar res dels params (recuperar-los)
    codeFuncCall = codeFuncCall || instruction::POP();   
  }

  std::string temp = "%"+codeCounters.newTEMP();
  // POP extra per guardar el resultat -> _return a un temporal
  codeFuncCall = codeFuncCall || instruction::POP(temp); // cal ficar-li el temp on quedara el resultat

  // return TEMP resultat de la crida
  CodeAttribs codAts(temp, "", codeFuncCall);
  DEBUG_EXIT();
  return codAts;
}

// (variable_decl)*
std::any CodeGenVisitor::visitDeclarations(AslParser::DeclarationsContext *ctx) {
  DEBUG_ENTER();
  std::vector<var> lvars;
  // recorrem totes les declaracions de variables
  for (auto & varDeclCtx : ctx->variable_decl()) {
    // canviem per tenir diverses variables a una mateixa linia
    std::vector<var> vars = std::any_cast<std::vector<var>>(visit(varDeclCtx)); // ara al visitar varDecl obtenim linia de diverses variables (abans una sola var per linia)
    for (auto & onevar : vars){
      lvars.push_back(onevar);  // afegim cada variable al vector
    }
  }
  DEBUG_EXIT();
  return lvars;
}

// VAR ID (',' ID)*  ':' type
std::any CodeGenVisitor::visitVariable_decl(AslParser::Variable_declContext *ctx) {
  DEBUG_ENTER();
  // obtenir el tipus de la var
  TypesMgr::TypeId   t1 = getTypeDecor(ctx->type());
  std::size_t      size = Types.getSizeOfType(t1);

  // obtenir llista de variables declarades a la mateixa linia
  std::vector<var> vars;
  // recorrem totes les var de la mateixa linia (tantes com IDs hi hagi)
  for (auto id : ctx->ID()){
    // afegim la var al vector
    if (Types.isArrayTy(t1)){ // en cas que sigui un array, el tipus és el tipus dels elems de l'array i la mida és el numero d'elems de l'array
      vars.push_back(var{id->getText(), Types.to_string(Types.getArrayElemType(t1)), size});
    }else
      vars.push_back(var{id->getText(), Types.to_string(t1), size});
  }
  DEBUG_EXIT();
  return vars;
}

std::any CodeGenVisitor::visitStatements(AslParser::StatementsContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  for (auto stCtx : ctx->statement()) {
    instructionList && codeS =  std::any_cast<instructionList>(visit(stCtx));
    code = code || codeS;
  }
  DEBUG_EXIT();
  return code;
}

// left_expr ASSIGN expr ';'           # assignStmt
std::any CodeGenVisitor::visitAssignStmt(AslParser::AssignStmtContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  CodeAttribs     && codAtsE1 =  std::any_cast<CodeAttribs>(visit(ctx->left_expr()));
  std::string           addr1 = codAtsE1.addr;
  std::string           offs1 = codAtsE1.offs;
  instructionList &     code1 = codAtsE1.code;
  
  CodeAttribs     && codAtsE2 = std::any_cast<CodeAttribs>(visit(ctx->expr()));
  std::string           addr2 = codAtsE2.addr;
  //std::string           offs2 = codAtsE2.offs; // NO NECESARIO SEGÚN EL EJEMPLO
  instructionList &     code2 = codAtsE2.code;
  
  code = code1 || code2;

  TypesMgr::TypeId t1 = getTypeDecor(ctx->left_expr());
  TypesMgr::TypeId t2 = getTypeDecor(ctx->expr());
  
  /* si left_expr es float y expr int-> expr paso a float*/
  if (Types.isFloatTy(t1) && Types.isIntegerTy(t2)) {
    std::string temp = "%" + codeCounters.newTEMP();
    code = code || instruction::FLOAT(temp, addr2);
    addr2 = temp;
  }
  
  // COPIA DE ARRAYS a = b, los dos tienen type Array i offset = ""(en teoría).
  if (Types.isArrayTy(t1) && Types.isArrayTy(t2)) {
    std::string temp1 = "%" + codeCounters.newTEMP();
    std::string temp2 = "%" + codeCounters.newTEMP();

    if (Symbols.isParameterClass(ctx->left_expr()->getText())) {
      code = code || instruction::LOAD(temp1, addr1);
      addr1 = temp1;
    }
    if (Symbols.isParameterClass(ctx->expr()->getText())) {
      code = code || instruction::LOAD(temp2, addr2);
      addr2 = temp2;
    }

    std::string ivar = "%"+codeCounters.newTEMP(); // comptador
    std::string limit = "%"+codeCounters.newTEMP(); // mida array
    std::string cond = "%"+codeCounters.newTEMP(); // condició
    std::string tempVal = "%"+codeCounters.newTEMP(); // valor temporal
    std::string inc = "%"+codeCounters.newTEMP(); // increment
    
    // Etiquetes del bucle
    std::string labelLoop = "arrayCopyWhile" + codeCounters.newLabelWHILE();
    std::string labelEnd = "arrayCopyend" + codeCounters.newLabelWHILE();
    
    // Inicialitzar bucle
    code = code || instruction::ILOAD(limit, std::to_string(Types.getArraySize(t1))); // Límit del bucle: mida de l'array
    code = code || instruction::ILOAD(ivar, "0"); // i = 0 
    code = code || instruction::ILOAD(inc, "1");  // increment es 1
    
    // Bucle que recorre l'array
    code = code || instruction::LABEL(labelLoop);               // while (i < limit) {
    code = code || instruction::LT(cond, ivar, limit);          // cond = i < limit
    code = code || instruction::FJUMP(cond, labelEnd);
    code = code || instruction::LOADX(tempVal, addr2, ivar);    //value = b[i]
    code = code || instruction::XLOAD(addr1, ivar, tempVal);    // a[i] = value
    code = code || instruction::ADD(ivar, ivar, inc);           // i++
    code = code || instruction::UJUMP(labelLoop);
    code = code || instruction::LABEL(labelEnd);
  }
  else {
    // Asignación normal
    if (offs1 != "") {
      code = code || instruction::XLOAD(addr1, offs1, addr2);
    }
    else code = code || instruction::LOAD(addr1, addr2);
  }

  DEBUG_EXIT();
  return code;
}


// IF expr THEN statements (ELSE statements)? ENDIF  # ifElseStmt
std::any CodeGenVisitor::visitIfElseStmt(AslParser::IfElseStmtContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  CodeAttribs     && codAtsE = std::any_cast<CodeAttribs>(visit(ctx->expr()));
  std::string          addr1 = codAtsE.addr;
  instructionList &    code1 = codAtsE.code;

  instructionList &&   codeSt0 = std::any_cast<instructionList>(visit(ctx->statements(0)));
  std::string label = codeCounters.newLabelIF();  // label IF
  std::string labelEndIf = "endif"+label; // label ENDIF

  // si té un ELSE, tindrà dos grups de statements
  if (ctx->statements(1)){
    instructionList &&   codeSt1 = std::any_cast<instructionList>(visit(ctx->statements(1)));
    std::string labelElse = "else"+label; // label ELSE
    code = code1 || instruction::FJUMP(addr1, labelElse) ||   // si no es compleix l'expr saltar a ELSE
           codeSt0 || instruction::UJUMP(labelEndIf) ||  // saltar a endIf si s'ha executat el then per evitar executar el else
           instruction::LABEL(labelElse) || // afegir label ELSE
           codeSt1 || instruction::LABEL(labelEndIf);  // afegir label ENDIF
  }else{  // si no té else
    code = code1 || instruction::FJUMP(addr1, labelEndIf) ||  // saltar a endif quan acabem d'executar els statements
           codeSt0 || instruction::LABEL(labelEndIf); // afegir label ENDIF
  }

  DEBUG_EXIT();
  return code;
}

// RETURN (expr)? ';'
std::any CodeGenVisitor::visitReturnStmt(AslParser::ReturnStmtContext *ctx){
  DEBUG_ENTER();
  instructionList code, codeR;
  if (ctx->expr()){
    CodeAttribs     && codAt = std::any_cast<CodeAttribs>(visit(ctx->expr()));
    std::string          addr1 = codAt.addr;
    instructionList  &   code1 = codAt.code;


    //instructionList && codeR;
    std::string addr = "_result";
    instructionList && codeR = instruction::LOAD(addr, addr1);
    code = code1 || codeR;
  }
  code = code || instruction(instruction::RETURN());
  DEBUG_EXIT();
  return code;
}

// WHILE expr DO statements ENDWHILE     # whileStmt
std::any CodeGenVisitor::visitWhileStmt(AslParser::WhileStmtContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  CodeAttribs     && codAtsE = std::any_cast<CodeAttribs>(visit(ctx->expr()));
  std::string          addr1 = codAtsE.addr;
  instructionList &    code1 = codAtsE.code;
  instructionList &&   code2 = std::any_cast<instructionList>(visit(ctx->statements()));
  std::string label = codeCounters.newLabelWHILE();
  std::string labelStartWhile = "while" + label;
  std::string labelEndWhile = "endwhile"+ label;
  code = instruction::LABEL(labelStartWhile) || // etiqueta while a l'inici per tal de després d'executar el do poguem tornar a reavaluar l'expr
         code1 || instruction::FJUMP(addr1, labelEndWhile) || // si no és certa saltem al final
         code2 || instruction::UJUMP(labelStartWhile) ||  // si és certa executem els statements i saltem a l'inici altre cop
         instruction::LABEL(labelEndWhile); // tancament while
  DEBUG_EXIT();
  return code;
}

// ident '(' (expr (',' expr)*)? ')' ';'  # procCall (quan fas la trucada a una funcio/proc sense guardar el seu resultat (com statement))
std::any CodeGenVisitor::visitProcCall(AslParser::ProcCallContext *ctx) {
  DEBUG_ENTER();
  instructionList codeProcCall;

  TypesMgr::TypeId tFunc = getTypeDecor(ctx->ident());
  std::vector<TypesMgr::TypeId> paramTypes = Types.getFuncParamsTypes(tFunc);

  // En cas que no sigui void cal fer un push i pop extra per retornar la solució
  // PUSH per la varaible _return (en cas de ser funció, no void)
  if (not Types.isVoidFunction(tFunc)) codeProcCall = codeProcCall || instruction::PUSH();

  // MIRAR ELS PARAMETRES + CODI DE CALCULAR-LOS (code)
  // cada param un expr()
  for (uint i = 0; i < ctx->expr().size(); ++i) {
    CodeAttribs     && codAtsE = std::any_cast<CodeAttribs>(visit(ctx->expr(i))); // la variable agafa aquella zona de memoria
    std::string           addr = codAtsE.addr;    // addr d'una expr té el seu valor (en cas de ser un ident doncs tens la variable p.ex. 'a')
    instructionList &     code = codAtsE.code;    // code d'una expr té el codi del que ha calgut per avaluar-la

    // COMPROVAR ELS TIPUS
    // obtenir el tipus del parametre
    TypesMgr::TypeId t = getTypeDecor(ctx->expr(i));
    // apliquem coercio si el tipus del param es un integer i ens han passat un float
    if (Types.isFloatTy(paramTypes[i]) and Types.isIntegerTy(t)) {
      std::string temp1 = "%"+codeCounters.newTEMP();
      code = code || instruction::FLOAT(temp1, addr); // casting a float del valor (addr)
      code = code || instruction::PUSH(temp1);  // push del param (que se li ha fet casting) -> el guardem a la pila
      // si el param es un array i es variable LOCAL:
    } else if (Types.isArrayTy(t) and not Symbols.isParameterClass(ctx -> expr(i) -> getText())) {
          std::string temp1 = "%"+codeCounters.newTEMP();
          // com es una variable local, del que cal fer push no es del seu contingut sino de la seva adreça -> quan es una variable local el contigut d'aquesta ja son els elems de l'array 
          // a la pila volem: &array (adreça de l'array per tant, aload)
          code = code || instruction::ALOAD(temp1, addr);
          code = code || instruction::PUSH(temp1);
    } else {
      // guardem a la pila el parametre, en cas de ser un array i no ser local com el contigut és l'adreça el push es fa d'allò correcte
      code = code || instruction::PUSH(addr);
    }

    // Afegim el code del PUSH DELS PARAMS
    codeProcCall = codeProcCall || code;
  }
  // CALL DE LA FUNC (trucada a la funcio)
  codeProcCall = codeProcCall || instruction::CALL(ctx->ident()->getText());

  // FER POP DELS PARAMS -> en ordre invers a com s'han ficat
  // Recuperem els params, no ens interessa guardar-nos-los
  for (uint i = 0; i < ctx->expr().size(); ++i) {
    // POP
    codeProcCall = codeProcCall || instruction::POP();   // pop buits perque no volem res dels params per guardar-lo
  }

  // En cas que sigui una funció, fem un pop extra (també buit perque en aquest cas no es vol guardar el resultat)
  if (not Types.isVoidFunction(tFunc)) codeProcCall = codeProcCall || instruction::POP();

  DEBUG_EXIT();
  return codeProcCall;
  
}

// READ left_expr ';'                  # readStmt
std::any CodeGenVisitor::visitReadStmt(AslParser::ReadStmtContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs     && codAtsE = std::any_cast<CodeAttribs>(visit(ctx->left_expr()));
  std::string          addr1 = codAtsE.addr;
  std::string          offs1 = codAtsE.offs;
  instructionList &    code1 = codAtsE.code;
  instructionList &     code = code1;
  TypesMgr::TypeId tid1 = getTypeDecor(ctx->left_expr());

  // no hi ha un readX cal fer-ho manualment, left_expr es l'adreça on voldrem guardar allo que llegim
  // llavors, read s'encarrega d'agafar de l'input allo i guardar-ho a on li passes per param
  // en el cas d'arrays no li pots passar al read, sino ho guardes a un temporal i després fas xload del que té el read a l'array (unica forma de poder guardar un valor dins d'un array)

  std::string temp1 = addr1;
  if (offs1 != ""){ // si allà a on ho has de guardar és un array 
    temp1 = "%" + codeCounters.newTEMP();
  }
  if (Types.isIntegerTy(tid1) or Types.isBooleanTy(tid1)){
    code = code || instruction::READI(temp1); // readi es pot utilitzar per guardar allò que ens han passat a una left-expr que sigui int o bool
  }else if (Types.isCharacterTy(tid1)){
    code = code || instruction::READC(temp1);  // readc es pot utilitzar per guardar allò que ens han passat a una left-expr que sigui char
  }else if  (Types.isFloatTy(tid1)){
    code = code || instruction::READF(temp1);  // readf es pot utilitzar per guardar allò que ens han passat a una left-expr que sigui float
  }
  if (offs1 != ""){ // en cas que sigui un array
    code = code || instruction::XLOAD(addr1, offs1, temp1);   // addr1[offs1] = temp1(resultat read)
  }

  DEBUG_EXIT();
  return code;
}

// WRITE expr ';'                      # writeExpr
std::any CodeGenVisitor::visitWriteExpr(AslParser::WriteExprContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs     && codAt1 = std::any_cast<CodeAttribs>(visit(ctx->expr()));
  std::string         addr1 = codAt1.addr;
  // std::string         offs1 = codAt1.offs;
  instructionList &   code1 = codAt1.code;
  instructionList &    code = code1;

  TypesMgr::TypeId tid1 = getTypeDecor(ctx->expr());  // comprovem el tipus d'allo que volem escriure per utilitzar un write o altre
  if (Types.isIntegerTy(tid1) or Types.isBooleanTy(tid1)){
    code = code || instruction::WRITEI(addr1);
  }else if (Types.isCharacterTy(tid1)){
    code = code || instruction::WRITEC(addr1);
  }else if  (Types.isFloatTy(tid1)){
    code = code || instruction::WRITEF(addr1);
  } 
  DEBUG_EXIT();
  return code;
}

// WRITE STRING ';'                    # writeString
std::any CodeGenVisitor::visitWriteString(AslParser::WriteStringContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  std::string s = ctx->STRING()->getText();
  code = code || instruction::WRITES(s);
  DEBUG_EXIT();
  return code;
}

// left_expr: ident | ident '[' expr ']'
std::any CodeGenVisitor::visitLeft_expr(AslParser::Left_exprContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs     && codAts = std::any_cast<CodeAttribs>(visit(ctx->ident()));
  if(ctx->expr()){ // Si es tracta d'un array

    std::string  addr1 = codAts.addr;   // Adreça de l'ident
    instructionList & code1 = codAts.code;

    CodeAttribs && codAt2 = std::any_cast<CodeAttribs>(visit(ctx->expr()));
    instructionList & code2 = codAt2.code;
    std::string     addr2 = codAt2.addr;  // Es l'offset (valor de l'expr)

    instructionList  code = code1 || code2;

    std::string temp2 = "%" + codeCounters.newTEMP();
    if (Symbols.isParameterClass(ctx->ident()->getText())){
      // en cas que sigui un parametre (per tant, no es variable local) 
      // cal obtenir el contingut del parametre (conte l'adreça base de l'array) perque el param apunta a la variable/array
      code = code || instruction::LOAD(temp2, addr1); 
    } else{
      // en cas que no sigui un param -> varible local
      // cal fer load de l'adreça de la variable per tenir l'adreça base (no del seu contigut, que es el que passaria amb un load normal)
      code = code || instruction::ALOAD(temp2, addr1); 
    }
    codAts = CodeAttribs(temp2, addr2, code); // aqui directament l'adreça de la variable és l'array (adreça base)
  }else{
    codAts = CodeAttribs(codAts.addr, "", codAts.code); // si no es un array passem l'areça de l'ident
  }
  DEBUG_EXIT();
  return codAts;
}

std::any CodeGenVisitor::visitSumExpr(AslParser::SumExprContext *ctx) {
  DEBUG_ENTER();
  instructionList code;


  TypesMgr::TypeId resultType = getTypeDecor(ctx);
  bool real = Types.isFloatTy(resultType);
  
  std::string result = "%"+codeCounters.newTEMP();
  
  if (real) 
    code = instruction::FLOAD(result, "0.0");
   else 
    code = instruction::ILOAD(result, "0");
  

  if (ctx->expr().size() > 0){
    for (auto expr : ctx->expr()){
      CodeAttribs     && codAt1 = std::any_cast<CodeAttribs>(visit(expr));
      std::string         addr1 = codAt1.addr;  // valor de l'expr
      instructionList &   code1 = codAt1.code;
      code = code || code1;
      TypesMgr::TypeId exprType = getTypeDecor(expr);

      std::string addr = addr1;
      if (real and Types.isIntegerTy(exprType)) {
        std::string temp = "%"+codeCounters.newTEMP();
        code = code || instruction::FLOAT(temp, addr1);
        addr = temp;
      }
      
      if (real) 
        code = code || instruction::FADD(result, result, addr);
      else 
        code = code || instruction::ADD(result, result, addr);
      
    }
  }
  CodeAttribs codAts(result, "", code);

  DEBUG_EXIT();
  return codAts;
}


std::any CodeGenVisitor::visitFilterExpr(AslParser::FilterExprContext *ctx) {
  DEBUG_ENTER();
  instructionList code;

  CodeAttribs     && codAtsE1 =  std::any_cast<CodeAttribs>(visit(ctx->ident(0)));
  std::string           addr1 = codAtsE1.addr;
  std::string           offs1 = codAtsE1.offs;
  instructionList &     code1 = codAtsE1.code;
  
  CodeAttribs     && codAtsE2 = std::any_cast<CodeAttribs>(visit(ctx->ident(1)));
  std::string           addr2 = codAtsE2.addr;
  //std::string           offs2 = codAtsE2.offs; // NO NECESARIO SEGÚN EL EJEMPLO
  instructionList &     code2 = codAtsE2.code;

  CodeAttribs     && codAtsE3 = std::any_cast<CodeAttribs>(visit(ctx->ident(2)));
  std::string           addr3 = codAtsE3.addr;
  //std::string           offs2 = codAtsE2.offs; // NO NECESARIO SEGÚN EL EJEMPLO
  instructionList &     code3 = codAtsE3.code;
  
  code = code1 || code2 || code3;

  std::string result = "%" + codeCounters.newTEMP();
  code = instruction::LOAD(result, "0");
  int n = Types.getArraySize(getTypeDecor(ctx->ident(0)));

  std::string ivar = "%"+codeCounters.newTEMP(); // comptador
    std::string limit = "%"+codeCounters.newTEMP(); // mida array
    std::string cond = "%"+codeCounters.newTEMP(); // condició
    std::string tempVal = "%"+codeCounters.newTEMP(); // valor temporal
    std::string inc = "%"+codeCounters.newTEMP(); // increment
    
    // Etiquetes del bucle
    std::string labelLoop = "while" + codeCounters.newLabelWHILE();
    std::string labelEnd = "whileEnd" + codeCounters.newLabelWHILE();
    
    // Inicialitzar bucle
    code = code || instruction::LOAD(limit, std::to_string(n)); // Límit del bucle: mida de l'array
    code = code || instruction::ILOAD(ivar, "0"); // i = 0 
    code = code || instruction::ILOAD(inc, "1");  // increment es 1
    
    // Bucle que recorre l'array
    code = code || instruction::LABEL(labelLoop);               // while (i < limit) {
    code = code || instruction::LT(cond, ivar, limit);          // cond = i < limit
    code = code || instruction::FJUMP(cond, labelEnd);

    code = code || instruction::LOADX(tempVal, addr1, ivar);    //value = a[i]
    code = code || instruction::PUSH();
    code = code || instruction::PUSH(tempVal);
    code = code || instruction::CALL(addr3);
    code = code || instruction::POP();
    code = code || instruction::POP(tempVal);
    code = code || instruction::XLOAD(addr2, ivar, tempVal);    // b[i] = value
    code = code || instruction::ADD(result, result, tempVal);   // temp += b[i]
    code = code || instruction::ADD(ivar, ivar, inc);           // i++
    code = code || instruction::UJUMP(labelLoop);
    code = code || instruction::LABEL(labelEnd);

  CodeAttribs codeAts(result, "", code);
  DEBUG_EXIT();
  return codeAts;
}
// op=(MINUS|NOT|PLUS) expr             # unary
std::any CodeGenVisitor::visitUnary(AslParser::UnaryContext *ctx){
  DEBUG_ENTER();
  CodeAttribs     && codAt1 = std::any_cast<CodeAttribs>(visit(ctx->expr()));
  std::string         addr1 = codAt1.addr;  // valor de l'expr
  instructionList &   code1 = codAt1.code;
  instructionList &    code = code1;
  TypesMgr::TypeId tid1 = getTypeDecor(ctx->expr());

  std::string temp = "%"+codeCounters.newTEMP();  // temp on guardarem el resultat
  if (ctx->NOT())
    code = code || instruction::NOT(temp, addr1); // apliquem el not sobre el valor 
  else if (ctx->MINUS()){
    if (Types.isIntegerTy(tid1) || Types.isBooleanTy(tid1)) {
      code = code || instruction::NEG(temp, addr1);
    }
    else{
      code = code || instruction::FNEG(temp, addr1);
    }
  }
  else if(ctx->PLUS()){
    temp = addr1; // no cal fer res perque a == +a
  }

  CodeAttribs codAts(temp, "", code);
  DEBUG_EXIT();
  return codAts;
}

// expr op=(MUL|DIV|MOD) expr           # arithmetic
// expr op=(PLUS|MINUS) expr            # arithmetic
std::any CodeGenVisitor::visitArithmetic(AslParser::ArithmeticContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs     && codAt1 = std::any_cast<CodeAttribs>(visit(ctx->expr(0)));
  std::string         addr1 = codAt1.addr;
  instructionList &   code1 = codAt1.code;
  CodeAttribs     && codAt2 = std::any_cast<CodeAttribs>(visit(ctx->expr(1)));
  std::string         addr2 = codAt2.addr;
  instructionList &   code2 = codAt2.code;
  instructionList &&   code = code1 || code2;
  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr(0));
  TypesMgr::TypeId t2 = getTypeDecor(ctx->expr(1));
  //TypesMgr::TypeId  t = getTypeDecor(ctx); 
  std::string temp = "%"+codeCounters.newTEMP();
  std::string temp1 = "%"+codeCounters.newTEMP();
  std::string temp2 = "%"+codeCounters.newTEMP();
  // Comprovar si cal aplicar coercio
  if (Types.isIntegerTy(t1) and Types.isFloatTy(t2)){
    // convertim l'expr1 a float en cas que sigui integer i l'altre float
    code = code || instruction::FLOAT(temp1, addr1);
  }else temp1 = addr1;
  if (Types.isIntegerTy(t2) and Types.isFloatTy(t1)){
    code = code || instruction::FLOAT(temp2, addr2);
  } else temp2 = addr2;
  if (Types.isFloatTy(t1) or Types.isFloatTy(t2)){
    // si es una operacio de floats utilitzem les operacions per a floats
    if (ctx->MUL())
      code = code || instruction::FMUL(temp, temp1, temp2);
    else if (ctx->PLUS())
      code = code || instruction::FADD(temp, temp1, temp2);
    else if (ctx->MINUS())
      code = code || instruction::FSUB(temp, temp1, temp2);
    else if (ctx->DIV())
      code = code || instruction::FDIV(temp, temp1, temp2);
  }else{  // isIntegerTy
    // si es una operacio d'enters utilitzem les operacions d'enters
    if (ctx->MUL())
      code = code || instruction::MUL(temp, temp1, temp2);
    else if (ctx->PLUS())
      code = code || instruction::ADD(temp, temp1, temp2);
    else if (ctx->MINUS())
      code = code || instruction::SUB(temp, temp1, temp2);
    else if (ctx->DIV())
      code = code || instruction::DIV(temp, temp1, temp2);
    else if (ctx->MOD()){
      std::string temp3 = "%"+codeCounters.newTEMP();
      std::string temp4 = "%"+codeCounters.newTEMP();
      code = code || instruction::DIV(temp3, temp1, temp2);
      code = code || instruction::MUL(temp4, temp2, temp3);
      code = code || instruction::SUB(temp, temp1, temp4);
    }
  }
  
  CodeAttribs codAts(temp, "", code);
  DEBUG_EXIT();
  return codAts;
}

// expr op=(EQUAL|NE|GT|GE|LT|LE) expr
std::any CodeGenVisitor::visitRelational(AslParser::RelationalContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs     && codAt1 = std::any_cast<CodeAttribs>(visit(ctx->expr(0)));
  std::string         addr1 = codAt1.addr;
  instructionList &   code1 = codAt1.code;
  CodeAttribs     && codAt2 = std::any_cast<CodeAttribs>(visit(ctx->expr(1)));
  std::string         addr2 = codAt2.addr;
  instructionList &   code2 = codAt2.code;
  instructionList &&   code = code1 || code2;
  
  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr(0));
  TypesMgr::TypeId t2 = getTypeDecor(ctx->expr(1));
  //TypesMgr::TypeId  t = getTypeDecor(ctx);
  
  std::string temp1 = "%"+codeCounters.newTEMP();
  std::string temp2 = "%"+codeCounters.newTEMP();
  // Comprovar si cal aplicar coercio
  if (Types.isIntegerTy(t1) and Types.isFloatTy(t2)){
    code = code || instruction::FLOAT(temp1, addr1);
  }else temp1 = addr1;
  if (Types.isIntegerTy(t2) and Types.isFloatTy(t1)){
    code = code || instruction::FLOAT(temp2, addr2);
  } else temp2 = addr2;

  std::string temp = "%"+codeCounters.newTEMP();
  if (Types.isFloatTy(t1) or Types.isFloatTy(t2)){
    if (ctx->EQUAL())
      code = code || instruction::FEQ(temp, temp1, temp2);
    else if (ctx->NE()){
      code = code || instruction::FEQ(temp, temp1, temp2);
      code = code || instruction::NOT(temp, temp);
    }
    else if (ctx->GT()){
      code = code || instruction::FLE(temp, temp1, temp2);
      code = code || instruction::NOT(temp, temp);
    }
    else if (ctx->GE()){
      code = code || instruction::FLT(temp, temp1, temp2);
      code = code || instruction::NOT(temp, temp);
    }
    else if (ctx->LT())
      code = code || instruction::FLT(temp, temp1, temp2);
    else if (ctx->LE())
      code = code || instruction::FLE(temp, temp1, temp2);
  }else if (Types.isBooleanTy(t1) or Types.isBooleanTy(t2)){
    if (ctx->EQUAL())
      code = code || instruction::EQ(temp, temp1, temp2);
    else if (ctx->NE()){
      code = code || instruction::EQ(temp, temp1, temp2);
      code = code || instruction::NOT(temp, temp);
    }
  }else{
    if (ctx->EQUAL())
      code = code || instruction::EQ(temp, temp1, temp2);
    else if (ctx->NE()){
      code = code || instruction::EQ(temp, temp1, temp2);
      code = code || instruction::NOT(temp, temp);
    }
    else if (ctx->GT()){
      code = code || instruction::LE(temp, temp1, temp2); // la GT es la neg de LE
      code = code || instruction::NOT(temp, temp);
    }
    else if (ctx->GE()){
      code = code || instruction::LT(temp, temp1, temp2);
      code = code || instruction::NOT(temp, temp);
    }
    else if (ctx->LT())
      code = code || instruction::LT(temp, temp1, temp2);
    else if (ctx->LE())
      code = code || instruction::LE(temp, temp1, temp2);
  }
  CodeAttribs codAts(temp, "", code);
  DEBUG_EXIT();
  return codAts;
}

// expr op=AND expr                     # logical
// expr op=OR expr                      # logical
std::any CodeGenVisitor::visitLogical(AslParser::LogicalContext *ctx){
  DEBUG_ENTER();
  CodeAttribs     && codAt1 = std::any_cast<CodeAttribs>(visit(ctx->expr(0)));
  std::string         addr1 = codAt1.addr;
  instructionList &   code1 = codAt1.code;
  CodeAttribs     && codAt2 = std::any_cast<CodeAttribs>(visit(ctx->expr(1)));
  std::string         addr2 = codAt2.addr;
  instructionList &   code2 = codAt2.code;
  instructionList &&   code = code1 || code2;
  std::string temp = "%"+codeCounters.newTEMP();
  if (ctx->AND())
    code = code || instruction::AND(temp, addr1, addr2);
  else if (ctx->OR())
    code = code || instruction::OR(temp, addr1, addr2);
  
  CodeAttribs codAts(temp, "", code); // resultat guardat al temp
  DEBUG_EXIT();
  return codAts;
  
}

// INTVAL                               # value
// FLOATVAL                             # value
// CHARVAL                              # value
// TRUE                                 # value
// FALSE                                # value
std::any CodeGenVisitor::visitValue(AslParser::ValueContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  std::string temp = "%"+codeCounters.newTEMP();
  // s'utilitza el iload per integers i bool (perque sera 0 o 1), fload per floats i chload per char
  // guardem el valor a un temporal (el qual es retorna)
  if (ctx->TRUE())
    code = instruction::ILOAD(temp, "1");
  else if (ctx->FALSE())
    code = instruction::ILOAD(temp, "0");
  else if (ctx->INTVAL())
    code = instruction::ILOAD(temp, ctx->getText());
  else if (ctx->FLOATVAL())
    code = instruction::FLOAD(temp, ctx->getText());
  else if (ctx->CHARVAL()){
    std::string c = ctx->getText();
    c = c.substr(1, c.length()-2); // treure les cometes del string
    code = instruction::CHLOAD(temp, c);
  }

  CodeAttribs codAts(temp, "", code);
  DEBUG_EXIT();
  return codAts;
}

std::any CodeGenVisitor::visitExprIdent(AslParser::ExprIdentContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs && codAts = std::any_cast<CodeAttribs>(visit(ctx->ident()));
  DEBUG_EXIT();
  return codAts;
}

// ident '[' expr ']'                   # array
std::any CodeGenVisitor::visitArray(AslParser::ArrayContext *ctx) {
  CodeAttribs     && codAt1 = std::any_cast<CodeAttribs>(visit(ctx->ident()));
  std::string         addr1 = codAt1.addr;
  instructionList &   code1 = codAt1.code;
  instructionList     code = code1;

  CodeAttribs     && codAt2 = std::any_cast<CodeAttribs>(visit(ctx->expr()));
  std::string         addr2 = codAt2.addr;
  instructionList &   code2 = codAt2.code;

  code = code || code2;
  // LOADX: a1 = a2[a3]
  std::string temp = "%"+codeCounters.newTEMP();
  std::string temp2 = "%"+codeCounters.newTEMP();
  if (Symbols.isParameterClass(ctx->ident()->getText())){
     code = code || instruction::LOAD(temp2, addr1);  // degut a que es un param cal obtenir l'adreça base (s'obte obtenint el contigut)
  }else{  
    code = code || instruction::ALOAD(temp2, addr1); // en cas que no sigui un param cal fer load de l'adreça no el seu contigut per tenir l'adreça base
  }
  code = code || instruction::LOADX(temp, temp2, addr2);  // temp = temp2[addr2]

  CodeAttribs codAts(temp, "", code); // temp: conte el valor en aquella pos de l'array
  DEBUG_EXIT();
  return codAts;
}

std::any CodeGenVisitor::visitIdent(AslParser::IdentContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs codAts(ctx->ID()->getText(), "", instructionList());  // retorna el text
  DEBUG_EXIT();
  return codAts;
}

std::any CodeGenVisitor::visitParenthesis(AslParser::ParenthesisContext *ctx){
  DEBUG_ENTER();
  CodeAttribs     && codAt1 = std::any_cast<CodeAttribs>(visit(ctx->expr()));
  std::string         addr1 = codAt1.addr;
  instructionList &   code1 = codAt1.code;
  instructionList &    code = code1;
  std::string temp = "%"+codeCounters.newTEMP();
  CodeAttribs codAts(temp, "", code);
  DEBUG_EXIT();
  return codAt1;
}


// Getters for the necessary tree node atributes:
//   Scope and Type
SymTable::ScopeId CodeGenVisitor::getScopeDecor(antlr4::ParserRuleContext *ctx) const {
  return Decorations.getScope(ctx);
}
TypesMgr::TypeId CodeGenVisitor::getTypeDecor(antlr4::ParserRuleContext *ctx) const {
  return Decorations.getType(ctx);
}


// Constructors of the class CodeAttribs:
//
CodeGenVisitor::CodeAttribs::CodeAttribs(const std::string & addr,
                                         const std::string & offs,
                                         instructionList & code) :
  addr{addr}, offs{offs}, code{code} {
}

CodeGenVisitor::CodeAttribs::CodeAttribs(const std::string & addr,
                                         const std::string & offs,
                                         instructionList && code) :
  addr{addr}, offs{offs}, code{code} {
}
