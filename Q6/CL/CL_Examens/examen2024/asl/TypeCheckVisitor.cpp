//////////////////////////////////////////////////////////////////////
//
//    TypeCheckVisitor - Walk the parser tree to do the semantic
//                       typecheck for the Asl programming language
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

#include "TypeCheckVisitor.h"
#include "antlr4-runtime.h"

#include "../common/TypesMgr.h"
#include "../common/SymTable.h"
#include "../common/TreeDecoration.h"
#include "../common/SemErrors.h"

#include <iostream>
#include <string>

// uncomment the following line to enable debugging messages with DEBUG*
//#define DEBUG_BUILD
#include "../common/debug.h"

// using namespace std;


// Constructor
TypeCheckVisitor::TypeCheckVisitor(TypesMgr       & Types,
                                   SymTable       & Symbols,
                                   TreeDecoration & Decorations,
                                   SemErrors      & Errors) :
  Types{Types},
  Symbols{Symbols},
  Decorations{Decorations},
  Errors{Errors} {
}

// Accessor/Mutator to the attribute currFunctionType
TypesMgr::TypeId TypeCheckVisitor::getCurrentFunctionTy() const {
  return currFunctionType;
}

void TypeCheckVisitor::setCurrentFunctionTy(TypesMgr::TypeId type) {
  currFunctionType = type;
}

// Methods to visit each kind of node:
//
std::any TypeCheckVisitor::visitProgram(AslParser::ProgramContext *ctx) {
  DEBUG_ENTER();
  SymTable::ScopeId sc = getScopeDecor(ctx);
  Symbols.pushThisScope(sc);
  for (auto ctxFunc : ctx->function()) { 
    visit(ctxFunc);
  }
  if (Symbols.noMainProperlyDeclared())
    Errors.noMainProperlyDeclared(ctx);
  Symbols.popScope();
  Errors.print();
  DEBUG_EXIT();
  return 0;
}

// FUNC ID '(' parameters? ')' (':' basic_type)? declarations statements ENDFUNC
std::any TypeCheckVisitor::visitFunction(AslParser::FunctionContext *ctx) {
  DEBUG_ENTER();
  // Obtenim l'scope de la funció i accedim
  SymTable::ScopeId sc = getScopeDecor(ctx);
  Symbols.pushThisScope(sc);

  // Parameters
  if (ctx->parameters()){
    visit(ctx->parameters());
  }

  // Type
  TypesMgr::TypeId tRet;
  if (ctx->basic_type()){ // Si és una funció (perque té return)
    tRet = getTypeDecor(ctx->basic_type());
  } else {  // si és un procediment
    tRet = Types.createVoidTy();
  }

  setCurrentFunctionTy(tRet); // modificar el tipus de la funció actual

  visit(ctx->declarations());
  visit(ctx->statements());

  Symbols.popScope();
  DEBUG_EXIT();
  return 0;
}

