
#include "antlr4-runtime.h"
#include "CalcLexer.h"
#include "CalcParser.h"
#include "CalcBaseVisitor.h"

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cstdio>     // fopen
#include <cstdlib>    // EXIT_FAILURE, EXIT_SUCCESS
#include <cmath>      

// using namespace std;
// using namespace antlr4;
// using namespace antlrcpp;


//////////////////////////////////////////////////////////////////////
// Sample "calculator" (implemented with a visitor)
class Calculator : public CalcBaseVisitor {
public:
  // "memory" for the calculator; variable/value pairs go here
  std::map<std::string, int> memory;

  // stat : expr NEWLINE
  std::any visitPrintExpr(CalcParser::PrintExprContext *ctx) {
    int value = std::any_cast<int>(visit(ctx->expr()));  // evaluate the expr child
    std::cout << value << std::endl;                     // print the result
    return 0;                                            // return dummy value
  }

  // stat : ID '=' expr NEWLINE
  std::any visitAssign(CalcParser::AssignContext *ctx) {
    std::string id = ctx->ID()->getText();               // id is left-hand side of '='
    int value = std::any_cast<int>(visit(ctx->expr()));  // compute value of expression on right
    memory[id] = value;                                  // store it in the memory
    return 0;                                            // return dummy value
  }

  // expr : '(' expr ')'          # parentesis
  std::any visitParentesis(CalcParser::ParentesisContext *ctx){
    int value = std::any_cast<int>(visit(ctx->expr()));
    return value;
  }

  // expr : expr FACT             # factorial
  std::any visitFactorial(CalcParser::FactorialContext *ctx){
    int value = std::any_cast<int>(visit(ctx->expr()));
    int fact = 1;
    for (int i = 1; i <= value; i++) fact *= i;
    return fact;
  }

  // expr: SUB expr # unary
  std::any visitUnary(CalcParser::UnaryContext *ctx){
    int value = std::any_cast<int>(visit(ctx->expr())); 
    return -value;
  }

  // expr : expr (MUL|DIV|MOD) expr   # prod
  std::any visitProd(CalcParser::ProdContext *ctx) {
    int left = std::any_cast<int>(visit(ctx->expr(0)));   // get value of left subexpression
    int right = std::any_cast<int>(visit(ctx->expr(1)));  // get value of right subexpression
    if (ctx->MUL()) return left*right;
    else if (ctx->DIV()) return left/right;
    else return left%right;
  }
  
  // expr : expr (ADD|SUB) expr
  std::any visitPlus(CalcParser::PlusContext *ctx) {
    int left = std::any_cast<int>(visit(ctx->expr(0)));   // get value of left subexpression
    int right = std::any_cast<int>(visit(ctx->expr(1)));  // get value of right subexpression
    if (ctx->ADD()) return left+right;
    else return left-right;
  }

  // expr : expr (COMP) expr      # comparacio
  std::any visitComparacio(CalcParser::ComparacioContext *ctx){
    int left = std::any_cast<int>(visit(ctx->expr(0)));   // get value of left subexpression
    int right = std::any_cast<int>(visit(ctx->expr(1)));
    bool comp;  // get value of right subexpression
    if (ctx->EQUAL()) comp = left == right;
    else if (ctx->NOT_EQUAL()) comp = left != right;
    else if (ctx->GREATER_THAN()) comp = left > right;
    else if (ctx->LESS_THAN()) comp = left < right;
    else if (ctx->GREATER_OR_EQUAL()) comp = left >= right;
    else if (ctx->LESS_OR_EQUAL()) comp = left <= right;
    return static_cast<int>(comp);
  }

  // expr : NOT expr              # not
  std::any visitNot(CalcParser::NotContext *ctx){
    int value = std::any_cast<int>(visit(ctx->expr()));
    if (value == 0) return 1;
    else return 0;
  }

  // expr : expr (AND|OR) expr   # booleans
  std::any visitBooleans(CalcParser::BooleansContext *ctx){
    int left = std::any_cast<int>(visit(ctx->expr(0)));   // get value of left subexpression
    int right = std::any_cast<int>(visit(ctx->expr(1)));  // get value of right subexpression
    if (ctx->AND()) return left & right;
    else return left | right;
  }

  // expr : POW '(' expr ',' expr ')'   #pow
  std::any visitPow(CalcParser::PowContext *ctx){
    int base = std::any_cast<int>(visit(ctx->expr(0)));
    int exp = std::any_cast<int>(visit(ctx->expr(1)));
    return static_cast<int>(pow(base, exp));
  }

