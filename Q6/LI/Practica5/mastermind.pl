% Mastermind ´es un joc on un jugador (defensor) s’inventa un codi secret i l’altre jugador
% (atacant) ha d’esbrinar-ho. El codi ´es una seq¨u`encia de 4 colors a triar entre vermell (v), blau
% (b), groc (g), lila (l), taronja (t) i marr´o (m). L’atacant t´e un nombre finit d’intents per a
% trencar el codi. En cada intent, l’atacant preguntar`a per una seq¨u`encia de 4 colors i el defensor
% respondr`a amb dos n´umeros (E,D), sent E el nombre de colors que l’atacant ha encertat en la
% posici´o Exacta, i D el nombre de colors que ha encertat per`o en una posici´o Diferent. 

resposta(Codi, Intent, E, D) :- 
    findall(I, (nth0(I, Codi, X), nth0(I, Intent, X)), Matches),
    length(Matches, E),
    findall(X, (nth0(I, Codi, X), \+ member(I, Matches)), CodiRest),
    findall(Y, (nth0(I, Intent, Y), \+ member(I, Matches)), IntentRest),
    findall(1, member(v, CodiRest), VCodi),
    length(VCodi, CountVCodi),
    findall(1, member(v, IntentRest), VIntent),
    length(VIntent, CountVIntent),
    MinV is min(CountVCodi, CountVIntent),
    findall(1, member(b, CodiRest), BCodi),
    length(BCodi, CountBCodi),
    findall(1, member(b, IntentRest), BIntent),
    length(BIntent, CountBIntent),
    MinB is min(CountBCodi, CountBIntent),
    findall(1, member(g, CodiRest), GCodi),
    length(GCodi, CountGCodi),
    findall(1, member(g, IntentRest), GIntent),
    length(GIntent, CountGIntent),
    MinG is min(CountGCodi, CountGIntent),
    findall(1, member(l, CodiRest), LCodi),
    length(LCodi, CountLCodi),
    findall(1, member(l, IntentRest), LIntent),
    length(LIntent, CountLIntent),
    MinL is min(CountLCodi, CountLIntent),
    findall(1, member(t, CodiRest), TCodi),
    length(TCodi, CountTCodi),
    findall(1, member(t, IntentRest), TIntent),
    length(TIntent, CountTIntent),
    MinT is min(CountTCodi, CountTIntent),
    findall(1, member(m, CodiRest), MCodi),
    length(MCodi, CountMCodi),
    findall(1, member(m, IntentRest), MIntent),
    length(MIntent, CountMIntent),
    MinM is min(CountMCodi, CountMIntent),
    D is MinV + MinB + MinG + MinL + MinT + MinM.

intents([ [ [v,b,g,l], [1,1] ], [ [m,t,g,l], [1,0] ], [ [g,l,g,l], [0,0] ], [ [v,b,m,m], [1,1] ], [ [v,t,b,t], [2,2] ] ]).

nouIntent(A) :- 
    codi(A),          
    intents(I),                
    compleixPred(A, I).       

compleixPred(_, []).
compleixPred(Codigo, [[Intent, [E, D]] | Resto]) :-
    resposta(Codigo, Intent, E, D),  
    compleixPred(Codigo, Resto). 

codi([C1, C2, C3, C4]) :-
    member(C1, [v, b, g, l, t, m]),   
    member(C2, [v, b, g, l, t, m]),   
    member(C3, [v, b, g, l, t, m]), 
    member(C4, [v, b, g, l, t, m]).

%% Cabre
color(C) :- member(C, [v, b, g, l, t, m]).

resposta(Codi, Intent, E, D) :-
    findall(I, (
        nth0(I, Codi, X),
        nth0(I, Intent, X)
    ), EL),
    findall(I, (
        nth0(I, Intent, X),
        \+ member(I, EL),
        nth0(J, Codi, X),
        \+ member(J, EL)
    ), DL),
    length(EL, E),
    length(DL, D).

% intents(L): L ´es una llista de parelles [Intent, Resposta]
intents([ [ [v,b,g,l], [1,1] ], [ [m,t,g,l], [1,0] ], [ [g,l,g,l], [0,0] ],
[ [v,b,m,m], [1,1] ], [ [v,t,b,t], [2,2] ] ]).

nouIntent(A) :-
    A = [C1,C2,C3,C4],
    color(C1), color(C2), color(C3), color(C4),
    intents(Intents),
    forall(member([I, [E,D]], Intents), 
        resposta(A, I, E, D)).