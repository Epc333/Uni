
// Generated from Asl.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  AslLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, ASSIGN = 6, EQUAL = 7, 
    NE = 8, GT = 9, GE = 10, LT = 11, LE = 12, TRUE = 13, FALSE = 14, PLUS = 15, 
    MUL = 16, MINUS = 17, DIV = 18, MOD = 19, AND = 20, OR = 21, NOT = 22, 
    VAR = 23, INT = 24, FLOAT = 25, BOOL = 26, CHAR = 27, IF = 28, THEN = 29, 
    ELSE = 30, ENDIF = 31, FUNC = 32, ENDFUNC = 33, READ = 34, WRITE = 35, 
    ID = 36, INTVAL = 37, FLOATVAL = 38, CHARVAL = 39, STRING = 40, COMMENT = 41, 
    WS = 42
  };

  explicit AslLexer(antlr4::CharStream *input);

  ~AslLexer() override;


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

