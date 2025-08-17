

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
    (assignado ?p - plato)
    (incompatible      ?p - primero ?s - segundo)
)



(:action assignarPrimero
    :parameters (?d - dia ?p - primero)
    :precondition (and (not (hayprimero ?d)) (not (assignado ?p)))
    :effect (and (hayprimero ?d) (assignado-primero ?d ?p) (assignado ?p))
)

(:action assignarSegundo
    :parameters (?d - dia ?se - segundo ?pr - primero)
    :precondition (and (assignado-primero ?d ?pr) (not (haysegundo ?d)) (not (incompatible ?pr ?se)) (not (assignado ?se)))
    :effect (and (haysegundo ?d) (assignado-segundo ?d ?se) (assignado ?se))
)


)