  // expr : MAX '(' expr ( ',' expr )* ')'   #max
  std::any visitMax(CalcParser::MaxContext *ctx){
    int m = std::any_cast<int>(visit(ctx->expr(0)));
    for (uint i = 1; i < ctx->expr().size(); i++){
      int value = std::any_cast<int>(visit(ctx->expr(i)));
      if (value > m) m = value;
    }
    return m;
  }

  // expr : MIN '(' expr ( ',' expr )* ')'   #min
  std::any visitMin(CalcParser::MinContext *ctx){
    int m = std::any_cast<int>(visit(ctx->expr(0)));
    for (uint i = 1; i < ctx->expr().size(); i++){
      int value = std::any_cast<int>(visit(ctx->expr(i)));
      if (value < m) m = value;
    }
    return m;
  }

  // expr : SUM '(' expr ( ',' expr )* ')'   #sum
  std::any visitSum(CalcParser::SumContext *ctx){
    int sum = std::any_cast<int>(visit(ctx->expr(0)));
    for (uint i = 1; i < ctx->expr().size(); i++){
      sum += std::any_cast<int>(visit(ctx->expr(i)));
    }
    return sum;
  }

  // expr : ABS '(' expr ')'   #abs
  std::any visitAbs(CalcParser::AbsContext *ctx){
    int value = std::any_cast<int>(visit(ctx->expr()));
    if (value < 0) return -value;
    return value;
  }
  
  // expr : '[' expr '?' expr ':' expr ']'   #condicional
  std::any visitCondicional(CalcParser::CondicionalContext *ctx){
    int cond = std::any_cast<int>(visit(ctx->expr(0)));
    if (cond) return std::any_cast<int>(visit(ctx->expr(1)));
    return std::any_cast<int>(visit(ctx->expr(2)));
  }
  
  
  // expr : WHILE expr '{' expr+ '}'  #while
  std::any visitWhile(CalcParser::WhileContext *ctx){
    int value = 0;
    while (std::any_cast<int>(visit(ctx->expr(0)))){
      for (uint i = 1; i < ctx->expr().size(); i++){
        value = std::any_cast<int>(visit(ctx->expr(i)));
      }
    }
    return value;
  }

  // expr : INT
  std::any visitInt(CalcParser::IntContext *ctx) {
    return std::stoi(ctx->INT()->getText());       // or: ctx->getText()
  }
  
  // expr : ID
  std::any visitId(CalcParser::IdContext *ctx) {
    std::string id = ctx->ID()->getText();         // or: ctx->getText()
    if (memory.find(id) != memory.end()) return memory[id];
    return 0;
  }
  
};
// Sample "calculator" (implemented with a visitor)
//////////////////////////////////////////////////////////////////////


int main(int argc, const char* argv[]) {
  // check the correct use of the program
  if (argc > 2) {
    std::cout << "Usage: ./main [<file>]" << std::endl;
    return EXIT_FAILURE;
  }
  if (argc == 2 and not std::fopen(argv[1], "r")) {
    std::cout << "No such file: " << argv[1] << std::endl;
    return EXIT_FAILURE;
  }

  // open input file (or std::cin) and create a character stream
  antlr4::ANTLRInputStream input;
  if (argc == 2) {  // reads from <file>
    std::ifstream stream;
    stream.open(argv[1]);
    input = antlr4::ANTLRInputStream(stream);
  }
  else {            // reads fron std::cin
    input = antlr4::ANTLRInputStream(std::cin);
  }

  // create a lexer that consumes the character stream and produce a token stream
  CalcLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);

  // create a parser that consumes the token stream, and parses it.
  CalcParser parser(&tokens);

  // call the parser and get the parse tree. prog is the initial rule
  antlr4::tree::ParseTree *tree = parser.prog();

  // check for lexical or syntactical errors
  if (lexer.getNumberOfSyntaxErrors() > 0 or
      parser.getNumberOfSyntaxErrors() > 0) {
    std::cout << "Lexical and/or syntactical errors have been found." << std::endl;
    return EXIT_FAILURE;
  }
  
  // print the parse tree (for debugging purposes)
  std::cout << tree->toStringTree(&parser) << std::endl;

  ////////////////////////////////////////////////////////////////////

  // Create a visitor that will execute the statements
  Calculator calc;

  // Traverse the tree using this Calculator visitor
  calc.visit(tree);

  return EXIT_SUCCESS;
}
