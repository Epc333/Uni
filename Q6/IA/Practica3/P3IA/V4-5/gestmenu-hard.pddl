(define (problem gestmenu-hard)
  (:domain GestMenu)

  (:objects
    ;; días laborables
    lunes martes miercoles jueves viernes - dia

    ;; 15 primeros
        salmon-nigiri
    philadelphia-maki
    fettuccine-alfredo
    fish-and-chips
    ebiten-maki
    chicken-fajitas
    fish-and-chips
    risotto-with-seafood
    katsu-curry
    meatballs-with-sauce
    caesar-salad
    souvlaki
    scotch-eggs
    tiramisù
    chicken-milanese                         - primero

    ;; 15 segundos
        fish-and-chips
    caesar-salad
    fettuccine-alfredo
    souvlaki
    teriyaki-chicken-donburi
    salmon-nigiri
    califlower-penne
    salmon-nigiri
    scotch-eggs
    bruschette-with-tomato
    tiramisù
    scotch-eggs
    french-fries-with-sausages
    tiramisù
    california-maki                - segundo
  )

(:init

  ;; Calorias de los platos
  (=(calorias salmon-nigiri) 201)
  (=(calorias philadelphia-maki) 312)
  (=(calorias fettuccine-alfredo) 365)
  (=(calorias fish-and-chips) 1013)
  (=(calorias ebiten-maki) 327)
  (=(calorias chicken-fajitas) 1091)
  (=(calorias fish-and-chips) 1013)
  (=(calorias risotto-with-seafood) 974)
  (=(calorias katsu-curry) 414)
  (=(calorias meatballs-with-sauce) 783)
  (=(calorias caesar-salad) 777)
  (=(calorias souvlaki) 289)
  (=(calorias scotch-eggs) 398)
  (=(calorias tiramisù) 861)
  (=(calorias chicken-milanese) 832)
  (=(calorias fish-and-chips) 1013)
  (=(calorias caesar-salad) 777)
  (=(calorias fettuccine-alfredo) 365)
  (=(calorias souvlaki) 289)
  (=(calorias teriyaki-chicken-donburi) 745)
  (=(calorias salmon-nigiri) 201)
  (=(calorias califlower-penne) 874)
  (=(calorias salmon-nigiri) 201)
  (=(calorias scotch-eggs) 398)
  (=(calorias bruschette-with-tomato) 697)
  (=(calorias tiramisù) 861)
  (=(calorias scotch-eggs) 398)
  (=(calorias french-fries-with-sausages) 305)
  (=(calorias tiramisù) 861)
  (=(calorias california-maki) 616)

  ;;Precio plato
  ;; precios de los primeros
(= (preu salmon-nigiri) 23.64)
(= (preu philadelphia-maki) 2.95)
(= (preu fettuccine-alfredo) 7.27)
(= (preu fish-and-chips) 14.2)
(= (preu ebiten-maki) 3.2)
(= (preu chicken-fajitas) 3.51)
(= (preu fish-and-chips) 14.2)
(= (preu risotto-with-seafood) 3.5)
(= (preu katsu-curry) 2.8)
(= (preu meatballs-with-sauce) 2.89)
(= (preu caesar-salad) 4.66)
(= (preu souvlaki) 5.73)
(= (preu scotch-eggs) 12.03)
(= (preu tiramisù) 23.49)
(= (preu chicken-milanese) 2.71)

;; precios de los segundos
(= (preu fish-and-chips) 14.2)
(= (preu caesar-salad) 4.66)
(= (preu fettuccine-alfredo) 7.27)
(= (preu souvlaki) 5.73)
(= (preu teriyaki-chicken-donburi) 20.14)
(= (preu salmon-nigiri) 23.64)
(= (preu califlower-penne) 15.16)
(= (preu salmon-nigiri) 23.64)
(= (preu scotch-eggs) 12.03)
(= (preu bruschette-with-tomato) 21.67)
(= (preu tiramisù) 23.49)
(= (preu scotch-eggs) 12.03)
(= (preu french-fries-with-sausages) 10.9)
(= (preu tiramisù) 23.49)
(= (preu california-maki) 6.94)

  ;;Calorias del dia
    (= (calorias-dia lunes) 0)
    (= (calorias-dia martes) 0)
    (= (calorias-dia miercoles) 0)
    (= (calorias-dia jueves) 0)
    (= (calorias-dia viernes) 0)
    (= (preuTotal) 0)
  
  ;; incompatibilidades primero vs. segundo
  (incompatible ebiten-maki fish-and-chips)
  (incompatible katsu-curry teriyaki-chicken-donburi)
  (incompatible fish-and-chips bruschette-with-tomato)
  (incompatible meatballs-with-sauce caesar-salad)
  (incompatible salmon-nigiri caesar-salad)

  ;; platos del mismo "giro" (para mismoTipo)
  (mismoTipo tiramisù chicken-milanese)
  (mismoTipo fish-and-chips chicken-fajitas)
  (mismoTipo fettuccine-alfredo fish-and-chips)
  (mismoTipo bruschette-with-tomato scotch-eggs)
  
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
      (hayprimero lunes)   (haysegundo lunes)
      (hayprimero martes)   (haysegundo martes)
      (hayprimero miercoles)   (haysegundo miercoles)
      (hayprimero jueves)   (haysegundo jueves)
      (hayprimero viernes)   (haysegundo viernes)
      (impres lunes)
      (impres martes)
      (impres miercoles)
      (impres jueves)
      (impres viernes)
      (assignado-primero lunes fish-and-chips)
    (>= (calorias-dia lunes) 1000)
    (<= (calorias-dia lunes) 1500)
    (>= (calorias-dia martes) 1000)
    (<= (calorias-dia martes) 1500)
    (>= (calorias-dia miercoles) 1000)
    (<= (calorias-dia miercoles) 1500)
    (>= (calorias-dia jueves) 1000)
    (<= (calorias-dia jueves) 1500)
    (>= (calorias-dia viernes) 1000)
    (<= (calorias-dia viernes) 1500)
    )
  )

  (:metric minimize (preuTotal))
)
