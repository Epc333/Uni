grammar scheme;

// Regla principal
root : expr* EOF;

expr
    : '(' expr* ')'    #evaluarExpressions
    | '\'(' expr* ')'  #definirLlistes
    | TRUE            #true
    | FALSE           #false
    | ATOM            #atom
    ;

// Tokens
TRUE : '#t';
FALSE : '#f';
ATOM: [a-zA-Z0-9_+*/<>=?!'-]+;
COMMENT : ';' ~[\r\n]* -> skip;
WS : [ \t\n\r]+ -> skip;
LEXICAL_ERROR : . -> skip;