// ident '(' (expr (',' expr)*)? ')'    # functionCall
std::any TypeCheckVisitor::visitFunctionCall(AslParser::FunctionCallContext *ctx) {
  DEBUG_ENTER();
  // Visitem l'identificador de la funció i obtenim el seu tipus
  visit(ctx->ident());
  TypesMgr::TypeId tFunc = getTypeDecor(ctx->ident());

  // Si no és una funció ni tipus error, donem error
  if (not Types.isErrorTy(tFunc) and not Types.isFunctionTy(tFunc)) {  
    Errors.isNotCallable(ctx->ident());         // Indiquem que no es pot trucar
    putTypeDecor(ctx, Types.createErrorTy()); 
    putIsLValueDecor(ctx, false);   // Les funcions mai son modificables -> Lvalue false 
    for (uint i = 0; i < ctx->expr().size(); ++i){  // Tot i no ser una funció, comprovem si els paràmetres estan ben formatats
      visit(ctx->expr(i));
    }
  } 
  else if (Types.isFunctionTy(tFunc)) {  // Si és una funció
    // Obtenim el tipus de retorn de la funció
    TypesMgr::TypeId tRet = Types.getFuncReturnType(tFunc);   // Amb el TypeId de la funció pots obtenir la seva informació (com el tipus de retorn)

    if (Types.isVoidTy(tRet)) { // En cas que no sigui una funció (perque retorna void, és un proc)
      Errors.isNotFunction(ctx->ident());
      putTypeDecor(ctx, Types.createErrorTy());
    }else{
      putTypeDecor(ctx, tRet);  // Decorem la FunctionCall amb el seu tipus de retorn
      putIsLValueDecor(ctx, false);
    }
    
    // Obtenim l'scope de la funció i accedim
    SymTable::ScopeId sc = getScopeDecor(ctx->ident());
    Symbols.pushThisScope(sc);
    
    //Comprovar que el nombre de parametres sigui el mateix
    if (ctx->expr().size() != Types.getNumOfParameters(tFunc))
      Errors.numberOfParameters(ctx);
    else{
      std::vector<TypesMgr::TypeId> paramTypes = Types.getFuncParamsTypes(tFunc);
      for (uint i = 0; i < ctx->expr().size(); ++i){
        visit(ctx->expr(i));
        TypesMgr::TypeId t2 = getTypeDecor(ctx->expr(i));
        // Si el tipus dels paràmetres és float i el tipus de l'expressió és int, el canviem a float
        if (Types.isFloatTy(paramTypes[i]) and Types.isIntegerTy(t2)) {
          t2 = Types.createFloatTy();
        }
        // Comprovem que coincideixin els tipus de paràmetres
        if (not Types.isErrorTy(t2) and not Types.equalTypes(paramTypes[i], t2)){ 
          Errors.incompatibleParameter(ctx->expr(i), i+1, ctx);
        }
      }   
    }
    Symbols.popScope();
    
  }else{  // En cas de ser error i continua decorant com error, només comprova si els paràmetres estan be formatats
    putTypeDecor(ctx, Types.createErrorTy()); 
    for (uint i = 0; i < ctx->expr().size(); ++i){
      visit(ctx->expr(i));
    }
  }
  
  DEBUG_EXIT();
  return 0;
}

// std::any TypeCheckVisitor::visitDeclarations(AslParser::DeclarationsContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any TypeCheckVisitor::visitVariable_decl(AslParser::Variable_declContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any TypeCheckVisitor::visitType(AslParser::TypeContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

std::any TypeCheckVisitor::visitStatements(AslParser::StatementsContext *ctx) {
  DEBUG_ENTER();
  visitChildren(ctx);

  // caldra fer gettype
  DEBUG_EXIT();
  return 0;
}

std::any TypeCheckVisitor::visitAssignStmt(AslParser::AssignStmtContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->left_expr());
  visit(ctx->expr());
  TypesMgr::TypeId t1 = getTypeDecor(ctx->left_expr());
  TypesMgr::TypeId t2 = getTypeDecor(ctx->expr());

  if ((not Types.isErrorTy(t1)) and (not Types.isErrorTy(t2)) and
      (not Types.copyableTypes(t1, t2)))
    Errors.incompatibleAssignment(ctx->ASSIGN());
  if ((not Types.isErrorTy(t1)) and (not getIsLValueDecor(ctx->left_expr())))
    Errors.nonReferenceableLeftExpr(ctx->left_expr());
  DEBUG_EXIT();
  return 0;
}

// IF expr THEN statements ELSE statements ENDIF  # ifElseStmt
std::any TypeCheckVisitor::visitIfElseStmt(AslParser::IfElseStmtContext *ctx) {
  DEBUG_ENTER();
  // visitem l'expr i obtenim el seu tipus
  visit(ctx->expr());
  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr());
  // error en cas que no sigui un booleà
  if ((not Types.isErrorTy(t1)) and (not Types.isBooleanTy(t1)))
    Errors.booleanRequired(ctx);
  // visitem ambdós blocs de statements (el de if i el de else)
  visit(ctx->statements(0));
  if (ctx -> ELSE()) visit(ctx->statements(1));
  DEBUG_EXIT();
  return 0;
}


