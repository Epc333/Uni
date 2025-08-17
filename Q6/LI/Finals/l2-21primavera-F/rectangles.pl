:- use_module(library(clpfd)).

% For the problem squares (how to fit N SQUARES into a big square), some useful prolog predicates are:
% 
% insideBigSquare(_,[],[]).
% insideBigSquare(Big,[S|Sides],[V|Vars]):-
%     Big #>= V+S-1,
%     insideBigSquare(Big,Sides,Vars).
% 
% nonoverlapping([],[],[]).
% nonoverlapping([S|Sides],[RV|RowVars],[CV|ColVars]):-
%     nonover( S,RV,CV, Sides,RowVars,ColVars ),   % the first one (S,RV,CV) does not overlap with the others
%     nonoverlapping(Sides,RowVars,ColVars).
% 
% nonover(_,_,_, [],[],[]).
% nonover(S1,RV1,CV1, [S2|Sides],[RV2|RowVars],[CV2|ColVars]):-
%     nonover(S1,RV1,CV1, Sides,RowVars,ColVars),
%     (  RV1 #>= RV2+S2   #\/   RV2 #>= RV1+S1   #\/   CV1 #>= CV2+S2   #\/   CV2 #>= CV1+S1  ).
%
%====================================================================================
% For this exam, complete the following code to fit N RECTANGLES into a big square. %
%====================================================================================
%
% Hint: you may want to adapt the predicates above used for squares!!!
% 
% example(_, Big, [Name1-L1-HT1...NameN-Ln-Hn]):  how to fit all rectangles Li-Hi of length Li and height Hi in a
%                                                 square of size Big?

example(0,   6, [a-2-3, b-2-4, c-1-4, d-2-2, e-3-2, f-3-1, g-1-4] ).
example(1,  10, [a-2-5, b-4-4, c-2-5, d-3-3, e-3-3, f-3-1, g-5-5, h-1-4, i-6-2] ).

% One possible solution for example 1 is the following (note that the big square is not full; there are two empty spaces):

%% cchaaggggg
%% cchaaggggg
%% cchaaggggg
%% cchaaggggg
%% cc aaggggg
%% dddeee fff
%% dddeeebbbb
%% dddeeebbbb
%% iiiiiibbbb
%% iiiiiibbbb



main:- 
    example(1, Big, Rectangles),
    nl, write('Fitting all rectangles of '), write(Rectangles), write(' into big square of size '), write(Big), nl,nl,
    length(Rectangles,N), 
    length(RowVars,N), % get list of N prolog vars: Row coordinates of each rectangle
    length(ColVars,N),

    insideBigSquare(Big, Rectangles, RowVars, ColVars),
    nonoverlapping(Rectangles, RowVars, ColVars),
    append(RowVars,ColVars,Vars),
    labeling([ff],Vars),
    displaySol(Big,Rectangles,RowVars,ColVars), halt.



insideBigSquare(_,[],[],[]).
insideBigSquare(Big,[_-N-M|Sides],[R|RowVars], [C|ColVars]):-
    Big #>= R+M-1,
    Big #>= C+N-1,
    0 #< R,
    0 #< C,    
    insideBigSquare(Big,Sides,RowVars,ColVars).

nonoverlapping([],[],[]).
nonoverlapping([S|Sides],[RV|RowVars],[CV|ColVars]):-
    nonover( S,RV,CV, Sides,RowVars,ColVars ),   % the first one (S,RV,CV) does not overlap with the others
    nonoverlapping(Sides,RowVars,ColVars).

nonover(_,_,_, [],[],[]).
nonover(_-X-Y, RV1,CV1, [_-X2-Y2|Sides],[RV2|RowVars],[CV2|ColVars]):-
    nonover(_-X-Y,RV1,CV1, Sides,RowVars,ColVars),
    (  RV1 #>= RV2+Y2   #\/   RV2 #>= RV1+Y   #\/   CV1 #>= CV2+X2   #\/   CV2 #>= CV1+X  ).

%--------------------------------
displaySol(N,Rectangles,RowVars,ColVars):- 
    between(1,N,Row), nl, between(1,N,Col),  wRowCol(Row,Col,Rectangles,RowVars,ColVars), fail.
displaySol(_,_,_,_):- nl,nl,!.

wRowCol(Row,Col,Rectangles,RowVars,ColVars):-
    nth1(K,Rectangles, X-Li-Hi),    
    nth1(K,RowVars,RV),    RVS is RV+Hi-1,     between(RV,RVS,Row),
    nth1(K,ColVars,CV),    CVS is CV+Li-1,     between(CV,CVS,Col),    write(X),!.
wRowCol(_,_,_,_,_):- write(' '),!.
%--------------------------------




