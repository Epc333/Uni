

(define (domain GestMenu)


(:requirements :strips :adl :typing :equality)

(:types 
    plato dia 
    primero segundo - plato 
)


(:predicates
    (assignado-primero ?d - dia   ?p - primero)
    (assignado-segundo ?d - dia   ?s - segundo)
    (hayprimero ?d - dia)
    (haysegundo ?d - dia)
    (incompatible      ?p - primero ?s - segundo)
)


(:action assignarPrimero
    :parameters (?d - dia ?p - primero)
    :precondition (not (hayprimero ?d))
    :effect (and (hayprimero ?d) (assignado-primero ?d ?p))
)

(:action assignarSegundo
    :parameters (?d - dia ?se - segundo ?pr - primero)
    :precondition (and (not (haysegundo ?d)) (assignado-primero ?d ?pr) (not (incompatible ?pr ?se)))
    :effect (and (haysegundo ?d) (assignado-segundo ?d ?se))
)


)

