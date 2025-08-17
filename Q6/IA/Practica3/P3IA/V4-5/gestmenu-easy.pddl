(define (problem gestmenu-easy)
  (:domain GestMenu)

  (:objects
    ;; días laborables
    lunes martes miercoles jueves viernes - dia

    ;; 25 primeros
        chicken-fajitas
    tuna-sashimi
    barbecue-ribs
    vegetable-soup
    chilli-con-carne
    linguine-with-clams
    pork-belly-buns
    mushroom-risotto
    pork-belly-buns
    philadelphia-maki
    califlower-penne
    katsu-curry
    souvlaki
    pizza
    cheeseburger
    barbecue-ribs
    lasagne
    california-maki
    fettuccine-alfredo
    mushroom-risotto
    ebiten-maki
    fettuccine-alfredo
    salmon-nigiri
    linguine-with-clams
    tuna-sashimi                         - primero

    ;; 25 segundos
        french-fries-with-sausages
    risotto-with-seafood
    teriyaki-chicken-donburi
    california-maki
    pork-belly-buns
    califlower-penne
    vegetable-soup
    barbecue-ribs
    philadelphia-maki
    meatballs-with-sauce
    califlower-penne
    katsu-curry
    chicken-wings
    califlower-penne
    ebiten-maki
    mushroom-risotto
    souvlaki
    pasta-carbonara
    califlower-penne
    chilli-con-carne
    ebiten-maki
    fish-and-chips
    katsu-curry
    pasta-carbonara
    pork-belly-buns                - segundo
  )

(:init

  ;; Calorias de los platos
  (=(calorias chicken-fajitas) 998)
  (=(calorias tuna-sashimi) 1104)
  (=(calorias barbecue-ribs) 897)
  (=(calorias vegetable-soup) 978)
  (=(calorias chilli-con-carne) 1099)
  (=(calorias linguine-with-clams) 1154)
  (=(calorias pork-belly-buns) 289)
  (=(calorias mushroom-risotto) 300)
  (=(calorias pork-belly-buns) 289)
  (=(calorias philadelphia-maki) 838)
  (=(calorias califlower-penne) 480)
  (=(calorias katsu-curry) 1172)
  (=(calorias souvlaki) 660)
  (=(calorias pizza) 575)
  (=(calorias cheeseburger) 654)
  (=(calorias barbecue-ribs) 897)
  (=(calorias lasagne) 247)
  (=(calorias california-maki) 653)
  (=(calorias fettuccine-alfredo) 620)
  (=(calorias mushroom-risotto) 300)
  (=(calorias ebiten-maki) 501)
  (=(calorias fettuccine-alfredo) 620)
  (=(calorias salmon-nigiri) 1173)
  (=(calorias linguine-with-clams) 1154)
  (=(calorias tuna-sashimi) 1104)
  (=(calorias french-fries-with-sausages) 784)
  (=(calorias risotto-with-seafood) 534)
  (=(calorias teriyaki-chicken-donburi) 202)
  (=(calorias california-maki) 653)
  (=(calorias pork-belly-buns) 289)
  (=(calorias califlower-penne) 480)
  (=(calorias vegetable-soup) 978)
  (=(calorias barbecue-ribs) 897)
  (=(calorias philadelphia-maki) 838)
  (=(calorias meatballs-with-sauce) 339)
  (=(calorias califlower-penne) 480)
  (=(calorias katsu-curry) 1172)
  (=(calorias chicken-wings) 840)
  (=(calorias califlower-penne) 480)
  (=(calorias ebiten-maki) 501)
  (=(calorias mushroom-risotto) 300)
  (=(calorias souvlaki) 660)
  (=(calorias pasta-carbonara) 501)
  (=(calorias califlower-penne) 480)
  (=(calorias chilli-con-carne) 1099)
  (=(calorias ebiten-maki) 501)
  (=(calorias fish-and-chips) 931)
  (=(calorias katsu-curry) 1172)
  (=(calorias pasta-carbonara) 501)
  (=(calorias pork-belly-buns) 289)

  ;;Precio plato
  ;; precios de los primeros
(= (preu chicken-fajitas) 2.78)
(= (preu tuna-sashimi) 3.83)
(= (preu barbecue-ribs) 24.53)
(= (preu vegetable-soup) 13.2)
(= (preu chilli-con-carne) 14.13)
(= (preu linguine-with-clams) 3.17)
(= (preu pork-belly-buns) 13.02)
(= (preu mushroom-risotto) 18.11)
(= (preu pork-belly-buns) 13.02)
(= (preu philadelphia-maki) 9.9)
(= (preu califlower-penne) 4.79)
(= (preu katsu-curry) 4.91)
(= (preu souvlaki) 8.99)
(= (preu pizza) 3.47)
(= (preu cheeseburger) 2.59)
(= (preu barbecue-ribs) 24.53)
(= (preu lasagne) 2.83)
(= (preu california-maki) 20.24)
(= (preu fettuccine-alfredo) 2.71)
(= (preu mushroom-risotto) 18.11)
(= (preu ebiten-maki) 9.37)
(= (preu fettuccine-alfredo) 2.71)
(= (preu salmon-nigiri) 2.04)
(= (preu linguine-with-clams) 3.17)
(= (preu tuna-sashimi) 3.83)

;; precios de los segundos
(= (preu french-fries-with-sausages) 15.03)
(= (preu risotto-with-seafood) 6.29)
(= (preu teriyaki-chicken-donburi) 13.82)
(= (preu california-maki) 20.24)
(= (preu pork-belly-buns) 13.02)
(= (preu califlower-penne) 4.79)
(= (preu vegetable-soup) 13.2)
(= (preu barbecue-ribs) 24.53)
(= (preu philadelphia-maki) 9.9)
(= (preu meatballs-with-sauce) 22.0)
(= (preu califlower-penne) 4.79)
(= (preu katsu-curry) 4.91)
(= (preu chicken-wings) 8.77)
(= (preu califlower-penne) 4.79)
(= (preu ebiten-maki) 9.37)
(= (preu mushroom-risotto) 18.11)
(= (preu souvlaki) 8.99)
(= (preu pasta-carbonara) 8.93)
(= (preu califlower-penne) 4.79)
(= (preu chilli-con-carne) 14.13)
(= (preu ebiten-maki) 9.37)
(= (preu fish-and-chips) 15.77)
(= (preu katsu-curry) 4.91)
(= (preu pasta-carbonara) 8.93)
(= (preu pork-belly-buns) 13.02)

  ;;Calorias del dia
    (= (calorias-dia lunes) 0)
    (= (calorias-dia martes) 0)
    (= (calorias-dia miercoles) 0)
    (= (calorias-dia jueves) 0)
    (= (calorias-dia viernes) 0)
    (= (preuTotal) 0)
  
  ;; incompatibilidades primero vs. segundo
  (incompatible tuna-sashimi ebiten-maki)
  (incompatible califlower-penne ebiten-maki)
  (incompatible tuna-sashimi ebiten-maki)
  (incompatible tuna-sashimi mushroom-risotto)
  (incompatible tuna-sashimi chicken-wings)

  ;; platos del mismo "giro" (para mismoTipo)
  (mismoTipo mushroom-risotto salmon-nigiri)
  (mismoTipo barbecue-ribs lasagne)
  (mismoTipo chilli-con-carne pasta-carbonara)
  (mismoTipo french-fries-with-sausages teriyaki-chicken-donburi)
  
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
      (assignado-primero miercoles mushroom-risotto)
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