// caldra fer gettype
// IF expr THEN statements ENDIF  # ifStmt
/*std::any TypeCheckVisitor::visitIfStmt(AslParser::IfStmtContext *ctx) {
  DEBUG_ENTER();
  // visitem l'expr i obtenim el seu tipus
  visit(ctx->expr());
  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr());
  // error en cas que no sigui un booleà
  if ((not Types.isErrorTy(t1)) and (not Types.isBooleanTy(t1)))
    Errors.booleanRequired(ctx);
  visit(ctx->statements());   // visitem les statements
  DEBUG_EXIT();
  return 0;
}*/

// WHILE expr DO statements ENDWHILE     # whileStmt
std::any TypeCheckVisitor::visitWhileStmt(AslParser::WhileStmtContext *ctx) {
  DEBUG_ENTER();
  // visitem l'expr i obtenim el seu tipus
  visit(ctx->expr());
  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr());
  // error en cas que no sigui un booleà
  if ((not Types.isErrorTy(t1)) and (not Types.isBooleanTy(t1)))
    Errors.booleanRequired(ctx);
  visit(ctx->statements()); // visitem les statements
  DEBUG_EXIT();
  return 0;
}

std::any TypeCheckVisitor::visitSwapStmt(AslParser::SwapStmtContext *ctx){
  DEBUG_ENTER();
  visit(ctx->left_expr(0));
  visit(ctx->left_expr(1));
  TypesMgr::TypeId t0 = getTypeDecor(ctx->left_expr(0));
  TypesMgr::TypeId t1 = getTypeDecor(ctx->left_expr(1));

  if (not Types.isErrorTy(t0) and not Types.isErrorTy(t1) and not Types.equalTypes(t0, t1))
    Errors.incompatibleArgumentsInSwap(ctx);

  DEBUG_EXIT();
  return 0;
}


std::any TypeCheckVisitor::visitSwitchStmt(AslParser::SwitchStmtContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->expr(0));
  TypesMgr::TypeId tE = getTypeDecor(ctx->expr(0));
  for (uint i = 0; i < ctx->CASE().size(); ++i){
    visit(ctx->expr(i+1));
    TypesMgr::TypeId tV = getTypeDecor(ctx->expr(i+1));
    if (not Types.isErrorTy(tE) and not Types.isErrorTy(tV) and not Types.comparableTypes(tE, tV, "="))
      Errors.incompatibleValueInSwitch(ctx->expr(i+1));
  }
  for (auto stmt : ctx->statements()){
    visit(stmt);
  }
  DEBUG_EXIT();
  return 0;
}


// RETURN (expr)? ';'                    #returnStmt
std::any TypeCheckVisitor::visitReturnStmt(AslParser::ReturnStmtContext *ctx) {
    DEBUG_ENTER();
    // Si hi ha expr, la visitem
    if(ctx->expr()){
      visit(ctx->expr());
      // obtenim el tipus de l'expr
      TypesMgr::TypeId t1 = getTypeDecor(ctx->expr());
      // obtenim el tipus de retorn de la funció actual
      TypesMgr::TypeId tRet = getCurrentFunctionTy();

      // si els tipus no coincideixen, error de return incompatible
      if ((not Types.isErrorTy(t1)) and (not Types.isErrorTy(tRet)) and (not Types.copyableTypes(tRet,t1)))   // copyableTypes perque si ens fiquen return 14 i esperen float doncs permet retornar com a float el int 14
        Errors.incompatibleReturn(ctx->RETURN());
    }else{
      // si no hi ha expr, és un return buit
      // obtenim el tipus de retorn de la funció actual
      TypesMgr::TypeId tRet = getCurrentFunctionTy();
      if (not Types.isVoidTy(tRet))   // si el tipus de retorn no és void, error de return incompatible
        Errors.incompatibleReturn(ctx->RETURN()); // a menys que sigui void, no podríem no retornar res
    }

    DEBUG_EXIT();
    return 0;
}

