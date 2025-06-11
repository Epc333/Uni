//////////////////////////////////////////////////////////////////////
//
//    SymbolsVisitor - Walk the parser tree to register symbols
//                     for the Asl programming language
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

#include "SymbolsVisitor.h"
#include "antlr4-runtime.h"

#include "../common/TypesMgr.h"
#include "../common/SymTable.h"
#include "../common/TreeDecoration.h"
#include "../common/SemErrors.h"

#include <iostream>
#include <string>
#include <vector>

#include <cstddef>    // std::size_t

// uncomment the following line to enable debugging messages with DEBUG*
//#define DEBUG_BUILD
#include "../common/debug.h"

// using namespace std;


// Constructor
SymbolsVisitor::SymbolsVisitor(TypesMgr       & Types,
                               SymTable       & Symbols,
                               TreeDecoration & Decorations,
                               SemErrors      & Errors) :
  Types{Types},
  Symbols{Symbols},
  Decorations{Decorations},
  Errors{Errors} {
}

// Methods to visit each kind of node:
//
std::any SymbolsVisitor::visitProgram(AslParser::ProgramContext *ctx) {
  DEBUG_ENTER();
  SymTable::ScopeId sc = Symbols.pushNewScope(SymTable::GLOBAL_SCOPE_NAME);
  putScopeDecor(ctx, sc);
  for (auto ctxFunc : ctx->function()) { 
    visit(ctxFunc);
  }
  // Symbols.print();
  Symbols.popScope();
  DEBUG_EXIT();
  return 0;
}


std::any SymbolsVisitor::visitFunction(AslParser::FunctionContext *ctx) {
  DEBUG_ENTER();
  // obtenim el nom de la funció
  std::string funcName = ctx->ID()->getText();
  // accedim al scope de la funció (amb el seu nom)
  SymTable::ScopeId sc = Symbols.pushNewScope(funcName);
  putScopeDecor(ctx, sc);

  if (ctx->parameters())  // Si té paràmetres, els visitem
    visit(ctx->parameters());

  visit(ctx->declarations());   // Visitem les declaracions de la funció
  
  // Symbols.print();
  Symbols.popScope();   // Sortim del scope de la funció

  // Comprovem si la funció ja existeix a la taula de símbols
  std::string ident = ctx->ID()->getText();
  if (Symbols.findInCurrentScope(ident)) {
    Errors.declaredIdent(ctx->ID());
  }
  else {
    std::vector<TypesMgr::TypeId> lParamsTy;
    if (ctx->parameters())
      for (auto param : ctx->parameters()->parameter()){  // Recorrem els paràmetres de la funció
        visit(param->type()); // Obtenim el tipus de cada paràmetre
        lParamsTy.push_back(getTypeDecor(param->type())); // Afegim el tipus a la llista de tipus de paràmetres
      }

    //Per gestionar si retorna algo
    TypesMgr::TypeId tRet;
    // Si té return, tindrà un basic_type (tipus de retorn), sinó serà un procediment
    if (ctx->basic_type()){ // Si és una funció (perque té return)
      visit(ctx->basic_type());
      tRet = getTypeDecor(ctx->basic_type()); // Obtenim el tipus de retorn
    } else {  // si és un procediment
      tRet = Types.createVoidTy();  
    }
    // Creem la funció amb els paràmetres i el tipus de retorn
    TypesMgr::TypeId tFunc = Types.createFunctionTy(lParamsTy, tRet);
    Symbols.addFunction(ident, tFunc);
  }

  DEBUG_EXIT();
  return 0;
}

std::any SymbolsVisitor::visitDeclarations(AslParser::DeclarationsContext *ctx) {
  DEBUG_ENTER();
  visitChildren(ctx);
  DEBUG_EXIT();
  return 0;
}

std::any SymbolsVisitor::visitVariable_decl(AslParser::Variable_declContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->type());
  // Obtenim el tipus de la variable (en type)
  TypesMgr::TypeId t1 = getTypeDecor(ctx->type());
  // Per cada identificador, comprovem si ja existeix a la taula de símbols
  for (auto id : ctx->ID()) {
    std::string ident = id->getText();
    if (Symbols.findInCurrentScope(ident)) {
      Errors.declaredIdent(id); // Si ja existeix, error
    } else {
      Symbols.addLocalVar(ident, t1); // Si no existeix, l'afegim a la taula de símbols
    }
  }
  DEBUG_EXIT();
  return 0;
}

