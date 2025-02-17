
// Generated from Calc.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "CalcVisitor.h"


/**
 * This class provides an empty implementation of CalcVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  CalcBaseVisitor : public CalcVisitor {
public:

  virtual std::any visitProg(CalcParser::ProgContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrintExpr(CalcParser::PrintExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssign(CalcParser::AssignContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlank(CalcParser::BlankContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProd(CalcParser::ProdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMax(CalcParser::MaxContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFactorial(CalcParser::FactorialContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSum(CalcParser::SumContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnary(CalcParser::UnaryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhile(CalcParser::WhileContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInt(CalcParser::IntContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPlus(CalcParser::PlusContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitComparacio(CalcParser::ComparacioContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParentesis(CalcParser::ParentesisContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNot(CalcParser::NotContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMin(CalcParser::MinContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAbs(CalcParser::AbsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCondicional(CalcParser::CondicionalContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPow(CalcParser::PowContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBooleans(CalcParser::BooleansContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitId(CalcParser::IdContext *ctx) override {
    return visitChildren(ctx);
  }


};

