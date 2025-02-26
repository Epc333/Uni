
// Generated from Asl.g4 by ANTLR 4.13.2


#include "AslLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct AslLexerStaticData final {
  AslLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  AslLexerStaticData(const AslLexerStaticData&) = delete;
  AslLexerStaticData(AslLexerStaticData&&) = delete;
  AslLexerStaticData& operator=(const AslLexerStaticData&) = delete;
  AslLexerStaticData& operator=(AslLexerStaticData&&) = delete;

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

::antlr4::internal::OnceFlag asllexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<AslLexerStaticData> asllexerLexerStaticData = nullptr;

void asllexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (asllexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(asllexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<AslLexerStaticData>(
    std::vector<std::string>{
      "T__0", "T__1", "T__2", "T__3", "T__4", "ASSIGN", "EQUAL", "NE", "GT", 
      "GE", "LT", "LE", "TRUE", "FALSE", "PLUS", "MUL", "MINUS", "DIV", 
      "MOD", "AND", "OR", "NOT", "VAR", "INT", "FLOAT", "BOOL", "CHAR", 
      "IF", "THEN", "ELSE", "ENDIF", "FUNC", "ENDFUNC", "READ", "WRITE", 
      "ID", "INTVAL", "FLOATVAL", "CHARVAL", "STRING", "ESC_SEQ", "COMMENT", 
      "WS"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "'('", "')'", "','", "':'", "';'", "'='", "'=='", "'!='", "'>'", 
      "'>='", "'<'", "'<='", "'true'", "'false'", "'+'", "'*'", "'-'", "'/'", 
      "'%'", "'and'", "'or'", "'not'", "'var'", "'int'", "'float'", "'bool'", 
      "'char'", "'if'", "'then'", "'else'", "'endif'", "'func'", "'endfunc'", 
      "'read'", "'write'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "ASSIGN", "EQUAL", "NE", "GT", "GE", "LT", 
      "LE", "TRUE", "FALSE", "PLUS", "MUL", "MINUS", "DIV", "MOD", "AND", 
      "OR", "NOT", "VAR", "INT", "FLOAT", "BOOL", "CHAR", "IF", "THEN", 
      "ELSE", "ENDIF", "FUNC", "ENDFUNC", "READ", "WRITE", "ID", "INTVAL", 
      "FLOATVAL", "CHARVAL", "STRING", "COMMENT", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,42,280,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,
  	7,28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,
  	7,35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,
  	7,42,1,0,1,0,1,1,1,1,1,2,1,2,1,3,1,3,1,4,1,4,1,5,1,5,1,6,1,6,1,6,1,7,
  	1,7,1,7,1,8,1,8,1,9,1,9,1,9,1,10,1,10,1,11,1,11,1,11,1,12,1,12,1,12,1,
  	12,1,12,1,13,1,13,1,13,1,13,1,13,1,13,1,14,1,14,1,15,1,15,1,16,1,16,1,
  	17,1,17,1,18,1,18,1,19,1,19,1,19,1,19,1,20,1,20,1,20,1,21,1,21,1,21,1,
  	21,1,22,1,22,1,22,1,22,1,23,1,23,1,23,1,23,1,24,1,24,1,24,1,24,1,24,1,
  	24,1,25,1,25,1,25,1,25,1,25,1,26,1,26,1,26,1,26,1,26,1,27,1,27,1,27,1,
  	28,1,28,1,28,1,28,1,28,1,29,1,29,1,29,1,29,1,29,1,30,1,30,1,30,1,30,1,
  	30,1,30,1,31,1,31,1,31,1,31,1,31,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,
  	32,1,33,1,33,1,33,1,33,1,33,1,34,1,34,1,34,1,34,1,34,1,34,1,35,1,35,5,
  	35,217,8,35,10,35,12,35,220,9,35,1,36,4,36,223,8,36,11,36,12,36,224,1,
  	37,4,37,228,8,37,11,37,12,37,229,1,37,1,37,4,37,234,8,37,11,37,12,37,
  	235,1,38,1,38,1,38,3,38,241,8,38,1,38,1,38,1,39,1,39,1,39,5,39,248,8,
  	39,10,39,12,39,251,9,39,1,39,1,39,1,40,1,40,1,40,1,41,1,41,1,41,1,41,
  	5,41,262,8,41,10,41,12,41,265,9,41,1,41,3,41,268,8,41,1,41,1,41,1,41,
  	1,41,1,42,4,42,275,8,42,11,42,12,42,276,1,42,1,42,0,0,43,1,1,3,2,5,3,
  	7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,23,12,25,13,27,14,29,15,31,16,
  	33,17,35,18,37,19,39,20,41,21,43,22,45,23,47,24,49,25,51,26,53,27,55,
  	28,57,29,59,30,61,31,63,32,65,33,67,34,69,35,71,36,73,37,75,38,77,39,
  	79,40,81,0,83,41,85,42,1,0,7,2,0,65,90,97,122,4,0,48,57,65,90,95,95,97,
  	122,2,0,39,39,92,92,2,0,34,34,92,92,8,0,34,34,39,39,92,92,98,98,102,102,
  	110,110,114,114,116,116,2,0,10,10,13,13,3,0,9,10,13,13,32,32,288,0,1,
  	1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,0,
  	0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,0,0,0,23,
  	1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,0,0,0,0,31,1,0,0,0,0,33,1,0,
  	0,0,0,35,1,0,0,0,0,37,1,0,0,0,0,39,1,0,0,0,0,41,1,0,0,0,0,43,1,0,0,0,
  	0,45,1,0,0,0,0,47,1,0,0,0,0,49,1,0,0,0,0,51,1,0,0,0,0,53,1,0,0,0,0,55,
  	1,0,0,0,0,57,1,0,0,0,0,59,1,0,0,0,0,61,1,0,0,0,0,63,1,0,0,0,0,65,1,0,
  	0,0,0,67,1,0,0,0,0,69,1,0,0,0,0,71,1,0,0,0,0,73,1,0,0,0,0,75,1,0,0,0,
  	0,77,1,0,0,0,0,79,1,0,0,0,0,83,1,0,0,0,0,85,1,0,0,0,1,87,1,0,0,0,3,89,
  	1,0,0,0,5,91,1,0,0,0,7,93,1,0,0,0,9,95,1,0,0,0,11,97,1,0,0,0,13,99,1,
  	0,0,0,15,102,1,0,0,0,17,105,1,0,0,0,19,107,1,0,0,0,21,110,1,0,0,0,23,
  	112,1,0,0,0,25,115,1,0,0,0,27,120,1,0,0,0,29,126,1,0,0,0,31,128,1,0,0,
  	0,33,130,1,0,0,0,35,132,1,0,0,0,37,134,1,0,0,0,39,136,1,0,0,0,41,140,
  	1,0,0,0,43,143,1,0,0,0,45,147,1,0,0,0,47,151,1,0,0,0,49,155,1,0,0,0,51,
  	161,1,0,0,0,53,166,1,0,0,0,55,171,1,0,0,0,57,174,1,0,0,0,59,179,1,0,0,
  	0,61,184,1,0,0,0,63,190,1,0,0,0,65,195,1,0,0,0,67,203,1,0,0,0,69,208,
  	1,0,0,0,71,214,1,0,0,0,73,222,1,0,0,0,75,227,1,0,0,0,77,237,1,0,0,0,79,
  	244,1,0,0,0,81,254,1,0,0,0,83,257,1,0,0,0,85,274,1,0,0,0,87,88,5,40,0,
  	0,88,2,1,0,0,0,89,90,5,41,0,0,90,4,1,0,0,0,91,92,5,44,0,0,92,6,1,0,0,
  	0,93,94,5,58,0,0,94,8,1,0,0,0,95,96,5,59,0,0,96,10,1,0,0,0,97,98,5,61,
  	0,0,98,12,1,0,0,0,99,100,5,61,0,0,100,101,5,61,0,0,101,14,1,0,0,0,102,
  	103,5,33,0,0,103,104,5,61,0,0,104,16,1,0,0,0,105,106,5,62,0,0,106,18,
  	1,0,0,0,107,108,5,62,0,0,108,109,5,61,0,0,109,20,1,0,0,0,110,111,5,60,
  	0,0,111,22,1,0,0,0,112,113,5,60,0,0,113,114,5,61,0,0,114,24,1,0,0,0,115,
  	116,5,116,0,0,116,117,5,114,0,0,117,118,5,117,0,0,118,119,5,101,0,0,119,
  	26,1,0,0,0,120,121,5,102,0,0,121,122,5,97,0,0,122,123,5,108,0,0,123,124,
  	5,115,0,0,124,125,5,101,0,0,125,28,1,0,0,0,126,127,5,43,0,0,127,30,1,
  	0,0,0,128,129,5,42,0,0,129,32,1,0,0,0,130,131,5,45,0,0,131,34,1,0,0,0,
  	132,133,5,47,0,0,133,36,1,0,0,0,134,135,5,37,0,0,135,38,1,0,0,0,136,137,
  	5,97,0,0,137,138,5,110,0,0,138,139,5,100,0,0,139,40,1,0,0,0,140,141,5,
  	111,0,0,141,142,5,114,0,0,142,42,1,0,0,0,143,144,5,110,0,0,144,145,5,
  	111,0,0,145,146,5,116,0,0,146,44,1,0,0,0,147,148,5,118,0,0,148,149,5,
  	97,0,0,149,150,5,114,0,0,150,46,1,0,0,0,151,152,5,105,0,0,152,153,5,110,
  	0,0,153,154,5,116,0,0,154,48,1,0,0,0,155,156,5,102,0,0,156,157,5,108,
  	0,0,157,158,5,111,0,0,158,159,5,97,0,0,159,160,5,116,0,0,160,50,1,0,0,
  	0,161,162,5,98,0,0,162,163,5,111,0,0,163,164,5,111,0,0,164,165,5,108,
  	0,0,165,52,1,0,0,0,166,167,5,99,0,0,167,168,5,104,0,0,168,169,5,97,0,
  	0,169,170,5,114,0,0,170,54,1,0,0,0,171,172,5,105,0,0,172,173,5,102,0,
  	0,173,56,1,0,0,0,174,175,5,116,0,0,175,176,5,104,0,0,176,177,5,101,0,
  	0,177,178,5,110,0,0,178,58,1,0,0,0,179,180,5,101,0,0,180,181,5,108,0,
  	0,181,182,5,115,0,0,182,183,5,101,0,0,183,60,1,0,0,0,184,185,5,101,0,
  	0,185,186,5,110,0,0,186,187,5,100,0,0,187,188,5,105,0,0,188,189,5,102,
  	0,0,189,62,1,0,0,0,190,191,5,102,0,0,191,192,5,117,0,0,192,193,5,110,
  	0,0,193,194,5,99,0,0,194,64,1,0,0,0,195,196,5,101,0,0,196,197,5,110,0,
  	0,197,198,5,100,0,0,198,199,5,102,0,0,199,200,5,117,0,0,200,201,5,110,
  	0,0,201,202,5,99,0,0,202,66,1,0,0,0,203,204,5,114,0,0,204,205,5,101,0,
  	0,205,206,5,97,0,0,206,207,5,100,0,0,207,68,1,0,0,0,208,209,5,119,0,0,
  	209,210,5,114,0,0,210,211,5,105,0,0,211,212,5,116,0,0,212,213,5,101,0,
  	0,213,70,1,0,0,0,214,218,7,0,0,0,215,217,7,1,0,0,216,215,1,0,0,0,217,
  	220,1,0,0,0,218,216,1,0,0,0,218,219,1,0,0,0,219,72,1,0,0,0,220,218,1,
  	0,0,0,221,223,2,48,57,0,222,221,1,0,0,0,223,224,1,0,0,0,224,222,1,0,0,
  	0,224,225,1,0,0,0,225,74,1,0,0,0,226,228,2,48,57,0,227,226,1,0,0,0,228,
  	229,1,0,0,0,229,227,1,0,0,0,229,230,1,0,0,0,230,231,1,0,0,0,231,233,5,
  	46,0,0,232,234,2,48,57,0,233,232,1,0,0,0,234,235,1,0,0,0,235,233,1,0,
  	0,0,235,236,1,0,0,0,236,76,1,0,0,0,237,240,5,39,0,0,238,241,3,81,40,0,
  	239,241,8,2,0,0,240,238,1,0,0,0,240,239,1,0,0,0,241,242,1,0,0,0,242,243,
  	5,39,0,0,243,78,1,0,0,0,244,249,5,34,0,0,245,248,3,81,40,0,246,248,8,
  	3,0,0,247,245,1,0,0,0,247,246,1,0,0,0,248,251,1,0,0,0,249,247,1,0,0,0,
  	249,250,1,0,0,0,250,252,1,0,0,0,251,249,1,0,0,0,252,253,5,34,0,0,253,
  	80,1,0,0,0,254,255,5,92,0,0,255,256,7,4,0,0,256,82,1,0,0,0,257,258,5,
  	47,0,0,258,259,5,47,0,0,259,263,1,0,0,0,260,262,8,5,0,0,261,260,1,0,0,
  	0,262,265,1,0,0,0,263,261,1,0,0,0,263,264,1,0,0,0,264,267,1,0,0,0,265,
  	263,1,0,0,0,266,268,5,13,0,0,267,266,1,0,0,0,267,268,1,0,0,0,268,269,
  	1,0,0,0,269,270,5,10,0,0,270,271,1,0,0,0,271,272,6,41,0,0,272,84,1,0,
  	0,0,273,275,7,6,0,0,274,273,1,0,0,0,275,276,1,0,0,0,276,274,1,0,0,0,276,
  	277,1,0,0,0,277,278,1,0,0,0,278,279,6,42,0,0,279,86,1,0,0,0,11,0,218,
  	224,229,235,240,247,249,263,267,276,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  asllexerLexerStaticData = std::move(staticData);
}

}

AslLexer::AslLexer(CharStream *input) : Lexer(input) {
  AslLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *asllexerLexerStaticData->atn, asllexerLexerStaticData->decisionToDFA, asllexerLexerStaticData->sharedContextCache);
}

AslLexer::~AslLexer() {
  delete _interpreter;
}

std::string AslLexer::getGrammarFileName() const {
  return "Asl.g4";
}

const std::vector<std::string>& AslLexer::getRuleNames() const {
  return asllexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& AslLexer::getChannelNames() const {
  return asllexerLexerStaticData->channelNames;
}

const std::vector<std::string>& AslLexer::getModeNames() const {
  return asllexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& AslLexer::getVocabulary() const {
  return asllexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView AslLexer::getSerializedATN() const {
  return asllexerLexerStaticData->serializedATN;
}

const atn::ATN& AslLexer::getATN() const {
  return *asllexerLexerStaticData->atn;
}




void AslLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  asllexerLexerInitialize();
#else
  ::antlr4::internal::call_once(asllexerLexerOnceFlag, asllexerLexerInitialize);
#endif
}