std::any SymbolsVisitor::visitBasic_type(AslParser::Basic_typeContext *ctx) {
  DEBUG_ENTER();
  TypesMgr::TypeId t;
  if (ctx->INT()) {
    t = Types.createIntegerTy();
  }
  else if (ctx->FLOAT()) {
    t = Types.createFloatTy();
  }
  else if (ctx->BOOL()) {
    t = Types.createBooleanTy();
  } 
  else{ // if (ctx->CHAR()) {
    t = Types.createCharacterTy();
  }
  putTypeDecor(ctx, t);

  DEBUG_EXIT();
  return 0;
}

std::any SymbolsVisitor::visitType(AslParser::TypeContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->basic_type());
  
  // No emetem missatge d'error en cas que la mida de l'array sigui menor que 0
  TypesMgr::TypeId t = getTypeDecor(ctx->basic_type());

  if (ctx->ARRAY()){
      t = Types.createArrayTy(std::stoi(ctx->INTVAL(0)->getText()), t);
  } else if (ctx->MATRIX()){
      unsigned int rows = std::stoi(ctx->INTVAL(0)->getText());
      unsigned int cols = std::stoi(ctx->INTVAL(1)->getText());
      t = Types.createMatrixTy(rows, cols, t);
  }
  putTypeDecor(ctx, t);

  DEBUG_EXIT();
  return 0;
}

std::any SymbolsVisitor::visitParameter(AslParser::ParameterContext *ctx) {
  DEBUG_ENTER();
  // Visitem el tipus i decorem el parametre amb el tipus
  visit(ctx->type());
  TypesMgr::TypeId t = getTypeDecor(ctx->type());

  auto id = ctx->ID();
  std::string ident = ctx->ID()->getText();
  if (Symbols.findInCurrentScope(ident)) {
    Errors.declaredIdent(id);
  } else {
    Symbols.addParameter(ident, t);
    putTypeDecor(ctx, t); // Decorem el parametre amb el tipus
  }
  DEBUG_EXIT();
  return 0;
}

// std::any SymbolsVisitor::visitStatements(AslParser::StatementsContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any SymbolsVisitor::visitAssignStmt(AslParser::AssignStmtContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any SymbolsVisitor::visitIfStmt(AslParser::IfStmtContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any SymbolsVisitor::visitProcCall(AslParser::ProcCallContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any SymbolsVisitor::visitReadStmt(AslParser::ReadStmtContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any SymbolsVisitor::visitWriteExpr(AslParser::WriteExprContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any SymbolsVisitor::visitWriteString(AslParser::WriteStringContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any SymbolsVisitor::visitLeft_expr(AslParser::Left_exprContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any SymbolsVisitor::visitExprIdent(AslParser::ExprIdentContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any SymbolsVisitor::visitArithmetic(AslParser::ArithmeticContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any SymbolsVisitor::visitRelational(AslParser::RelationalContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any SymbolsVisitor::visitValue(AslParser::ValueContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any SymbolsVisitor::visitIdent(AslParser::IdentContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }


// Getters for the necessary tree node atributes:
//   Scope and Type
SymTable::ScopeId SymbolsVisitor::getScopeDecor(antlr4::ParserRuleContext *ctx) {
  return Decorations.getScope(ctx);
}
TypesMgr::TypeId SymbolsVisitor::getTypeDecor(antlr4::ParserRuleContext *ctx) {
  return Decorations.getType(ctx);
}

// Setters for the necessary tree node attributes:
//   Scope and Type
void SymbolsVisitor::putScopeDecor(antlr4::ParserRuleContext *ctx, SymTable::ScopeId s) {
  Decorations.putScope(ctx, s);
}
void SymbolsVisitor::putTypeDecor(antlr4::ParserRuleContext *ctx, TypesMgr::TypeId t) {
  Decorations.putType(ctx, t);
}
