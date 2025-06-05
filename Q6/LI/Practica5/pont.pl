% Pont de nit: tracta d’esbrinar la manera més ràpida que tenen quatre persones P1,
% P2, P5 i P8 per a creuar de nit un pont que només aguanta el pes de dues, on tenen una única i
% imprescindible llanterna i cada Pi triga i minuts a creuar. Dues juntes triguen com la més lenta
% de les dues.

main :- EstatInicial = [ [1,2,5,8], e, []],    EstatFinal = [ [], d, [1,2,5,8]],
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

%unPas(...) :- ...
%...

% 1. Creua una persona
unPas(M, [LIn, e, LF], [L2, d, LF2]) :-
    select(M, LIn, L2),
    append(LF, [M], TMP), sort(TMP, LF2).

% 2. Creuen dues persones
unPas(M, [LIn, e, LF], [L2, d, LF2]) :-
    select(E1, LIn, Rest),
    select(E2, Rest, L2),
    M is max(E1, E2),
    append(LF, [E1, E2], TMP), sort(TMP, LF2).

% 3. Torna una persona
unPas(M, [LIn, d, LF], [L2, e, LF2]) :-
    select(M, LF, LF2),
    append(LIn, [M], TMP), sort(TMP, L2).

% 4. Tornen dues persones
unPas(M, [LIn, d, LF], [L2, e, LF2]) :-
    select(E1, LF, Rest),
    select(E2, Rest, LF2),
    M is max(E1, E2),
    append(LIn, [E1, E2], TMP), sort(TMP, L2).