:- use_module(library(clpfd)).

%% A (6-sided) "letter dice" has on each side a different letter.
%% Find four of them, with the 24 letters abcdefghijklmnoprstuvwxy such
%% that you can make all the following words: bake, onyx, echo, oval,
%% gird, smug, jump, torn, luck, viny, lush, wrap, fame.

% Some helpful predicates:

word( [b,a,k,e] ).
word( [o,n,y,x] ).
word( [e,c,h,o] ).
word( [o,v,a,l] ).
word( [g,i,r,d] ).
word( [s,m,u,g] ).
word( [j,u,m,p] ).
word( [t,o,r,n] ).
word( [l,u,c,k] ).
word( [v,i,n,y] ).
word( [l,u,s,h] ).
word( [w,r,a,p] ).
word( [f,a,m,e] ).

% num(?X, ?N)   "La lletra X és a la posició N de la llista"
num(X, N) :- nth1( N, [a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,r,s,t,u,v,w,x,y], X ).


main :-
%1: Variables i dominis:
    length(D1, 6),
    length(D2, 6),
    length(D3, 6),
    length(D4, 6),
    append([D1, D2, D3, D4], Daus),
    all_distinct(Daus),
    Daus ins 1..24,
%2: Constraints:
    findall([X1, X2, X3, X4], (word([L1, L2, L3, L4]), num(L1, X1), num(L2, X2), num(L3, X3), num(L4, X4)), Words),  %Pasem les paraules de números a digits
    findall([X, Y], (member(S, Words), member(X, S), member(Y, S), X < Y), I),  % X < Y per evitar duplicats i informacio redundant
    sort(I, Incomp),
    aplicar_restriccions(D1, Incomp),
    aplicar_restriccions(D2, Incomp),
    aplicar_restriccions(D3, Incomp),
    aplicar_restriccions(D4, Incomp),
    ordenar(D1),
    ordenar(D2),
    ordenar(D3),
    ordenar(D4),
%3: Labeling:
    label(Daus),
%4: Escrivim el resultat:
    writeN(D1), nl,
    writeN(D2), nl,
    writeN(D3), nl,
    writeN(D4), nl, halt.
    
writeN(D) :- findall(X, (member(N,D),num(X,N)), L), write(L), nl, !.

aplicar_restriccions(_, []) :- !.
aplicar_restriccions(Dado, [[X, Y] | L]) :-
    verificar_dau(Dado, [X, Y]),
    aplicar_restriccions(Dado, L).

verificar_dau([], _) :- !.
verificar_dau([X | L], L2) :-
    comprovar_incompatibilitat(X, L, L2),
    verificar_dau(L, L2).

comprovar_incompatibilitat(_, [], _) :- !.
comprovar_incompatibilitat(X, [Y | L], [P1, P2]) :-
    P1 #\= X #\/ P2 #\= Y,
    comprovar_incompatibilitat(X, L, [P1, P2]).

ordenar([X, Y | L]) :- X #< Y, ordenar([Y | L]).
ordenar([X, Y]) :- X #< Y, !.