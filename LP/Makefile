all: parser

parser: scheme.g4
	antlr4 -Dlanguage=Python3 -no-listener -visitor scheme.g4

clean:
	rm -f *.interp *.tokens
	rm -f schemeLexer.py schemeParser.py schemeVisitor.py schemeListener.py
