(define (problem gestmenu-prob3)
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
  ;; incompatibilidades primero vs. segundo
  (incompatible crema-zanahoria paella-seg)
  (incompatible gazpacho pescado-horno)
  (incompatible sopa-minestrone fabada-asturiana)

  ;; platos del mismo “giro” (para mismoTipo)
  (mismoTipo gazpacho salmorejo)
  (mismoTipo paella-seg arroz-negro)
  (diaInicial lunes)

  ;; días consecutivos
  (diaConsecutivo lunes martes)
  (diaConsecutivo martes miercoles)
  (diaConsecutivo miercoles jueves)
  (diaConsecutivo jueves viernes)
)
  (:goal
    (and
      ;; queremos un primero y un segundo para cada día
      (hayprimero   lunes)   (haysegundo   lunes)
      (hayprimero   martes)  (haysegundo   martes)
      (hayprimero   miercoles)(haysegundo  miercoles)
      (hayprimero   jueves)  (haysegundo   jueves)
      (hayprimero   viernes) (haysegundo   viernes)
      (impres lunes) (impres martes) (impres miercoles) (impres jueves) (impres viernes)
      (assignado-primero lunes pisto)
    )
  )
)