std::any TypeCheckVisitor::visitProcCall(AslParser::ProcCallContext *ctx) {
  DEBUG_ENTER();

  visit(ctx->ident());
  TypesMgr::TypeId t1 = getTypeDecor(ctx->ident());
  if (not Types.isErrorTy(t1) and not Types.isFunctionTy(t1)) {
    Errors.isNotCallable(ctx->ident());
    putTypeDecor(ctx, Types.createErrorTy()); 
    for (uint i = 0; i < ctx->expr().size(); ++i){  // Tot i no ser una funció, comprovem si els paràmetres estan ben formatats
      visit(ctx->expr(i));
    }
  } 
  else if (Types.isFunctionTy(t1)) {  
  
    TypesMgr::TypeId tFunc = Symbols.getType(ctx->ident()->getText());
    TypesMgr::TypeId tRet = Types.getFuncReturnType(tFunc);

    SymTable::ScopeId sc = getScopeDecor(ctx->ident());
    Symbols.pushThisScope(sc);

    putTypeDecor(ctx, tRet);
    putIsLValueDecor(ctx, false);
      
    //Comprovar que el nombre de parametres sigui el mateix
    if (ctx->expr().size() != Types.getNumOfParameters(t1)){
      Errors.numberOfParameters(ctx);
      for (uint i = 0; i < ctx->expr().size(); ++i){  // Tot i no coincidir el nombre de parametres els visitem per comprovar s
        visit(ctx->expr(i));
      }
    }else{
      std::vector<TypesMgr::TypeId> paramTypes = Types.getFuncParamsTypes(t1);
      for (uint i = 0; i < ctx->expr().size(); ++i){
        visit(ctx->expr(i));
        TypesMgr::TypeId t2 = getTypeDecor(ctx->expr(i));
        if (Types.isFloatTy(paramTypes[i]) and Types.isIntegerTy(t2)) {
          t2 = Types.createFloatTy();
        }
        if (not Types.isErrorTy(t2) and not Types.equalTypes(paramTypes[i], t2)){ 
          Errors.incompatibleParameter(ctx->expr(i), i+1, ctx);
        }
      }   
    }
    Symbols.popScope();
  }else{  // En cas de no ser funció, només comprova si els paràmetres estan be formatats
    for (uint i = 0; i < ctx->expr().size(); ++i){
      visit(ctx->expr(i));
    }
  }

  DEBUG_EXIT();
  return 0;
}

std::any TypeCheckVisitor::visitReadStmt(AslParser::ReadStmtContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->left_expr());
  TypesMgr::TypeId t1 = getTypeDecor(ctx->left_expr());
  if ((not Types.isErrorTy(t1)) and (not Types.isPrimitiveTy(t1)) and
      (not Types.isFunctionTy(t1)))
    Errors.readWriteRequireBasic(ctx);
  if ((not Types.isErrorTy(t1)) and (not getIsLValueDecor(ctx->left_expr())))
    Errors.nonReferenceableExpression(ctx);
  DEBUG_EXIT();
  return 0;
}

std::any TypeCheckVisitor::visitWriteExpr(AslParser::WriteExprContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->expr());
  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr());
  if ((not Types.isErrorTy(t1)) and (not Types.isPrimitiveTy(t1)))
    Errors.readWriteRequireBasic(ctx);
  DEBUG_EXIT();
  return 0;
}

// std::any TypeCheckVisitor::visitWriteString(AslParser::WriteStringContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

std::any TypeCheckVisitor::visitLeft_expr(AslParser::Left_exprContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->ident());
  TypesMgr::TypeId t1 = getTypeDecor(ctx->ident());
  if (ctx->expr()){
    if (Types.isIntegerTy(t1) or Types.isFloatTy(t1) or Types.isCharacterTy(t1) or Types.isBooleanTy(t1) or Types.isFunctionTy(t1)) {
      Errors.nonArrayInArrayAccess(ctx->ident());
    } else if (Types.isErrorTy(t1)){
      putTypeDecor(ctx, Types.createErrorTy());
      bool b = getIsLValueDecor(ctx->ident());
      putIsLValueDecor(ctx, b);
    } 
    else { // és un array
      TypesMgr::TypeId t = Types.getArrayElemType(t1);  // Comprovem el tipus dels elements de l'array
      putTypeDecor(ctx, t); // Decorem l'expressió amb el tipus dels elements de l'array perque retorna l'element de l'array: a[3] -> int
      bool b = getIsLValueDecor(ctx->ident());
      putIsLValueDecor(ctx, b);
    }

    visit(ctx->expr());
    TypesMgr::TypeId t2 = getTypeDecor(ctx->expr());
  
    if ((not Types.isErrorTy(t2)) and (not Types.isIntegerTy(t2)))
      Errors.nonIntegerIndexInArrayAccess(ctx->expr());
  }else{
    putTypeDecor(ctx, t1);
    bool b = getIsLValueDecor(ctx->ident());
    putIsLValueDecor(ctx, b);
  }
  DEBUG_EXIT();
  return 0;
}

