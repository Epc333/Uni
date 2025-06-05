% Missioners i caníbals: busquem la manera més ràpida per tal que tres missioners i tres
% caníbals travessin un riu en una canoa que pot ser utilitzada per 1 o 2 persones (missioners o
% caníbals), però sempre evitant que els missioners quedin en minoria en qualsevol riba (per raons
% òbvies).

main :- EstatInicial = [3,3, esq, 0, 0],    EstatFinal = [0,0, dreta, 3, 3],
        between(0, 1000, CostMax),                  % Busquem solució de cost 0; si no, de 1, etc.
        cami(CostMax, EstatInicial, EstatFinal, [EstatInicial], Cami),
        reverse(Cami, Cami1), write(Cami1), write(' amb cost '), write(CostMax), nl, halt.

cami(0, E, E, C, C).                                % Cas base: quan l'estat actual és l'estat final.
cami(CostMax, EstatActual, EstatFinal, CamiFinsAra, CamiTotal) :-
        CostMax > 0, 
        unPas(CostPas, EstatActual, EstatSeguent),  % En B1 i B2, CostPas és 1.
        \+ member(EstatSeguent, CamiFinsAra),
        CostMax1 is CostMax-CostPas,
        cami(CostMax1, EstatSeguent, EstatFinal, [EstatSeguent|CamiFinsAra], CamiTotal).



% 1. Un misioner travessa el riu sol.
unPas(1, [M1, C1, esq, M2, C2], [M3, C1, dreta, M4, C2]) :- 
        M3 is M1-1, M4 is M2+1,
        M3 >= 0, M4 >= 0,
        (M3 = 0; M3 >= C1),
        (M4 = 0; M4 >= C2).
% 2. Un canival travesa el riu.
unPas(1, [M1, C1, esq, M2, C2], [M1, C3, dreta, M2, C4]) :- 
        C3 is C1 - 1, C4 is C2 + 1,
        C3 >= 0, C4 >= 0,
        (M1 = 0; C3 =< M1),
        (M2 = 0; C4 =< M2).
% 3. Dos missioners travessen el riu.
unPas(1, [M1, C1, esq, M2, C2], [M3, C1, dreta, M4, C2]) :- 
        M3 is M1-2, M4 is M2+2,
        M3 >= 0, M4 >= 0,
        (M3 = 0; M3 >= C1),
        (M4 = 0; M4 >= C2).
% 4. Dos canibals travessen el riu.
unPas(1, [M1, C1, esq, M2, C2], [M1, C3, dreta, M2, C4]) :- 
        C3 is C1 - 2, C4 is C2 + 2,
        C3 >= 0, C4 >= 0,
        (M1 = 0; C3 =< M1),
        (M2 = 0; C4 =< M2).
% 5. Un misioner i un canibal travessen el riu.
unPas(1, [M1, C1, esq, M2, C2], [M3, C3, dreta, M4, C4]) :- 
        M3 is M1 - 1, M4 is M2 + 1,
        C3 is C1 - 1, C4 is C2 + 1,
        M3 >= 0, M4 >= 0,
        C3 >= 0, C4 >= 0,
        (M3 = 0; M3 >= C3),
        (M4 = 0; M4 >= C4).


% 1. Un misioner torna sol.
unPas(1, [M1, C1, dreta, M2, C2], [M3, C1, esq, M4, C2]) :- 
        M3 is M1+1, M4 is M2-1,
        M3 >= 0, M4 >= 0,
        (M3 = 0; M3 >= C1),
        (M4 = 0; M4 >= C2).
% 2. Un canival torna sol.
unPas(1, [M1, C1, dreta, M2, C2], [M1, C3, esq, M2, C4]) :- 
        C3 is C1 + 1, C4 is C2 - 1,
        C3 >= 0, C4 >= 0,
        (M1 = 0; C3 =< M1),
        (M2 = 0; C4 =< M2).
% 3. Dos missioners tornen.
unPas(1, [M1, C1, dreta, M2, C2], [M3, C1, esq, M4, C2]) :- 
        M3 is M1+2, M4 is M2-2,
        M3 >= 0, M4 >= 0,
        (M3 = 0; M3 >= C1),
        (M4 = 0; M4 >= C2).
% 4. Dos canibals tornen.
unPas(1, [M1, C1, dreta, M2, C2], [M1, C3, esq, M2, C4]) :- 
        C3 is C1 + 2, C4 is C2 - 2,
        C3 >= 0, C4 >= 0,
        (M1 = 0; C3 =< M1),
        (M2 = 0; C4 =< M2).
% 5. Un misioner i un canibal tornen.
unPas(1, [M1, C1, dreta, M2, C2], [M3, C3, esq, M4, C4]) :- 
        M3 is M1 + 1, M4 is M2 - 1,
        C3 is C1 + 1, C4 is C2 - 1,
        M3 >= 0, M4 >= 0,
        C3 >= 0, C4 >= 0,
        (M3 = 0; M3 >= C3),
        (M4 = 0; M4 >= C4).