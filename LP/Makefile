all: antlr

antlr: scheme.g4
	antlr3 -Dlanguage=Python3 -no-listener -visitor scheme.g4

clean:
	rm -f *.interp *.tokens *Parser.py *Lexer.py *Visitor.py