//  ident '[' expr ']'                   # array
std::any TypeCheckVisitor::visitArray(AslParser::ArrayContext *ctx) {
  DEBUG_ENTER();

  // Obtenim el tipus de l'identificador
  visit(ctx->ident());
  TypesMgr::TypeId t1 = getTypeDecor(ctx->ident());
  // Si no és de tipus array i no és de tipus error -> mostrem error
  if(not Types.isErrorTy(t1) and not Types.isArrayTy(t1)){
    Errors.nonArrayInArrayAccess(ctx->ident());
    putTypeDecor(ctx, Types.createErrorTy()); // cal decorar amb error en aquest cas 
    bool b = getIsLValueDecor(ctx->ident());  // tot i això, ha de tenir el Lvalue del seu ident
    putIsLValueDecor(ctx, b);
  } else if (Types.isErrorTy(t1)){  // si és error
    putTypeDecor(ctx, Types.createErrorTy()); // decorem amb tipus error
    bool b = getIsLValueDecor(ctx->ident());
    putIsLValueDecor(ctx, b);
  } else { // és un array
    TypesMgr::TypeId t = Types.getArrayElemType(t1);  // Comprovem el tipus dels elements de l'array
    putTypeDecor(ctx, t); // Decorem l'expressió amb el tipus dels elements de l'array perque retorna l'element de l'array: a[3] -> int
    bool b = getIsLValueDecor(ctx->ident());
    putIsLValueDecor(ctx, b);
  }

  // Obtenim el tipus de l'expressió
  visit(ctx->expr());
  TypesMgr::TypeId t2 = getTypeDecor(ctx->expr());

  // Si no és error i no és integer, error d'accés a l'array amb índex no enter
  if ((not Types.isErrorTy(t2)) and (not Types.isIntegerTy(t2)))
    Errors.nonIntegerIndexInArrayAccess(ctx->expr());

  DEBUG_EXIT();
  return 0;
}

// op=(MINUS|NOT|PLUS) expr             # unary
std::any TypeCheckVisitor::visitUnary(AslParser::UnaryContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->expr());
  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr());
  if (Types.isErrorTy(t1))  // Si l'expr és error, decorem l'unary com error
    putTypeDecor(ctx, Types.createErrorTy());
  else if (ctx->MINUS()) {  // Si és '-' i no és error, comprovem que sigui numèric
    if (not Types.isNumericTy(t1)){
      Errors.incompatibleOperator(ctx->op); // Si no és numèric, operadors incompatibles
      putTypeDecor(ctx, Types.createErrorTy()); // Cal decorar tota l'expr unary com error
    }else{
      putTypeDecor(ctx, t1);  // Si és numèric, decorar amb el tipus de l'expr (numeric)
    }
  } else if (ctx->NOT()) {  // Si és 'not' i no és error, comprovem que sigui booleà
    if (not Types.isBooleanTy(t1)){
      Errors.incompatibleOperator(ctx->op); // Si no és booleà, operadors incompatibles
      putTypeDecor(ctx, Types.createErrorTy()); // Cal decorar tota l'expr unary com error
    }else{
      putTypeDecor(ctx, t1);  // Si és booleà, decorar amb el tipus de l'expr (boolean)
    }
  } else if (ctx->PLUS()) {
    if (not Types.isNumericTy(t1)){
      Errors.incompatibleOperator(ctx->op);
      putTypeDecor(ctx, Types.createErrorTy());
    }else{
      putTypeDecor(ctx, t1);
    }
  }
  DEBUG_EXIT();
  return 0;
}

