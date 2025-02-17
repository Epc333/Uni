grammar Calc;

prog:  stat+ EOF ; 

stat:  expr NEWLINE           # printExpr
    |  ID '=' expr NEWLINE    # assign
    |  NEWLINE                # blank
    ;

expr: SUB expr               # unary
    |  '(' expr ')'          # parentesis
    |  expr FACT             # factorial
    |  expr (MUL|DIV|MOD) expr   # prod
    |  expr (ADD|SUB) expr   # plus
    |  expr (EQUAL|NOT_EQUAL|GREATER_THAN|GREATER_OR_EQUAL|LESS_OR_EQUAL|LESS_THAN) expr      # comparacio
    |  NOT expr              # not
    |  expr (AND|OR) expr    # booleans
    |  POW '(' expr ',' expr ')'   #pow
    |  MAX '(' expr ( ',' expr )* ')'   #max
    |  MIN '(' expr ( ',' expr )* ')'   #min
    |  SUM '(' expr ( ',' expr )* ')'   #sum
    |  ABS '(' expr ')'      #abs
    |  '[' expr '?' expr ':' expr ']'   #condicional
    |  WHILE expr '{' expr+ '}'  #while
    |  INT                   # int
    |  ID                    # id
    ;

MUL :  '*' ;
DIV :  '/' ;
MOD :  '%' ;
ADD :  '+' ;
SUB :  '-' ;
FACT : '!' ;

EQUAL : '==';
NOT_EQUAL : '!=';
GREATER_THAN : '>';
LESS_THAN : '<';
GREATER_OR_EQUAL : '>=';
LESS_OR_EQUAL : '<=';

IF : 'if';
ELSE : 'else';
THEN : 'then';
WHILE : 'while';

AND : 'and';
OR : 'or';
NOT : 'not';

POW : 'pow';
MAX : 'max';
MIN : 'min';
ABS : 'abs';
SUM : 'sum';

ID  :  [a-zA-Z]+ ;       // match identifiers
INT :  [0-9]+ ;          // match integers
NEWLINE: '\r'? '\n' ;    // return newlines to parser (is end-statement signal)
WS  :  [ \t]+ -> skip ;  // toss out whitespace
