// Generated from /home/eudald/Desktop/Uni/LP/scheme.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link schemeParser}.
 */
public interface schemeListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link schemeParser#root}.
	 * @param ctx the parse tree
	 */
	void enterRoot(schemeParser.RootContext ctx);
	/**
	 * Exit a parse tree produced by {@link schemeParser#root}.
	 * @param ctx the parse tree
	 */
	void exitRoot(schemeParser.RootContext ctx);
	/**
	 * Enter a parse tree produced by the {@code evaluarExpressions}
	 * labeled alternative in {@link schemeParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterEvaluarExpressions(schemeParser.EvaluarExpressionsContext ctx);
	/**
	 * Exit a parse tree produced by the {@code evaluarExpressions}
	 * labeled alternative in {@link schemeParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitEvaluarExpressions(schemeParser.EvaluarExpressionsContext ctx);
	/**
	 * Enter a parse tree produced by the {@code definirLlistes}
	 * labeled alternative in {@link schemeParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterDefinirLlistes(schemeParser.DefinirLlistesContext ctx);
	/**
	 * Exit a parse tree produced by the {@code definirLlistes}
	 * labeled alternative in {@link schemeParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitDefinirLlistes(schemeParser.DefinirLlistesContext ctx);
	/**
	 * Enter a parse tree produced by the {@code true}
	 * labeled alternative in {@link schemeParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterTrue(schemeParser.TrueContext ctx);
	/**
	 * Exit a parse tree produced by the {@code true}
	 * labeled alternative in {@link schemeParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitTrue(schemeParser.TrueContext ctx);
	/**
	 * Enter a parse tree produced by the {@code false}
	 * labeled alternative in {@link schemeParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterFalse(schemeParser.FalseContext ctx);
	/**
	 * Exit a parse tree produced by the {@code false}
	 * labeled alternative in {@link schemeParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitFalse(schemeParser.FalseContext ctx);
	/**
	 * Enter a parse tree produced by the {@code atom}
	 * labeled alternative in {@link schemeParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterAtom(schemeParser.AtomContext ctx);
	/**
	 * Exit a parse tree produced by the {@code atom}
	 * labeled alternative in {@link schemeParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitAtom(schemeParser.AtomContext ctx);
}