// expr op=(MUL|DIV|MOD|PLUS|MINUS) expr # arithmetic
std::any TypeCheckVisitor::visitArithmetic(AslParser::ArithmeticContext *ctx) {
  DEBUG_ENTER();
  // Obtenim de la taula de símbols el tipus d'ambdues expressions
  visit(ctx->expr(0));
  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr(0));
  visit(ctx->expr(1));
  TypesMgr::TypeId t2 = getTypeDecor(ctx->expr(1));
  TypesMgr::TypeId t;
  if (ctx->MOD()){  // en el cas de MOD els dos han de ser integer
    if (((not Types.isErrorTy(t1)) and (not Types.isIntegerTy(t1))) or 
        ((not Types.isErrorTy(t2)) and (not Types.isIntegerTy(t2)))){
      Errors.incompatibleOperator(ctx->op);
    }
    t = Types.createIntegerTy();  // mod sempre donarà int
  }else{  // la resta poden ser independentment float o int
    if (((not Types.isErrorTy(t1)) and (not Types.isNumericTy(t1))) or 
        ((not Types.isErrorTy(t2)) and (not Types.isNumericTy(t2)))){
      Errors.incompatibleOperator(ctx->op);
    }
    if (Types.isFloatTy(t1) or Types.isFloatTy(t2)) // si un dels dos es float el resultat es float
      t = Types.createFloatTy();
    else 
      t = Types.createIntegerTy();
  }
  putTypeDecor(ctx, t); // Decorem l'arithmetic amb el tipus resultant (float o int)
  putIsLValueDecor(ctx, false); // Una expr aritmètica no és modificable, no és lvalue
  DEBUG_EXIT();
  return 0;
}

// expr op=(EQUAL|NE|GT|GE|LT|LE) expr  # relational
std::any TypeCheckVisitor::visitRelational(AslParser::RelationalContext *ctx) {
  DEBUG_ENTER();
  // Obtenim de la taula de símbols el tipus d'ambdues expressions
  visit(ctx->expr(0));
  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr(0));
  visit(ctx->expr(1));
  TypesMgr::TypeId t2 = getTypeDecor(ctx->expr(1));

  // Si un dels dos és float i l'altre no, el convertim a float (type coercion)
  if (Types.isFloatTy(t1) && Types.isIntegerTy(t2)) {
    t2 = coercionIntToFloat(t2);
  } else if (Types.isFloatTy(t2) && Types.isIntegerTy(t1)) {
    t1 = coercionIntToFloat(t1);
  }

  // Comprovem que els tipus siguin comparables
  std::string oper = ctx->op->getText();
  if ((not Types.isErrorTy(t1)) and (not Types.isErrorTy(t2)) and
      (not Types.comparableTypes(t1, t2, oper))) {
    Errors.incompatibleOperator(ctx->op);
  }

  // El resultat d'una expressió relacional és sempre booleà
  TypesMgr::TypeId t = Types.createBooleanTy();
  putTypeDecor(ctx, t);
  putIsLValueDecor(ctx, false); // Una expr relacional no és modificable, no és lvalue
  DEBUG_EXIT();
  return 0;
}

// expr op=AND expr                     # logical
// expr op=OR expr                      # logical
std::any TypeCheckVisitor::visitLogical(AslParser::LogicalContext *ctx) {
  DEBUG_ENTER();
  // Obtenim de la taula de símbols el tipus d'ambdues expressions
  visit(ctx->expr(0));
  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr(0));
  visit(ctx->expr(1));
  TypesMgr::TypeId t2 = getTypeDecor(ctx->expr(1));

  // Si un dels dos no és booleà, error d'incompatibilitat
  if (((not Types.isErrorTy(t1)) and (not Types.isBooleanTy(t1))) or
      ((not Types.isErrorTy(t2)) and (not Types.isBooleanTy(t2)))) {
    Errors.incompatibleOperator(ctx->op);
  }

  // El resultat d'una expressió lògica és sempre booleà
  TypesMgr::TypeId t = Types.createBooleanTy();
  putTypeDecor(ctx, t);
  putIsLValueDecor(ctx, false); // Una expr lògica no és modificable, no és lvalue
  DEBUG_EXIT();
  return 0;
}

