(define (problem gestmenu-prob2)
  (:domain GestMenu)

  (:objects
    ;; días laborables
    lunes martes miercoles jueves viernes sabado domingo - dia

    ;; 7 primeros
    crema-zanahoria
    gazpacho
    ensalada-cesar
    sopa-minestrone
    salmorejo
    ensalada-pasta
    pisto                         - primero

    ;; 7 segundos
    paella-seg
    arroz-negro
    pollo-asado
    pescado-horno
    fabada-asturiana
    tortilla-patatas
    filete-ternera                - segundo
  )

  (:init
    ;; incompatibilidades entre algunos primeros y segundos
    (incompatible crema-zanahoria paella-seg)
    (incompatible gazpacho pescado-horno)
    (incompatible sopa-minestrone fabada-asturiana)
  )

  (:goal
    (and
      ;; queremos un primero y un segundo para cada día
      (hayprimero   lunes)   (haysegundo   lunes)
      (hayprimero   martes)  (haysegundo   martes)
      (hayprimero   miercoles)(haysegundo  miercoles)
      (hayprimero   jueves)  (haysegundo   jueves)
      (hayprimero   viernes) (haysegundo   viernes)
      (hayprimero   sabado) (haysegundo   sabado)
      (hayprimero   domingo) (haysegundo   domingo)
    )
  )
)
