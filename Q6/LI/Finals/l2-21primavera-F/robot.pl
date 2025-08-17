%% Complete the following prolog program that writes the shortest path for a robot to 
%% go in a factory from initial location (marked i) to final location (marked f).
%% The robot cannot traverse the obstacles (marked with o). 

  
factoryMap( [                                                %    Output (path marked with "."), should be:      
	       [o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o],    %    o o o o o o o o o o o o o o o o o o o o    		       
	       [o,-,-,-,-,-,-,-,-,-,-,-,-,-,-,-,-,-,-,o],    %    o                                     o	 	       
	       [o,o,o,-,-,-,-,-,-,-,-,-,-,-,-,-,-,-,-,o],    %    o o o                                 o	 	       
	       [o,-,o,-,-,-,-,-,-,-,-,-,-,-,-,-,-,-,-,o],    %    o   o                                 o	 	       
	       [o,-,o,o,o,o,o,o,o,o,o,o,o,o,o,o,-,-,-,o],    %    o   o o o o o o o o o o o o o o       o	 	       
	       [o,-,-,-,-,-,-,-,-,-,-,-,-,-,-,-,o,o,o,o],    %    o . . . . . . . . . . . . . .   o o o o	 	       
	       [o,-,o,o,o,o,o,o,o,o,o,o,o,o,-,-,o,o,o,o],    %    o . o o o o o o o o o o o o .   o o o o	 	       
	       [o,-,o,-,-,-,o,o,o,o,o,-,-,o,-,-,o,o,o,o],    %    o . o       o o o o o     o .   o o o o	 	       
	       [o,-,o,-,-,-,o,o,o,o,o,-,-,o,-,o,o,o,-,o],    %    o . o       o o o o o     o . o o o   o	 	       
	       [o,-,o,-,-,-,o,o,o,o,o,-,-,o,-,o,o,o,-,o],    %    o . o       o o o o o     o . o o o   o	 	       
	       [o,-,o,o,o,o,o,o,o,o,o,f,o,o,-,o,o,o,-,o],    %    o . o o o o o o o o o f o o . o o o   o	 	       
	       [o,-,-,-,-,-,-,-,-,o,o,-,o,o,-,-,o,-,-,o],    %    o .               o o . o o .   o     o	 	       
	       [o,-,o,-,-,-,-,-,-,o,o,-,o,o,-,-,o,-,-,o],    %    o . o             o o . o o .   o     o	 	       
	       [o,-,o,-,-,o,o,o,o,-,-,-,o,o,-,-,o,-,-,o],    %    o . o     o o o o     . o o .   o     o	 	       
	       [-,-,o,-,-,o,o,o,o,-,-,-,o,o,-,-,o,-,-,o],    %      . o     o o o o     . o o .   o     o	 	       
	       [-,-,o,-,-,o,o,o,o,-,-,-,-,-,-,-,o,-,-,o],    %      . o     o o o o     . . . .   o     o	 	       
	       [-,-,o,o,o,o,-,-,-,-,o,o,o,o,o,o,o,-,-,o],    %      . o o o o         o o o o o o o     o	 	       
	       [o,i,o,o,o,o,-,-,-,-,-,-,-,-,-,-,-,-,-,o],    %    o i o o o o                           o	 	       
	       [o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o]     %    o o o o o o o o o o o o o o o o o o o o         
	   ]).    


estadoInicial([X,Y]):- factoryMap(F), nth1(X,F,Row), nth1(Y,Row,i),!.  %nth1(N,L,X) means "the Nth elemento of list L is X"
estadoFinal([X,Y]):- factoryMap(F), nth1(X,F,Row), nth1(Y,Row,f),!.

main:- 
       estadoInicial(EstadoInicial), estadoFinal(EstadoFinal),
       between(1,1000,CosteMax),               % Buscamos solucion de coste 0; si no, de 1, etc.
       camino( CosteMax, EstadoInicial, EstadoFinal, [EstadoInicial], Camino ),
       displaySol(Camino), nl,halt.

camino( 0, E,E, C,C ).
camino( CosteMax, EstadoActual, EstadoFinal, CaminoHastaAhora, CaminoTotal ):-
	CosteMax>0,
	unPaso( CostePaso, EstadoActual, EstadoSiguiente ),  % Aqui CostePaso siempre es 1.
	\+member( EstadoSiguiente, CaminoHastaAhora ),
	CosteMax1 is CosteMax-CostePaso,
	camino(CosteMax1,EstadoSiguiente,EstadoFinal, [EstadoSiguiente|CaminoHastaAhora], CaminoTotal).

unPaso(1, [X, Y], [X1, Y]) :- X1 is X + 1, factoryMap(M), nth1(X1, M, Row), nth1(Y, Row, El), El \= o.
unPaso(1, [X, Y], [X1, Y]) :- X1 is X - 1, factoryMap(M), nth1(X1, M, Row), nth1(Y, Row, El), El \= o.
unPaso(1, [X, Y], [X, Y1]) :- Y1 is Y + 1, factoryMap(M), nth1(X, M, Row), nth1(Y1, Row, El), El \= o.
unPaso(1, [X, Y], [X, Y1]) :- Y1 is Y - 1, factoryMap(M), nth1(X, M, Row), nth1(Y1, Row, El), El \= o.

displaySol(Camino):-   factoryMap(F), nth1(X,F,Row), nl, nth1(Y,Row,E), writePos(E,X,Y,Camino), fail.
displaySol(_).
writePos(E,_,_,_):- member(E,[i,f,o]), write(E),write(' '), !.
writePos(_,X,Y,Camino):- member([X,Y],Camino), write('. '),!.
writePos(-,_,_,_):- write('  '),!.

