
// Generated from Calc.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "CalcParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by CalcParser.
 */
class  CalcVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by CalcParser.
   */
    virtual std::any visitProg(CalcParser::ProgContext *context) = 0;

    virtual std::any visitPrintExpr(CalcParser::PrintExprContext *context) = 0;

    virtual std::any visitAssign(CalcParser::AssignContext *context) = 0;

    virtual std::any visitBlank(CalcParser::BlankContext *context) = 0;

    virtual std::any visitProd(CalcParser::ProdContext *context) = 0;

    virtual std::any visitMax(CalcParser::MaxContext *context) = 0;

    virtual std::any visitFactorial(CalcParser::FactorialContext *context) = 0;

    virtual std::any visitSum(CalcParser::SumContext *context) = 0;

    virtual std::any visitUnary(CalcParser::UnaryContext *context) = 0;

    virtual std::any visitWhile(CalcParser::WhileContext *context) = 0;

    virtual std::any visitInt(CalcParser::IntContext *context) = 0;

    virtual std::any visitPlus(CalcParser::PlusContext *context) = 0;

    virtual std::any visitComparacio(CalcParser::ComparacioContext *context) = 0;

    virtual std::any visitParentesis(CalcParser::ParentesisContext *context) = 0;

    virtual std::any visitNot(CalcParser::NotContext *context) = 0;

    virtual std::any visitMin(CalcParser::MinContext *context) = 0;

    virtual std::any visitAbs(CalcParser::AbsContext *context) = 0;

    virtual std::any visitCondicional(CalcParser::CondicionalContext *context) = 0;

    virtual std::any visitPow(CalcParser::PowContext *context) = 0;

    virtual std::any visitBooleans(CalcParser::BooleansContext *context) = 0;

    virtual std::any visitId(CalcParser::IdContext *context) = 0;


};

