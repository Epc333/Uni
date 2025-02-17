
// Generated from Calc.g4 by ANTLR 4.13.2


#include "CalcLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct CalcLexerStaticData final {
  CalcLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  CalcLexerStaticData(const CalcLexerStaticData&) = delete;
  CalcLexerStaticData(CalcLexerStaticData&&) = delete;
  CalcLexerStaticData& operator=(const CalcLexerStaticData&) = delete;
  CalcLexerStaticData& operator=(CalcLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag calclexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<CalcLexerStaticData> calclexerLexerStaticData = nullptr;

void calclexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (calclexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(calclexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<CalcLexerStaticData>(
    std::vector<std::string>{
      "T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "T__8", 
      "T__9", "MUL", "DIV", "MOD", "ADD", "SUB", "FACT", "EQUAL", "NOT_EQUAL", 
      "GREATER_THAN", "LESS_THAN", "GREATER_OR_EQUAL", "LESS_OR_EQUAL", 
      "IF", "ELSE", "THEN", "WHILE", "AND", "OR", "NOT", "POW", "MAX", "MIN", 
      "ABS", "SUM", "ID", "INT", "NEWLINE", "WS"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
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
  	4,0,38,197,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,
  	7,28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,
  	7,35,2,36,7,36,2,37,7,37,1,0,1,0,1,1,1,1,1,2,1,2,1,3,1,3,1,4,1,4,1,5,
  	1,5,1,6,1,6,1,7,1,7,1,8,1,8,1,9,1,9,1,10,1,10,1,11,1,11,1,12,1,12,1,13,
  	1,13,1,14,1,14,1,15,1,15,1,16,1,16,1,16,1,17,1,17,1,17,1,18,1,18,1,19,
  	1,19,1,20,1,20,1,20,1,21,1,21,1,21,1,22,1,22,1,22,1,23,1,23,1,23,1,23,
  	1,23,1,24,1,24,1,24,1,24,1,24,1,25,1,25,1,25,1,25,1,25,1,25,1,26,1,26,
  	1,26,1,26,1,27,1,27,1,27,1,28,1,28,1,28,1,28,1,29,1,29,1,29,1,29,1,30,
  	1,30,1,30,1,30,1,31,1,31,1,31,1,31,1,32,1,32,1,32,1,32,1,33,1,33,1,33,
  	1,33,1,34,4,34,177,8,34,11,34,12,34,178,1,35,4,35,182,8,35,11,35,12,35,
  	183,1,36,3,36,187,8,36,1,36,1,36,1,37,4,37,192,8,37,11,37,12,37,193,1,
  	37,1,37,0,0,38,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,23,
  	12,25,13,27,14,29,15,31,16,33,17,35,18,37,19,39,20,41,21,43,22,45,23,
  	47,24,49,25,51,26,53,27,55,28,57,29,59,30,61,31,63,32,65,33,67,34,69,
  	35,71,36,73,37,75,38,1,0,3,2,0,65,90,97,122,1,0,48,57,2,0,9,9,32,32,200,
  	0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,
  	0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,0,0,
  	0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,0,0,0,0,31,1,0,0,0,0,33,
  	1,0,0,0,0,35,1,0,0,0,0,37,1,0,0,0,0,39,1,0,0,0,0,41,1,0,0,0,0,43,1,0,
  	0,0,0,45,1,0,0,0,0,47,1,0,0,0,0,49,1,0,0,0,0,51,1,0,0,0,0,53,1,0,0,0,
  	0,55,1,0,0,0,0,57,1,0,0,0,0,59,1,0,0,0,0,61,1,0,0,0,0,63,1,0,0,0,0,65,
  	1,0,0,0,0,67,1,0,0,0,0,69,1,0,0,0,0,71,1,0,0,0,0,73,1,0,0,0,0,75,1,0,
  	0,0,1,77,1,0,0,0,3,79,1,0,0,0,5,81,1,0,0,0,7,83,1,0,0,0,9,85,1,0,0,0,
  	11,87,1,0,0,0,13,89,1,0,0,0,15,91,1,0,0,0,17,93,1,0,0,0,19,95,1,0,0,0,
  	21,97,1,0,0,0,23,99,1,0,0,0,25,101,1,0,0,0,27,103,1,0,0,0,29,105,1,0,
  	0,0,31,107,1,0,0,0,33,109,1,0,0,0,35,112,1,0,0,0,37,115,1,0,0,0,39,117,
  	1,0,0,0,41,119,1,0,0,0,43,122,1,0,0,0,45,125,1,0,0,0,47,128,1,0,0,0,49,
  	133,1,0,0,0,51,138,1,0,0,0,53,144,1,0,0,0,55,148,1,0,0,0,57,151,1,0,0,
  	0,59,155,1,0,0,0,61,159,1,0,0,0,63,163,1,0,0,0,65,167,1,0,0,0,67,171,
  	1,0,0,0,69,176,1,0,0,0,71,181,1,0,0,0,73,186,1,0,0,0,75,191,1,0,0,0,77,
  	78,5,61,0,0,78,2,1,0,0,0,79,80,5,40,0,0,80,4,1,0,0,0,81,82,5,41,0,0,82,
  	6,1,0,0,0,83,84,5,44,0,0,84,8,1,0,0,0,85,86,5,91,0,0,86,10,1,0,0,0,87,
  	88,5,63,0,0,88,12,1,0,0,0,89,90,5,58,0,0,90,14,1,0,0,0,91,92,5,93,0,0,
  	92,16,1,0,0,0,93,94,5,123,0,0,94,18,1,0,0,0,95,96,5,125,0,0,96,20,1,0,
  	0,0,97,98,5,42,0,0,98,22,1,0,0,0,99,100,5,47,0,0,100,24,1,0,0,0,101,102,
  	5,37,0,0,102,26,1,0,0,0,103,104,5,43,0,0,104,28,1,0,0,0,105,106,5,45,
  	0,0,106,30,1,0,0,0,107,108,5,33,0,0,108,32,1,0,0,0,109,110,5,61,0,0,110,
  	111,5,61,0,0,111,34,1,0,0,0,112,113,5,33,0,0,113,114,5,61,0,0,114,36,
  	1,0,0,0,115,116,5,62,0,0,116,38,1,0,0,0,117,118,5,60,0,0,118,40,1,0,0,
  	0,119,120,5,62,0,0,120,121,5,61,0,0,121,42,1,0,0,0,122,123,5,60,0,0,123,
  	124,5,61,0,0,124,44,1,0,0,0,125,126,5,105,0,0,126,127,5,102,0,0,127,46,
  	1,0,0,0,128,129,5,101,0,0,129,130,5,108,0,0,130,131,5,115,0,0,131,132,
  	5,101,0,0,132,48,1,0,0,0,133,134,5,116,0,0,134,135,5,104,0,0,135,136,
  	5,101,0,0,136,137,5,110,0,0,137,50,1,0,0,0,138,139,5,119,0,0,139,140,
  	5,104,0,0,140,141,5,105,0,0,141,142,5,108,0,0,142,143,5,101,0,0,143,52,
  	1,0,0,0,144,145,5,97,0,0,145,146,5,110,0,0,146,147,5,100,0,0,147,54,1,
  	0,0,0,148,149,5,111,0,0,149,150,5,114,0,0,150,56,1,0,0,0,151,152,5,110,
  	0,0,152,153,5,111,0,0,153,154,5,116,0,0,154,58,1,0,0,0,155,156,5,112,
  	0,0,156,157,5,111,0,0,157,158,5,119,0,0,158,60,1,0,0,0,159,160,5,109,
  	0,0,160,161,5,97,0,0,161,162,5,120,0,0,162,62,1,0,0,0,163,164,5,109,0,
  	0,164,165,5,105,0,0,165,166,5,110,0,0,166,64,1,0,0,0,167,168,5,97,0,0,
  	168,169,5,98,0,0,169,170,5,115,0,0,170,66,1,0,0,0,171,172,5,115,0,0,172,
  	173,5,117,0,0,173,174,5,109,0,0,174,68,1,0,0,0,175,177,7,0,0,0,176,175,
  	1,0,0,0,177,178,1,0,0,0,178,176,1,0,0,0,178,179,1,0,0,0,179,70,1,0,0,
  	0,180,182,7,1,0,0,181,180,1,0,0,0,182,183,1,0,0,0,183,181,1,0,0,0,183,
  	184,1,0,0,0,184,72,1,0,0,0,185,187,5,13,0,0,186,185,1,0,0,0,186,187,1,
  	0,0,0,187,188,1,0,0,0,188,189,5,10,0,0,189,74,1,0,0,0,190,192,7,2,0,0,
  	191,190,1,0,0,0,192,193,1,0,0,0,193,191,1,0,0,0,193,194,1,0,0,0,194,195,
  	1,0,0,0,195,196,6,37,0,0,196,76,1,0,0,0,5,0,178,183,186,193,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  calclexerLexerStaticData = std::move(staticData);
}

}

CalcLexer::CalcLexer(CharStream *input) : Lexer(input) {
  CalcLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *calclexerLexerStaticData->atn, calclexerLexerStaticData->decisionToDFA, calclexerLexerStaticData->sharedContextCache);
}

CalcLexer::~CalcLexer() {
  delete _interpreter;
}

std::string CalcLexer::getGrammarFileName() const {
  return "Calc.g4";
}

const std::vector<std::string>& CalcLexer::getRuleNames() const {
  return calclexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& CalcLexer::getChannelNames() const {
  return calclexerLexerStaticData->channelNames;
}

const std::vector<std::string>& CalcLexer::getModeNames() const {
  return calclexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& CalcLexer::getVocabulary() const {
  return calclexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView CalcLexer::getSerializedATN() const {
  return calclexerLexerStaticData->serializedATN;
}

const atn::ATN& CalcLexer::getATN() const {
  return *calclexerLexerStaticData->atn;
}




void CalcLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  calclexerLexerInitialize();
#else
  ::antlr4::internal::call_once(calclexerLexerOnceFlag, calclexerLexerInitialize);
#endif
}
