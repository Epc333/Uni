%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% NotaciÃ³:
%%   * "donat N" significa que l'argument N estarÃ  instanciat inicialmente.
%%   * "ha de ser capaÃ§ de generar totes les respostes possibles" significa que
%%     si hi ha backtracking ha de poder generar la segÃ¼ent resposta, com el
%%     member(E,L) que per una llista L "donada" pot generar tots els elements E.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% En LI adapterem la "Notation of Predicate Descriptions" de SWI-Prolog per
%% descriure els predicats, prefixant cada argument amb un d'aquests 3 sÃ­mbols:
%%   '+' quan l'argument ha d'estar necessÃ riament instanciat (no pot ser una
%%       variable sense instanciar). Pot ser ground (f(a) o 34)" o no (X+1 o g(a,Y)).
%%       Quan parlem de "donada L", llavors especficarem +L en la *descripciÃ³*.
%%       Per exemple, l'argument de +L del predicat esta_ordenada(+L).
%%   '-' quan l'argument ha de ser necessÃ riament una variable que quedarÃ 
%%       instanciada, al satisfer-se el predicat, amb un cert terme que podem
%%       veure com un "resultat".
%%       Per exemple, l'argument -F en el predicat fact(+N,-F) que per un N donat,
%%       se satisfÃ  fent que F sigui el valor N!.
%%   '?' quan s'accepta que l'argument pugui estar instanciat o no.
%%       Es tracta dels casos en que es diu "ha de poder generar la S i tambÃ©
%%       comprovar una S donada". Llavors especificarem ?S en la *descripciÃ³*.
%%       Per exemple, l'argument ?S de suma(+L,?S).
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% En aquests exercicis feu servir els predicats:
%%   * member(E,L)         en lloc de  pert(E,L)
%%   * append(L1,L2,L3)    en lloc de  concat(L1,L2,L3)
%%   * select(E,L,R)       en lloc de  pert_amb_resta(E,L,R)
%%   * permutation(L,P)    en lloc de  permutacio(L,P)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



% PROB. A =========================================================
% Escriu un predicat
% prod(+L,?P)  que signifiqui: P Ã©s el producte dels
% elements de la llista de enters donada L. Ha de poder generar la
% P i tambÃ© comprovar una P donada







% PROB. B =========================================================
% Escriu un predicat
% pescalar(+L1,+L2,?P) que signifiqui: P Ã©s el producte escalar dels
% vectors L1 i L2, on els vectors es representen com llistes
% d'enters. El predicat ha de fallar si els dos vectors
% tenen longituds diferents.







% PROB. C =========================================================
% Representant conjunts com llistes sense repeticions, escriu
% predicats per les operacions d'intersecciÃ³ i uniÃ³ de conjunts donats

% interseccio(+L1,+L2,?L3)




% unio(+L1,+L2,?L3)






% PROB. D =========================================================
% Usant append/3, escriu un predicat per calcular l'Ãºltim 
% element d'una llista donada, i un altre per calcular la llista
% inversa d'una llista donada.

% ultim(+L,?E)




% inversa(+L1,?L2)






% PROB. E =========================================================
% Escriu un predicat
% fib(+N,?F) que signifiqui: F Ã©s l'N-Ã©ssim nombre de Fibonacci
% per a la N donada. Aquests nombres es defineixen aixÃ­:
% fib(1) = 1, fib(2) = 1, i si N > 2 llavors
% fib(N) = fib(N-1) + fib(N-2)






