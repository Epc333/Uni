// Generated from /home/eudald/Desktop/Uni/LP/scheme.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue"})
public class schemeParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.13.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, TRUE=4, FALSE=5, ATOM=6, COMMENT=7, WS=8, LEXICAL_ERROR=9;
	public static final int
		RULE_root = 0, RULE_expr = 1;
	private static String[] makeRuleNames() {
		return new String[] {
			"root", "expr"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'('", "')'", "''('", "'#t'", "'#f'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, "TRUE", "FALSE", "ATOM", "COMMENT", "WS", "LEXICAL_ERROR"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "scheme.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public schemeParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@SuppressWarnings("CheckReturnValue")
	public static class RootContext extends ParserRuleContext {
		public TerminalNode EOF() { return getToken(schemeParser.EOF, 0); }
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public RootContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_root; }
	}

	public final RootContext root() throws RecognitionException {
		RootContext _localctx = new RootContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_root);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(7);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 122L) != 0)) {
				{
				{
				setState(4);
				expr();
				}
				}
				setState(9);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(10);
			match(EOF);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ExprContext extends ParserRuleContext {
		public ExprContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr; }
	 
		public ExprContext() { }
		public void copyFrom(ExprContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class DefinirLlistesContext extends ExprContext {
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public DefinirLlistesContext(ExprContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class TrueContext extends ExprContext {
		public TerminalNode TRUE() { return getToken(schemeParser.TRUE, 0); }
		public TrueContext(ExprContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class FalseContext extends ExprContext {
		public TerminalNode FALSE() { return getToken(schemeParser.FALSE, 0); }
		public FalseContext(ExprContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class AtomContext extends ExprContext {
		public TerminalNode ATOM() { return getToken(schemeParser.ATOM, 0); }
		public AtomContext(ExprContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class EvaluarExpressionsContext extends ExprContext {
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public EvaluarExpressionsContext(ExprContext ctx) { copyFrom(ctx); }
	}

	public final ExprContext expr() throws RecognitionException {
		ExprContext _localctx = new ExprContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_expr);
		int _la;
		try {
			setState(31);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__0:
				_localctx = new EvaluarExpressionsContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(12);
				match(T__0);
				setState(16);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 122L) != 0)) {
					{
					{
					setState(13);
					expr();
					}
					}
					setState(18);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(19);
				match(T__1);
				}
				break;
			case T__2:
				_localctx = new DefinirLlistesContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(20);
				match(T__2);
				setState(24);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 122L) != 0)) {
					{
					{
					setState(21);
					expr();
					}
					}
					setState(26);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				setState(27);
				match(T__1);
				}
				break;
			case TRUE:
				_localctx = new TrueContext(_localctx);
				enterOuterAlt(_localctx, 3);
				{
				setState(28);
				match(TRUE);
				}
				break;
			case FALSE:
				_localctx = new FalseContext(_localctx);
				enterOuterAlt(_localctx, 4);
				{
				setState(29);
				match(FALSE);
				}
				break;
			case ATOM:
				_localctx = new AtomContext(_localctx);
				enterOuterAlt(_localctx, 5);
				{
				setState(30);
				match(ATOM);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static final String _serializedATN =
		"\u0004\u0001\t\"\u0002\u0000\u0007\u0000\u0002\u0001\u0007\u0001\u0001"+
		"\u0000\u0005\u0000\u0006\b\u0000\n\u0000\f\u0000\t\t\u0000\u0001\u0000"+
		"\u0001\u0000\u0001\u0001\u0001\u0001\u0005\u0001\u000f\b\u0001\n\u0001"+
		"\f\u0001\u0012\t\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0005\u0001"+
		"\u0017\b\u0001\n\u0001\f\u0001\u001a\t\u0001\u0001\u0001\u0001\u0001\u0001"+
		"\u0001\u0001\u0001\u0003\u0001 \b\u0001\u0001\u0001\u0000\u0000\u0002"+
		"\u0000\u0002\u0000\u0000&\u0000\u0007\u0001\u0000\u0000\u0000\u0002\u001f"+
		"\u0001\u0000\u0000\u0000\u0004\u0006\u0003\u0002\u0001\u0000\u0005\u0004"+
		"\u0001\u0000\u0000\u0000\u0006\t\u0001\u0000\u0000\u0000\u0007\u0005\u0001"+
		"\u0000\u0000\u0000\u0007\b\u0001\u0000\u0000\u0000\b\n\u0001\u0000\u0000"+
		"\u0000\t\u0007\u0001\u0000\u0000\u0000\n\u000b\u0005\u0000\u0000\u0001"+
		"\u000b\u0001\u0001\u0000\u0000\u0000\f\u0010\u0005\u0001\u0000\u0000\r"+
		"\u000f\u0003\u0002\u0001\u0000\u000e\r\u0001\u0000\u0000\u0000\u000f\u0012"+
		"\u0001\u0000\u0000\u0000\u0010\u000e\u0001\u0000\u0000\u0000\u0010\u0011"+
		"\u0001\u0000\u0000\u0000\u0011\u0013\u0001\u0000\u0000\u0000\u0012\u0010"+
		"\u0001\u0000\u0000\u0000\u0013 \u0005\u0002\u0000\u0000\u0014\u0018\u0005"+
		"\u0003\u0000\u0000\u0015\u0017\u0003\u0002\u0001\u0000\u0016\u0015\u0001"+
		"\u0000\u0000\u0000\u0017\u001a\u0001\u0000\u0000\u0000\u0018\u0016\u0001"+
		"\u0000\u0000\u0000\u0018\u0019\u0001\u0000\u0000\u0000\u0019\u001b\u0001"+
		"\u0000\u0000\u0000\u001a\u0018\u0001\u0000\u0000\u0000\u001b \u0005\u0002"+
		"\u0000\u0000\u001c \u0005\u0004\u0000\u0000\u001d \u0005\u0005\u0000\u0000"+
		"\u001e \u0005\u0006\u0000\u0000\u001f\f\u0001\u0000\u0000\u0000\u001f"+
		"\u0014\u0001\u0000\u0000\u0000\u001f\u001c\u0001\u0000\u0000\u0000\u001f"+
		"\u001d\u0001\u0000\u0000\u0000\u001f\u001e\u0001\u0000\u0000\u0000 \u0003"+
		"\u0001\u0000\u0000\u0000\u0004\u0007\u0010\u0018\u001f";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}