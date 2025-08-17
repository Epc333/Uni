(define (domain menu-week)

(:requirements :typing :adl :fluents)

(:types 
    plate day type
    first second - plate
)

; Definición de constantes para los días de la semana
(:constants 
    monday tuesday wednesday thursday friday - day
)

(:predicates
    ; assigned-first: El primer plato ?f está asignado al día ?d
    (assigned-first ?f - plate ?d - day)
    ; assigned-second: El segundo plato ?s está asignado al día ?d
    (assigned-second ?s - plate ?d - day)
    ; assigned-first-day: El día ?d ya tiene un primer plato asignado
    (assigned-first-day ?d - day)
    ; assigned-second-day: El día ?d ya tiene un segundo plato asignado
    (assigned-second-day ?d - day)
    ; incompatible: El primer plato ?f y el segundo plato ?s son incompatibles
    (incompatible ?f - first ?s - second)
    ; used: El plato ?p ya ha sido usado en la semana
    (used ?p - plate)
    ; previous-day: ?d1 es el día siguiente a ?d2
    (previous-day ?d1 - day ?d2 - day)
    ; same-type: Los platos ?p1 y ?p2 son del mismo tipo
    (same-type ?p1 - plate ?p2 - plate)
    ; menu-displayed: El menú del día ?d ya ha sido mostrado
    (menu-displayed ?d - day)
)

(:functions
    (calories ?p - plate)
    (price ?p - plate)
    (total-price)
)

(:action display-menu-day
    :parameters (?d - day ?f - first ?s - second)
    :precondition (and 
        (assigned-first ?f ?d)
        (assigned-second ?s ?d)
    )
    :effect (and 
        (menu-displayed ?d)
    )
)

(:action assign-menu
    :parameters (?d - day ?f - first ?s - second ?prevd - day ?fprev - first ?sprev - second)
    :precondition (and 
        (not (assigned-first-day ?d))
        (not (assigned-second-day ?d))
        (not (incompatible ?f ?s))
        (not (used ?f))
        (not (used ?s))

        (or 
            (= ?d monday)
            (and
                (previous-day ?d ?prevd)
                (assigned-first ?fprev ?prevd)
                (assigned-second ?sprev ?prevd)
                (not 
                    (or
                        (same-type ?fprev ?f)
                        (same-type ?f ?fprev)
                    )
                )
                (not 
                    (or
                        (same-type ?sprev ?s)
                        (same-type ?s ?sprev)
                    )
                )
            )    
        )
        (>= (+ (calories ?f) (calories ?s)) 1000)
        (<= (+ (calories ?f) (calories ?s)) 1500)
    )
    :effect (and 
        (assigned-first ?f ?d)
        (assigned-second ?s ?d)
        (assigned-first-day ?d)
        (assigned-second-day ?d)
        (used ?f)
        (used ?s)
        (increase (total-price) (price ?f))
        (increase (total-price) (price ?s))
    )

)

)