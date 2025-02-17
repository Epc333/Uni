
// Generated from Calc.g4 by ANTLR 4.13.2


#include "CalcVisitor.h"

#include "CalcParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct CalcParserStaticData final {
  CalcParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  CalcParserStaticData(const CalcParserStaticData&) = delete;
  CalcParserStaticData(CalcParserStaticData&&) = delete;
  CalcParserStaticData& operator=(const CalcParserStaticData&) = delete;
  CalcParserStaticData& operator=(CalcParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag calcParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<CalcParserStaticData> calcParserStaticData = nullptr;

void calcParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (calcParserStaticData != nullptr) {
    return;
  }
#else
  assert(calcParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<CalcParserStaticData>(
    std::vector<std::string>{
      "prog", "stat", "expr"
    },
    std::vector<std::string>{
      "", "'='", "'('", "')'", "','", "'['", "'\\u003F'", "':'", "']'", 
      "'{'", "'}'", "'*'", "'/'", "'%'", "'+'", "'-'", "'!'", "'=='", "'!='", 
      "'>'", "'<'", "'>='", "'<='", "'if'", "'else'", "'then'", "'while'", 
      "'and'", "'or'", "'not'", "'pow'", "'max'", "'min'", "'abs'", "'sum'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "MUL", "DIV", "MOD", "ADD", 
      "SUB", "FACT", "EQUAL", "NOT_EQUAL", "GREATER_THAN", "LESS_THAN", 
      "GREATER_OR_EQUAL", "LESS_OR_EQUAL", "IF", "ELSE", "THEN", "WHILE", 
      "AND", "OR", "NOT", "POW", "MAX", "MIN", "ABS", "SUM", "ID", "INT", 
      "NEWLINE", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,38,123,2,0,7,0,2,1,7,1,2,2,7,2,1,0,4,0,8,8,0,11,0,12,0,9,1,0,1,0,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,23,8,1,1,2,1,2,1,2,1,2,1,2,1,
  	2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,5,2,46,
  	8,2,10,2,12,2,49,9,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,5,2,58,8,2,10,2,12,2,
  	61,9,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,5,2,70,8,2,10,2,12,2,73,9,2,1,2,1,
  	2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,
  	4,2,94,8,2,11,2,12,2,95,1,2,1,2,1,2,1,2,3,2,102,8,2,1,2,1,2,1,2,1,2,1,
  	2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,5,2,118,8,2,10,2,12,2,121,9,2,1,
  	2,0,1,4,3,0,2,4,0,4,1,0,11,13,1,0,14,15,1,0,17,22,1,0,27,28,142,0,7,1,
  	0,0,0,2,22,1,0,0,0,4,101,1,0,0,0,6,8,3,2,1,0,7,6,1,0,0,0,8,9,1,0,0,0,
  	9,7,1,0,0,0,9,10,1,0,0,0,10,11,1,0,0,0,11,12,5,0,0,1,12,1,1,0,0,0,13,
  	14,3,4,2,0,14,15,5,37,0,0,15,23,1,0,0,0,16,17,5,35,0,0,17,18,5,1,0,0,
  	18,19,3,4,2,0,19,20,5,37,0,0,20,23,1,0,0,0,21,23,5,37,0,0,22,13,1,0,0,
  	0,22,16,1,0,0,0,22,21,1,0,0,0,23,3,1,0,0,0,24,25,6,2,-1,0,25,26,5,15,
  	0,0,26,102,3,4,2,17,27,28,5,2,0,0,28,29,3,4,2,0,29,30,5,3,0,0,30,102,
  	1,0,0,0,31,32,5,29,0,0,32,102,3,4,2,11,33,34,5,30,0,0,34,35,5,2,0,0,35,
  	36,3,4,2,0,36,37,5,4,0,0,37,38,3,4,2,0,38,39,5,3,0,0,39,102,1,0,0,0,40,
  	41,5,31,0,0,41,42,5,2,0,0,42,47,3,4,2,0,43,44,5,4,0,0,44,46,3,4,2,0,45,
  	43,1,0,0,0,46,49,1,0,0,0,47,45,1,0,0,0,47,48,1,0,0,0,48,50,1,0,0,0,49,
  	47,1,0,0,0,50,51,5,3,0,0,51,102,1,0,0,0,52,53,5,32,0,0,53,54,5,2,0,0,
  	54,59,3,4,2,0,55,56,5,4,0,0,56,58,3,4,2,0,57,55,1,0,0,0,58,61,1,0,0,0,
  	59,57,1,0,0,0,59,60,1,0,0,0,60,62,1,0,0,0,61,59,1,0,0,0,62,63,5,3,0,0,
  	63,102,1,0,0,0,64,65,5,34,0,0,65,66,5,2,0,0,66,71,3,4,2,0,67,68,5,4,0,
  	0,68,70,3,4,2,0,69,67,1,0,0,0,70,73,1,0,0,0,71,69,1,0,0,0,71,72,1,0,0,
  	0,72,74,1,0,0,0,73,71,1,0,0,0,74,75,5,3,0,0,75,102,1,0,0,0,76,77,5,33,
  	0,0,77,78,5,2,0,0,78,79,3,4,2,0,79,80,5,3,0,0,80,102,1,0,0,0,81,82,5,
  	5,0,0,82,83,3,4,2,0,83,84,5,6,0,0,84,85,3,4,2,0,85,86,5,7,0,0,86,87,3,
  	4,2,0,87,88,5,8,0,0,88,102,1,0,0,0,89,90,5,26,0,0,90,91,3,4,2,0,91,93,
  	5,9,0,0,92,94,3,4,2,0,93,92,1,0,0,0,94,95,1,0,0,0,95,93,1,0,0,0,95,96,
  	1,0,0,0,96,97,1,0,0,0,97,98,5,10,0,0,98,102,1,0,0,0,99,102,5,36,0,0,100,
  	102,5,35,0,0,101,24,1,0,0,0,101,27,1,0,0,0,101,31,1,0,0,0,101,33,1,0,
  	0,0,101,40,1,0,0,0,101,52,1,0,0,0,101,64,1,0,0,0,101,76,1,0,0,0,101,81,
  	1,0,0,0,101,89,1,0,0,0,101,99,1,0,0,0,101,100,1,0,0,0,102,119,1,0,0,0,
  	103,104,10,14,0,0,104,105,7,0,0,0,105,118,3,4,2,15,106,107,10,13,0,0,
  	107,108,7,1,0,0,108,118,3,4,2,14,109,110,10,12,0,0,110,111,7,2,0,0,111,
  	118,3,4,2,13,112,113,10,10,0,0,113,114,7,3,0,0,114,118,3,4,2,11,115,116,
  	10,15,0,0,116,118,5,16,0,0,117,103,1,0,0,0,117,106,1,0,0,0,117,109,1,
  	0,0,0,117,112,1,0,0,0,117,115,1,0,0,0,118,121,1,0,0,0,119,117,1,0,0,0,
  	119,120,1,0,0,0,120,5,1,0,0,0,121,119,1,0,0,0,9,9,22,47,59,71,95,101,
  	117,119
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  calcParserStaticData = std::move(staticData);
}

}

CalcParser::CalcParser(TokenStream *input) : CalcParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

CalcParser::CalcParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  CalcParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *calcParserStaticData->atn, calcParserStaticData->decisionToDFA, calcParserStaticData->sharedContextCache, options);
}

