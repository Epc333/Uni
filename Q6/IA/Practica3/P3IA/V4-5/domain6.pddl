;==================================================================
; GestMenu.pddl
; Dominio para gestionar menús semanales con restricción de tipos
;==================================================================

(define (domain GestMenu)
  (:requirements :strips :adl :typing :equality :fluents)

  (:types
    plato dia
    primero segundo    - plato
  )

  (:functions
    ;; calorías de cada plato
    (calorias   ?p - plato)
    ;; suma de calorías consumidas en un día
    (calorias-dia ?d - dia)
    ;; precio de cada plato
    (preu ?p - plato)
    ;; suma de precios de platos de todo el menu semanal
    (preuTotal)
  )


  (:predicates
    ;; Flags de hueco libre/ocupado
    (hayprimero        ?d - dia)
    (haysegundo        ?d - dia)

    ;; Asignación concreta
    (assignado-primero ?d - dia    ?p - primero)
    (assignado-segundo ?d - dia    ?s - segundo)

    ;; No repetir el mismo plato en la semana
    (assignado         ?p - plato)

    ;; Control de repetición de “giro” entre días consecutivos
  
    (diaConsecutivo    ?d1 - dia   ?d2 - dia)
    (diaInicial        ?d - dia)            ;para indicar el primer día de la semana
    ;; Repetición de tipo de plato
    (mismoTipo         ?p1 - plato ?p2 - plato)
    ;; Incompatibilidades primer vs. segundo
    (incompatible      ?p - primero ?s - segundo)
    ;; Para imprimir mas legible
    (impres ?d)
  )

  ;;----------------------------------------------------------------------  
  ;; Acción para el primer día (lunes, marcado con diaInicial)
  ;;----------------------------------------------------------------------  
  (:action assignar-primero-inicial
    :parameters (?d - dia ?p - primero)
    :precondition (and
      (diaInicial ?d)
      (not (hayprimero ?d))
      (not (assignado ?p))
    )
    :effect (and
      (hayprimero        ?d)
      (assignado-primero ?d ?p)
      (assignado         ?p)
      (increase (calorias-dia ?d) (calorias ?p))
      (increase (preuTotal) (preu ?p)) 
    )
  )

  ;;----------------------------------------------------------------------  
  ;; Acción para cualquier otro día, evitando repetir tipo de primero
  ;;----------------------------------------------------------------------  
  (:action assignar-primero
    :parameters (?d - dia ?p - primero ?dprev - dia ?p2 - primero)
    :precondition (and
      (not (diaInicial ?d))
      (diaConsecutivo    ?dprev ?d)
      (assignado-primero ?dprev ?p2)
      (not (hayprimero   ?d))
      (not (assignado    ?p))
      (not (or (mismoTipo    ?p ?p2) (mismoTipo ?p2 ?p)))
    )
    :effect (and
      (hayprimero        ?d)
      (assignado-primero ?d ?p)
      (assignado         ?p)
      (increase (calorias-dia ?d) (calorias ?p))
      (increase (preuTotal) (preu ?p))
    )
  )

  ;;----------------------------------------------------------------------  
  ;; Acción para el segundo en el primer día
  ;;----------------------------------------------------------------------  
  (:action assignar-segundo-inicial
    :parameters (?d - dia ?p1 - primero ?s - segundo)
    :precondition (and
      (diaInicial ?d)
      (assignado-primero ?d ?p1)
      (not (haysegundo   ?d))
      (not (assignado    ?s))
      (not (incompatible ?p1 ?s))
    )
    :effect (and
      (haysegundo        ?d)
      (assignado-segundo ?d ?s)
      (assignado         ?s)
      (increase (calorias-dia ?d) (calorias ?s))
      (increase (preuTotal) (preu ?s))
    )
  )

  ;;----------------------------------------------------------------------  
  ;; Acción para cualquier otro día, evitando incompatibles y repetir tipo
  ;;----------------------------------------------------------------------  
  (:action assignar-segundo
    :parameters (?d - dia ?p1 - primero ?s - segundo ?dprev - dia ?s2 - segundo)
    :precondition (and
      (not (diaInicial      ?d))
      (diaConsecutivo       ?dprev ?d)
      (assignado-primero    ?d ?p1)
      (assignado-segundo    ?dprev ?s2)
      (not (haysegundo      ?d))
      (not (assignado       ?s))
      (not (incompatible    ?p1 ?s))
      (not (or (mismoTipo    ?s ?s2) (mismoTipo ?s2 ?s)))
    )
    :effect (and
      (haysegundo        ?d)
      (assignado-segundo ?d ?s)
      (assignado         ?s)
      (increase (calorias-dia ?d) (calorias ?s))
      (increase (preuTotal) (preu ?s))
    )
  )

  (:action printar
      :parameters (?p - primero ?s - segundo ?d - dia)
      :precondition (and (assignado-primero ?d ?p) (assignado-segundo ?d ?s) (not (impres ?d)))
      :effect (and (impres ?d))
  )
  
)
