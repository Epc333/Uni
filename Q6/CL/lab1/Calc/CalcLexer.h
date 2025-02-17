
// Generated from Calc.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  CalcLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, MUL = 11, DIV = 12, MOD = 13, ADD = 14, 
    SUB = 15, FACT = 16, EQUAL = 17, NOT_EQUAL = 18, GREATER_THAN = 19, 
    LESS_THAN = 20, GREATER_OR_EQUAL = 21, LESS_OR_EQUAL = 22, IF = 23, 
    ELSE = 24, THEN = 25, WHILE = 26, AND = 27, OR = 28, NOT = 29, POW = 30, 
    MAX = 31, MIN = 32, ABS = 33, SUM = 34, ID = 35, INT = 36, NEWLINE = 37, 
    WS = 38
  };

  explicit CalcLexer(antlr4::CharStream *input);

  ~CalcLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

