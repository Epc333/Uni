from antlr4 import *
from schemeLexer import schemeLexer
from schemeParser import schemeParser
from schemeVisitor import schemeVisitor
from evalVisitor import EvalVisitor
import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python3 scheme.py <input_file>")
        sys.exit(1)

    # Fix encoding by specifying utf-8
    input_stream = FileStream(sys.argv[1], encoding='utf-8')
    lexer = schemeLexer(input_stream)
    stream = CommonTokenStream(lexer)
    parser = schemeParser(stream)
    tree = parser.root()

    evaluator = EvalVisitor()
    try:
        result = evaluator.visit(tree)
        if result is not None:
            print(result)
    except Exception as e:
        print(f"Error: {str(e)}")
        sys.exit(1)

if __name__ == '__main__':
    main()