% PROB. F =========================================================
% Escriu un predicat
% dados(+P,+N,-L) que signifiqui: la llista L expressa una forma de
% sumar P punts llanÃ§ant N daus. Per exemple: si P Ã©s 5, i
% N Ã©s 2, una soluciÃ³ seria [1,4] (noteu que la longitud de L Ã©s N.
% Tant P com N venen instanciats. El predicat deu ser capaÃ§ de
% generar totes les solucions possibles,






% PROB. G =========================================================
% Escriu un predicat
% suma_la_resta(+L) que, donada una llista d'enters L, es satisfÃ  si
% existeix algun element en L que Ã©s igual a la suma de la resta
% d'elements de L, i que altrament falla.
% Escriu abans un predicat
% suma(+L,?S) que, donada una llista d'enters L, se satisfÃ  si S
% Ã©s la suma dels elements d'L.

% suma(+L,?S)




% suma_la_resta(+L)






% PROB. H =========================================================
% Escriu un predicat
% card(+L) que, donada una llista d'enters L, escriba la llista
% que, para cada element d'L, diu quantes vegades surt aquest
% element en L.
% Per exemple, si fem la consulta
% card( [1,2,1,5,1,3,3,7] )  l'intÃ¨rpret escriurÃ :
% [[1,3],[2,1],[5,1],[3,2],[7,1]].







% PROB. I ========================================================
% Escriu un predicat
% esta_ordenada(+L) que signifiqui: la llista L de nombres enters
% estÃ  ordenada de menor a major.
% Per exemple, a la consulta:
% ?- esta_ordenada([3,45,67,83]).
% l'intÃ¨rpret respon yes, i a la consulta:
% ?- esta_ordenada([3,67,45]).
% respon no.








% PROB. J ========================================================
% Escriu un predicat
% palÃ­ndroms(+L) que, donada una llista de lletres L escrigui
% totes les permutacions dels seus elements que siguin palÃ­ndroms
% (capicues). Per exemple, amb la consulta palindrom([a,a,c,c])
% s'escriu [a,c,c,a] i [c,a,a,c]
% (possiblement diverses vegades, no cal que eviteu les repeticions).








% PROB. K ========================================================
% Volem obtenir en Prolog un predicat
% dom(+L) que, donada una llista L de fitxes de dominÃ³ (en el format
% indicat abaix), escrigui una cadena de dominÃ³fent servir *totes*
% les fitxes de L, o escrigui "no hi ha cadena" si no Ã©s possible.
% Per exemple,
% ?- dom( [ f(3,4), f(2,3), f(1,6), f(2,2), f(4,2), f(2,1) ] ).
% escriu la cadena correcta:
% [ f(2,3), f(3,4), f(4,2), f(2,2), f(2,1), f(1,6) ].
%
% TambÃ© podem "girar" alguna fitxa como f(N,M), reemplaÃ§ant-la
% per f(M,N). AixÃ­, per:
% ?- dom( [ f(4,3), f(2,3), f(1,6), f(2,2), f(2,4), f(2,1) ] ).
% nomÃ©s hi ha cadena si es gira alguna fitxa (per exemple, hi ha
% mateixa cadena d'abans).
%
% El segÃ¼ent programa Prolog encara no tÃ© implementat els possibles
% girs de fitxes, ni tÃ© implementat el predicat ok(P), que
% significa: P Ã©s una cadena de dominÃ³ correcta (tal qual,
% sense necessitat de girar cap fitxa):

p([],[]).
p(L,[X|P]) :- select(X,L,R), p(R,P).

dom(L) :- p(L,P), ok(P), write(P), nl.
dom(_) :- write('no hi ha cadena'), nl.

% a) Escriu el predicat ok(+P) que falta.






% b) EstÃ©n el predicat p/2 per a que el programa tambÃ© pugui
%    fer cadenes girant alguna de les fitxes de l'entrada.







% PROB. L ========================================================
% Write in Prolog a predicate aplanada(+L,?F) that ``flattens''
% (cat.: ``aplana'') the list F as in the example:
% ?- aplanada( [a,b,[c,[d],e,[]],f,[g,h]], F ).
% F = [a,b,c,d,e,f,g,h]







% PROB. M ========================================================
% Consider two groups of 10 people each. In the first group,
% as expected, the percentage of people with lung cancer among smokers
% is higher than among non-smokers.
% In the second group, the same is the case.
% But if we consider the 20 people of the two groups together, then
% the situation is the opposite: the proportion of people with
% lung cancer is higher among non-smokers than among smokers!
% Can this be true? Write a little Prolog program to find it out.

%% Descomenteu i completeu les linies de codi que veieu a continuaciÃ³:
%% main :-
%%     between(0,3,SC1),    % SC1:   "no.    smokers with    cancer group 1"
%%     between(0,3,SNC1),   % SNC1:  "no.    smokers with no cancer group 1"
%%     between(0,3,NSC1),   % NSC1:  "no. no smokers with    cancer group 1"
%%     between(0,3,NSNC1),  % NSNC1: "no. no smokers with no cancer group 1"
%%     10 is SC1+SNC1+NSC1+NSNC1,  
%%     ...
