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

  ;; Calorias de los platos
  (=(calorias crema-zanahoria) 200)
  (=(calorias gazpacho) 350)
  (=(calorias ensalada-cesar) 450)
  (=(calorias sopa-minestrone) 500)
  (=(calorias salmorejo) 450)
  (=(calorias ensalada-pasta) 400)
  (=(calorias pisto) 600)
  (=(calorias paella-seg) 500)
  (=(calorias arroz-negro) 950)
  (=(calorias pollo-asado) 700)
  (=(calorias pescado-horno) 600)
  (=(calorias fabada-asturiana) 750)
  (=(calorias tortilla-patatas) 800)
  (=(calorias filete-ternera) 1001)

  ;;Calorias del dia
    (= (calorias-dia lunes)   0)
    (= (calorias-dia martes)  0)
    (= (calorias-dia miercoles) 0)
    (= (calorias-dia jueves)  0)
    (= (calorias-dia viernes) 0)
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
    (>= (calorias-dia lunes)   1000) (<= (calorias-dia lunes)   1500)
    (>= (calorias-dia martes)  1000) (<= (calorias-dia martes)  1500)
    (>= (calorias-dia miercoles)1000) (<= (calorias-dia miercoles)1500)
    (>= (calorias-dia jueves)  1000) (<= (calorias-dia jueves)  1500)
    (>= (calorias-dia viernes) 1000) (<= (calorias-dia viernes) 1500)
    )
  )
)