CalcParser::~CalcParser() {
  delete _interpreter;
}

const atn::ATN& CalcParser::getATN() const {
  return *calcParserStaticData->atn;
}

std::string CalcParser::getGrammarFileName() const {
  return "Calc.g4";
}

const std::vector<std::string>& CalcParser::getRuleNames() const {
  return calcParserStaticData->ruleNames;
}

const dfa::Vocabulary& CalcParser::getVocabulary() const {
  return calcParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView CalcParser::getSerializedATN() const {
  return calcParserStaticData->serializedATN;
}


//----------------- ProgContext ------------------------------------------------------------------

CalcParser::ProgContext::ProgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CalcParser::ProgContext::EOF() {
  return getToken(CalcParser::EOF, 0);
}

std::vector<CalcParser::StatContext *> CalcParser::ProgContext::stat() {
  return getRuleContexts<CalcParser::StatContext>();
}

CalcParser::StatContext* CalcParser::ProgContext::stat(size_t i) {
  return getRuleContext<CalcParser::StatContext>(i);
}


size_t CalcParser::ProgContext::getRuleIndex() const {
  return CalcParser::RuleProg;
}


std::any CalcParser::ProgContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitProg(this);
  else
    return visitor->visitChildren(this);
}

CalcParser::ProgContext* CalcParser::prog() {
  ProgContext *_localctx = _tracker.createInstance<ProgContext>(_ctx, getState());
  enterRule(_localctx, 0, CalcParser::RuleProg);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(7); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(6);
      stat();
      setState(9); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 274408177700) != 0));
    setState(11);
    match(CalcParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatContext ------------------------------------------------------------------

CalcParser::StatContext::StatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CalcParser::StatContext::getRuleIndex() const {
  return CalcParser::RuleStat;
}

void CalcParser::StatContext::copyFrom(StatContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- BlankContext ------------------------------------------------------------------

tree::TerminalNode* CalcParser::BlankContext::NEWLINE() {
  return getToken(CalcParser::NEWLINE, 0);
}

CalcParser::BlankContext::BlankContext(StatContext *ctx) { copyFrom(ctx); }


std::any CalcParser::BlankContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitBlank(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PrintExprContext ------------------------------------------------------------------

CalcParser::ExprContext* CalcParser::PrintExprContext::expr() {
  return getRuleContext<CalcParser::ExprContext>(0);
}

tree::TerminalNode* CalcParser::PrintExprContext::NEWLINE() {
  return getToken(CalcParser::NEWLINE, 0);
}

CalcParser::PrintExprContext::PrintExprContext(StatContext *ctx) { copyFrom(ctx); }


std::any CalcParser::PrintExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitPrintExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AssignContext ------------------------------------------------------------------

tree::TerminalNode* CalcParser::AssignContext::ID() {
  return getToken(CalcParser::ID, 0);
}

CalcParser::ExprContext* CalcParser::AssignContext::expr() {
  return getRuleContext<CalcParser::ExprContext>(0);
}

tree::TerminalNode* CalcParser::AssignContext::NEWLINE() {
  return getToken(CalcParser::NEWLINE, 0);
}

CalcParser::AssignContext::AssignContext(StatContext *ctx) { copyFrom(ctx); }


std::any CalcParser::AssignContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitAssign(this);
  else
    return visitor->visitChildren(this);
}
CalcParser::StatContext* CalcParser::stat() {
  StatContext *_localctx = _tracker.createInstance<StatContext>(_ctx, getState());
  enterRule(_localctx, 2, CalcParser::RuleStat);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(22);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<CalcParser::PrintExprContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(13);
      expr(0);
      setState(14);
      match(CalcParser::NEWLINE);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<CalcParser::AssignContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(16);
      match(CalcParser::ID);
      setState(17);
      match(CalcParser::T__0);
      setState(18);
      expr(0);
      setState(19);
      match(CalcParser::NEWLINE);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<CalcParser::BlankContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(21);
      match(CalcParser::NEWLINE);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

CalcParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CalcParser::ExprContext::getRuleIndex() const {
  return CalcParser::RuleExpr;
}

void CalcParser::ExprContext::copyFrom(ExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ProdContext ------------------------------------------------------------------

std::vector<CalcParser::ExprContext *> CalcParser::ProdContext::expr() {
  return getRuleContexts<CalcParser::ExprContext>();
}

CalcParser::ExprContext* CalcParser::ProdContext::expr(size_t i) {
  return getRuleContext<CalcParser::ExprContext>(i);
}

tree::TerminalNode* CalcParser::ProdContext::MUL() {
  return getToken(CalcParser::MUL, 0);
}

tree::TerminalNode* CalcParser::ProdContext::DIV() {
  return getToken(CalcParser::DIV, 0);
}

tree::TerminalNode* CalcParser::ProdContext::MOD() {
  return getToken(CalcParser::MOD, 0);
}

CalcParser::ProdContext::ProdContext(ExprContext *ctx) { copyFrom(ctx); }


std::any CalcParser::ProdContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitProd(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MaxContext ------------------------------------------------------------------

tree::TerminalNode* CalcParser::MaxContext::MAX() {
  return getToken(CalcParser::MAX, 0);
}

std::vector<CalcParser::ExprContext *> CalcParser::MaxContext::expr() {
  return getRuleContexts<CalcParser::ExprContext>();
}

CalcParser::ExprContext* CalcParser::MaxContext::expr(size_t i) {
  return getRuleContext<CalcParser::ExprContext>(i);
}

CalcParser::MaxContext::MaxContext(ExprContext *ctx) { copyFrom(ctx); }


std::any CalcParser::MaxContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitMax(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FactorialContext ------------------------------------------------------------------

CalcParser::ExprContext* CalcParser::FactorialContext::expr() {
  return getRuleContext<CalcParser::ExprContext>(0);
}

tree::TerminalNode* CalcParser::FactorialContext::FACT() {
  return getToken(CalcParser::FACT, 0);
}

CalcParser::FactorialContext::FactorialContext(ExprContext *ctx) { copyFrom(ctx); }


std::any CalcParser::FactorialContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitFactorial(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SumContext ------------------------------------------------------------------

tree::TerminalNode* CalcParser::SumContext::SUM() {
  return getToken(CalcParser::SUM, 0);
}

std::vector<CalcParser::ExprContext *> CalcParser::SumContext::expr() {
  return getRuleContexts<CalcParser::ExprContext>();
}

CalcParser::ExprContext* CalcParser::SumContext::expr(size_t i) {
  return getRuleContext<CalcParser::ExprContext>(i);
}

CalcParser::SumContext::SumContext(ExprContext *ctx) { copyFrom(ctx); }


std::any CalcParser::SumContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitSum(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UnaryContext ------------------------------------------------------------------

tree::TerminalNode* CalcParser::UnaryContext::SUB() {
  return getToken(CalcParser::SUB, 0);
}

CalcParser::ExprContext* CalcParser::UnaryContext::expr() {
  return getRuleContext<CalcParser::ExprContext>(0);
}

CalcParser::UnaryContext::UnaryContext(ExprContext *ctx) { copyFrom(ctx); }


std::any CalcParser::UnaryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitUnary(this);
  else
    return visitor->visitChildren(this);
}
//----------------- WhileContext ------------------------------------------------------------------

tree::TerminalNode* CalcParser::WhileContext::WHILE() {
  return getToken(CalcParser::WHILE, 0);
}

std::vector<CalcParser::ExprContext *> CalcParser::WhileContext::expr() {
  return getRuleContexts<CalcParser::ExprContext>();
}

CalcParser::ExprContext* CalcParser::WhileContext::expr(size_t i) {
  return getRuleContext<CalcParser::ExprContext>(i);
}

CalcParser::WhileContext::WhileContext(ExprContext *ctx) { copyFrom(ctx); }


std::any CalcParser::WhileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitWhile(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IntContext ------------------------------------------------------------------

tree::TerminalNode* CalcParser::IntContext::INT() {
  return getToken(CalcParser::INT, 0);
}

CalcParser::IntContext::IntContext(ExprContext *ctx) { copyFrom(ctx); }


std::any CalcParser::IntContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitInt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PlusContext ------------------------------------------------------------------

std::vector<CalcParser::ExprContext *> CalcParser::PlusContext::expr() {
  return getRuleContexts<CalcParser::ExprContext>();
}

CalcParser::ExprContext* CalcParser::PlusContext::expr(size_t i) {
  return getRuleContext<CalcParser::ExprContext>(i);
}

tree::TerminalNode* CalcParser::PlusContext::ADD() {
  return getToken(CalcParser::ADD, 0);
}

tree::TerminalNode* CalcParser::PlusContext::SUB() {
  return getToken(CalcParser::SUB, 0);
}

CalcParser::PlusContext::PlusContext(ExprContext *ctx) { copyFrom(ctx); }


std::any CalcParser::PlusContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitPlus(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ComparacioContext ------------------------------------------------------------------

std::vector<CalcParser::ExprContext *> CalcParser::ComparacioContext::expr() {
  return getRuleContexts<CalcParser::ExprContext>();
}

CalcParser::ExprContext* CalcParser::ComparacioContext::expr(size_t i) {
  return getRuleContext<CalcParser::ExprContext>(i);
}

tree::TerminalNode* CalcParser::ComparacioContext::EQUAL() {
  return getToken(CalcParser::EQUAL, 0);
}

tree::TerminalNode* CalcParser::ComparacioContext::NOT_EQUAL() {
  return getToken(CalcParser::NOT_EQUAL, 0);
}

tree::TerminalNode* CalcParser::ComparacioContext::GREATER_THAN() {
  return getToken(CalcParser::GREATER_THAN, 0);
}

tree::TerminalNode* CalcParser::ComparacioContext::GREATER_OR_EQUAL() {
  return getToken(CalcParser::GREATER_OR_EQUAL, 0);
}

tree::TerminalNode* CalcParser::ComparacioContext::LESS_OR_EQUAL() {
  return getToken(CalcParser::LESS_OR_EQUAL, 0);
}

tree::TerminalNode* CalcParser::ComparacioContext::LESS_THAN() {
  return getToken(CalcParser::LESS_THAN, 0);
}

CalcParser::ComparacioContext::ComparacioContext(ExprContext *ctx) { copyFrom(ctx); }


std::any CalcParser::ComparacioContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitComparacio(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ParentesisContext ------------------------------------------------------------------

CalcParser::ExprContext* CalcParser::ParentesisContext::expr() {
  return getRuleContext<CalcParser::ExprContext>(0);
}

CalcParser::ParentesisContext::ParentesisContext(ExprContext *ctx) { copyFrom(ctx); }


std::any CalcParser::ParentesisContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitParentesis(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NotContext ------------------------------------------------------------------

tree::TerminalNode* CalcParser::NotContext::NOT() {
  return getToken(CalcParser::NOT, 0);
}

CalcParser::ExprContext* CalcParser::NotContext::expr() {
  return getRuleContext<CalcParser::ExprContext>(0);
}

CalcParser::NotContext::NotContext(ExprContext *ctx) { copyFrom(ctx); }


std::any CalcParser::NotContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitNot(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MinContext ------------------------------------------------------------------

tree::TerminalNode* CalcParser::MinContext::MIN() {
  return getToken(CalcParser::MIN, 0);
}

std::vector<CalcParser::ExprContext *> CalcParser::MinContext::expr() {
  return getRuleContexts<CalcParser::ExprContext>();
}

CalcParser::ExprContext* CalcParser::MinContext::expr(size_t i) {
  return getRuleContext<CalcParser::ExprContext>(i);
}

CalcParser::MinContext::MinContext(ExprContext *ctx) { copyFrom(ctx); }


std::any CalcParser::MinContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitMin(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AbsContext ------------------------------------------------------------------

tree::TerminalNode* CalcParser::AbsContext::ABS() {
  return getToken(CalcParser::ABS, 0);
}

CalcParser::ExprContext* CalcParser::AbsContext::expr() {
  return getRuleContext<CalcParser::ExprContext>(0);
}

CalcParser::AbsContext::AbsContext(ExprContext *ctx) { copyFrom(ctx); }


std::any CalcParser::AbsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitAbs(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CondicionalContext ------------------------------------------------------------------

std::vector<CalcParser::ExprContext *> CalcParser::CondicionalContext::expr() {
  return getRuleContexts<CalcParser::ExprContext>();
}

CalcParser::ExprContext* CalcParser::CondicionalContext::expr(size_t i) {
  return getRuleContext<CalcParser::ExprContext>(i);
}

CalcParser::CondicionalContext::CondicionalContext(ExprContext *ctx) { copyFrom(ctx); }


std::any CalcParser::CondicionalContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitCondicional(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PowContext ------------------------------------------------------------------

tree::TerminalNode* CalcParser::PowContext::POW() {
  return getToken(CalcParser::POW, 0);
}

std::vector<CalcParser::ExprContext *> CalcParser::PowContext::expr() {
  return getRuleContexts<CalcParser::ExprContext>();
}

CalcParser::ExprContext* CalcParser::PowContext::expr(size_t i) {
  return getRuleContext<CalcParser::ExprContext>(i);
}

CalcParser::PowContext::PowContext(ExprContext *ctx) { copyFrom(ctx); }


std::any CalcParser::PowContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitPow(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BooleansContext ------------------------------------------------------------------

std::vector<CalcParser::ExprContext *> CalcParser::BooleansContext::expr() {
  return getRuleContexts<CalcParser::ExprContext>();
}

CalcParser::ExprContext* CalcParser::BooleansContext::expr(size_t i) {
  return getRuleContext<CalcParser::ExprContext>(i);
}

tree::TerminalNode* CalcParser::BooleansContext::AND() {
  return getToken(CalcParser::AND, 0);
}

tree::TerminalNode* CalcParser::BooleansContext::OR() {
  return getToken(CalcParser::OR, 0);
}

CalcParser::BooleansContext::BooleansContext(ExprContext *ctx) { copyFrom(ctx); }


std::any CalcParser::BooleansContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitBooleans(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IdContext ------------------------------------------------------------------

tree::TerminalNode* CalcParser::IdContext::ID() {
  return getToken(CalcParser::ID, 0);
}

CalcParser::IdContext::IdContext(ExprContext *ctx) { copyFrom(ctx); }


std::any CalcParser::IdContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitId(this);
  else
    return visitor->visitChildren(this);
}

CalcParser::ExprContext* CalcParser::expr() {
   return expr(0);
}

CalcParser::ExprContext* CalcParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CalcParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  CalcParser::ExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 4;
  enterRecursionRule(_localctx, 4, CalcParser::RuleExpr, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(101);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CalcParser::SUB: {
        _localctx = _tracker.createInstance<UnaryContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(25);
        match(CalcParser::SUB);
        setState(26);
        expr(17);
        break;
      }

      case CalcParser::T__1: {
        _localctx = _tracker.createInstance<ParentesisContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(27);
        match(CalcParser::T__1);
        setState(28);
        expr(0);
        setState(29);
        match(CalcParser::T__2);
        break;
      }

      case CalcParser::NOT: {
        _localctx = _tracker.createInstance<NotContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(31);
        match(CalcParser::NOT);
        setState(32);
        expr(11);
        break;
      }

      case CalcParser::POW: {
        _localctx = _tracker.createInstance<PowContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(33);
        match(CalcParser::POW);
        setState(34);
        match(CalcParser::T__1);
        setState(35);
        expr(0);
        setState(36);
        match(CalcParser::T__3);
        setState(37);
        expr(0);
        setState(38);
        match(CalcParser::T__2);
        break;
      }

      case CalcParser::MAX: {
        _localctx = _tracker.createInstance<MaxContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(40);
        match(CalcParser::MAX);
        setState(41);
        match(CalcParser::T__1);
        setState(42);
        expr(0);
        setState(47);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == CalcParser::T__3) {
          setState(43);
          match(CalcParser::T__3);
          setState(44);
          expr(0);
          setState(49);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(50);
        match(CalcParser::T__2);
        break;
      }

      case CalcParser::MIN: {
        _localctx = _tracker.createInstance<MinContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(52);
        match(CalcParser::MIN);
        setState(53);
        match(CalcParser::T__1);
        setState(54);
        expr(0);
        setState(59);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == CalcParser::T__3) {
          setState(55);
          match(CalcParser::T__3);
          setState(56);
          expr(0);
          setState(61);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(62);
        match(CalcParser::T__2);
        break;
      }

      case CalcParser::SUM: {
        _localctx = _tracker.createInstance<SumContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(64);
        match(CalcParser::SUM);
        setState(65);
        match(CalcParser::T__1);
        setState(66);
        expr(0);
        setState(71);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == CalcParser::T__3) {
          setState(67);
          match(CalcParser::T__3);
          setState(68);
          expr(0);
          setState(73);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(74);
        match(CalcParser::T__2);
        break;
      }

      case CalcParser::ABS: {
        _localctx = _tracker.createInstance<AbsContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(76);
        match(CalcParser::ABS);
        setState(77);
        match(CalcParser::T__1);
        setState(78);
        expr(0);
        setState(79);
        match(CalcParser::T__2);
        break;
      }

      case CalcParser::T__4: {
        _localctx = _tracker.createInstance<CondicionalContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(81);
        match(CalcParser::T__4);
        setState(82);
        expr(0);
        setState(83);
        match(CalcParser::T__5);
        setState(84);
        expr(0);
        setState(85);
        match(CalcParser::T__6);
        setState(86);
        expr(0);
        setState(87);
        match(CalcParser::T__7);
        break;
      }

      case CalcParser::WHILE: {
        _localctx = _tracker.createInstance<WhileContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(89);
        match(CalcParser::WHILE);
        setState(90);
        expr(0);
        setState(91);
        match(CalcParser::T__8);
        setState(93); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(92);
          expr(0);
          setState(95); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 136969224228) != 0));
        setState(97);
        match(CalcParser::T__9);
        break;
      }

      case CalcParser::INT: {
        _localctx = _tracker.createInstance<IntContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(99);
        match(CalcParser::INT);
        break;
      }

      case CalcParser::ID: {
        _localctx = _tracker.createInstance<IdContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(100);
        match(CalcParser::ID);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(119);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(117);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<ProdContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(103);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(104);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 14336) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(105);
          expr(15);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<PlusContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(106);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(107);
          _la = _input->LA(1);
          if (!(_la == CalcParser::ADD

          || _la == CalcParser::SUB)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(108);
          expr(14);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<ComparacioContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(109);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(110);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 8257536) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(111);
          expr(13);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<BooleansContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(112);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(113);
          _la = _input->LA(1);
          if (!(_la == CalcParser::AND

          || _la == CalcParser::OR)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(114);
          expr(11);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<FactorialContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(115);

          if (!(precpred(_ctx, 15))) throw FailedPredicateException(this, "precpred(_ctx, 15)");
          setState(116);
          match(CalcParser::FACT);
          break;
        }

        default:
          break;
        } 
      }
      setState(121);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

bool CalcParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 2: return exprSempred(antlrcpp::downCast<ExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool CalcParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 14);
    case 1: return precpred(_ctx, 13);
    case 2: return precpred(_ctx, 12);
    case 3: return precpred(_ctx, 10);
    case 4: return precpred(_ctx, 15);

  default:
    break;
  }
  return true;
}

void CalcParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  calcParserInitialize();
#else
  ::antlr4::internal::call_once(calcParserOnceFlag, calcParserInitialize);
#endif
}
