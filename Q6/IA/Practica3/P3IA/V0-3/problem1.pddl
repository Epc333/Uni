(define (problem gestmenu-prob1)
  (:domain GestMenu)

  (:objects
    ;; los días laborables
    lunes martes miercoles jueves viernes sabado domingo - dia

    ;; ejemplos de primeros
    crema-zanahoria gazpacho ensalada-lechuga - primero

    ;; ejemplos de segundos
    paella pollo-asado pescado-horno        - segundo
  )

  (:init
    ;; incompatibilidades entre primeros y segundos
    (incompatible crema-zanahoria paella)
    (incompatible gazpacho pescado-horno)
    ;; (no hace falta declarar hayprimero/haysegundo: están a false por defecto)
  )

  (:goal
    (and
      ;; para cada día queremos que haya primero y segundo asignado
      (hayprimero lunes)   (haysegundo lunes)
      (hayprimero martes)  (haysegundo martes)
      (hayprimero miercoles) (haysegundo miercoles)
      (hayprimero jueves)  (haysegundo jueves)
      (hayprimero viernes) (haysegundo viernes)
      (hayprimero   sabado) (haysegundo   sabado)
      (hayprimero   domingo) (haysegundo   domingo)
    )
  )
)