std::any TypeCheckVisitor::visitValue(AslParser::ValueContext *ctx) {
  DEBUG_ENTER();
  TypesMgr::TypeId t;
  if (ctx->INTVAL()) 
    t = Types.createIntegerTy();
  else if (ctx->FLOATVAL()) 
    t = Types.createFloatTy();
  else if (ctx->TRUE() or ctx->FALSE()) 
    t = Types.createBooleanTy();
  else if (ctx->CHARVAL()) 
    t = Types.createCharacterTy();

  // Decorem l'expressió amb el tipus corresponent
  putTypeDecor(ctx, t);
  putIsLValueDecor(ctx, false);
  DEBUG_EXIT();
  return 0;

}

std::any TypeCheckVisitor::visitExprIdent(AslParser::ExprIdentContext *ctx) {
  DEBUG_ENTER();
  // Quan l'expr correspon a un identificador, obtenim el tipus de l'identificador
  visit(ctx->ident());
  TypesMgr::TypeId t1 = getTypeDecor(ctx->ident());
  // Decorem l¡expr amb el tipus de l'id i si és modificable o no
  putTypeDecor(ctx, t1);
  bool b = getIsLValueDecor(ctx->ident());
  putIsLValueDecor(ctx, b);
  DEBUG_EXIT();
  return 0;
}

//  '(' expr ')'             # parenthesis
std::any TypeCheckVisitor::visitParenthesis(AslParser::ParenthesisContext *ctx) {
  DEBUG_ENTER();
  // Obtenim el tipus de l'expressió continguda dins els parèntesis
  visit(ctx->expr());
  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr());
  putTypeDecor(ctx, t1);  // Decorem l'expressió amb el tipus de l'expressió continguda
  putIsLValueDecor(ctx, getIsLValueDecor(ctx->expr())); // Indiquem si és modificable o no segons l'expressió continguda
  DEBUG_EXIT();
  return 0;
}

std::any TypeCheckVisitor::visitIdent(AslParser::IdentContext *ctx) {
  DEBUG_ENTER();
  // Obtenim el text de l'identificador
  std::string ident = ctx->getText();
  // Busquem l'identificador a la taula de símbols
  if (Symbols.findInStack(ident) == -1) { // Si no trobem l'identificador (-1), error
    Errors.undeclaredIdent(ctx->ID());  // Indiquem que l'identificador no està declarat
    TypesMgr::TypeId te = Types.createErrorTy();
    putTypeDecor(ctx, te);
    putIsLValueDecor(ctx, true);      // Si li hem donat tipus error podem fer lvalue true? Si perque no sabem quin us tindra
  }
  else {  // Si trobem l'identificador
    TypesMgr::TypeId t1 = Symbols.getType(ident);
    putTypeDecor(ctx, t1);  // Decorem l'identificador amb el seu tipus
    if (Symbols.isFunctionClass(ident))
      putIsLValueDecor(ctx, false); // Si és una funció, no és modificable
    else
      putIsLValueDecor(ctx, true);
  }
  DEBUG_EXIT();
  return 0;
}

TypesMgr::TypeId TypeCheckVisitor::coercionIntToFloat(TypesMgr::TypeId t) {
  if (Types.isIntegerTy(t)) {
    return Types.createFloatTy();
  }
  return 0;
}


// Getters for the necessary tree node atributes:
//   Scope, Type ans IsLValue
SymTable::ScopeId TypeCheckVisitor::getScopeDecor(antlr4::ParserRuleContext *ctx) {
  return Decorations.getScope(ctx);
}
TypesMgr::TypeId TypeCheckVisitor::getTypeDecor(antlr4::ParserRuleContext *ctx) {
  return Decorations.getType(ctx);
}
bool TypeCheckVisitor::getIsLValueDecor(antlr4::ParserRuleContext *ctx) {
  return Decorations.getIsLValue(ctx);
}

// Setters for the necessary tree node attributes:
//   Scope, Type ans IsLValue
void TypeCheckVisitor::putScopeDecor(antlr4::ParserRuleContext *ctx, SymTable::ScopeId s) {
  Decorations.putScope(ctx, s);
}
void TypeCheckVisitor::putTypeDecor(antlr4::ParserRuleContext *ctx, TypesMgr::TypeId t) {
  Decorations.putType(ctx, t);
}
void TypeCheckVisitor::putIsLValueDecor(antlr4::ParserRuleContext *ctx, bool b) {
  Decorations.putIsLValue(ctx, b);
}
