(define (problem gestmenu-medium)
  (:domain GestMenu)

  (:objects
    ;; días laborables
    lunes martes miercoles jueves viernes - dia

    ;; 20 primeros
        chicken-milanese
    pappardelle-alla-bolognese
    risotto-with-seafood
    mushroom-risotto
    caesar-salad
    pizza
    fettuccine-alfredo
    califlower-penne
    caprese-salad
    caprese-salad
    souvlaki
    fish-and-chips
    chicken-fajitas
    teriyaki-chicken-donburi
    pork-sausage-roll
    philadelphia-maki
    califlower-penne
    cheeseburger
    ricotta-stuffed-ravioli
    pork-belly-buns                         - primero

    ;; 20 segundos
        barbecue-ribs
    pasta-and-beans
    tiramisù
    chilli-con-carne
    califlower-penne
    ebiten-maki
    salmon-nigiri
    califlower-penne
    lasagne
    souvlaki
    meatballs-with-sauce
    california-maki
    cheeseburger
    mushroom-risotto
    chilli-con-carne
    califlower-penne
    mushroom-risotto
    salmon-nigiri
    fish-and-chips
    califlower-penne                - segundo
  )

(:init

  ;; Calorias de los platos
  (=(calorias chicken-milanese) 1166)
  (=(calorias pappardelle-alla-bolognese) 264)
  (=(calorias risotto-with-seafood) 1007)
  (=(calorias mushroom-risotto) 352)
  (=(calorias caesar-salad) 930)
  (=(calorias pizza) 487)
  (=(calorias fettuccine-alfredo) 1083)
  (=(calorias califlower-penne) 1065)
  (=(calorias caprese-salad) 577)
  (=(calorias caprese-salad) 577)
  (=(calorias souvlaki) 366)
  (=(calorias fish-and-chips) 1136)
  (=(calorias chicken-fajitas) 1009)
  (=(calorias teriyaki-chicken-donburi) 801)
  (=(calorias pork-sausage-roll) 313)
  (=(calorias philadelphia-maki) 871)
  (=(calorias califlower-penne) 1065)
  (=(calorias cheeseburger) 409)
  (=(calorias ricotta-stuffed-ravioli) 672)
  (=(calorias pork-belly-buns) 616)
  (=(calorias barbecue-ribs) 224)
  (=(calorias pasta-and-beans) 1121)
  (=(calorias tiramisù) 625)
  (=(calorias chilli-con-carne) 479)
  (=(calorias califlower-penne) 1065)
  (=(calorias ebiten-maki) 915)
  (=(calorias salmon-nigiri) 998)
  (=(calorias califlower-penne) 1065)
  (=(calorias lasagne) 225)
  (=(calorias souvlaki) 366)
  (=(calorias meatballs-with-sauce) 938)
  (=(calorias california-maki) 981)
  (=(calorias cheeseburger) 409)
  (=(calorias mushroom-risotto) 352)
  (=(calorias chilli-con-carne) 479)
  (=(calorias califlower-penne) 1065)
  (=(calorias mushroom-risotto) 352)
  (=(calorias salmon-nigiri) 998)
  (=(calorias fish-and-chips) 1136)
  (=(calorias califlower-penne) 1065)

  ;;Precio plato
  ;; precios de los primeros
(= (preu chicken-milanese) 2.71)
(= (preu pappardelle-alla-bolognese) 2.9)
(= (preu risotto-with-seafood) 3.21)
(= (preu mushroom-risotto) 21.83)
(= (preu caesar-salad) 3.61)
(= (preu pizza) 2.23)
(= (preu fettuccine-alfredo) 3.43)
(= (preu califlower-penne) 7.76)
(= (preu caprese-salad) 2.12)
(= (preu caprese-salad) 2.12)
(= (preu souvlaki) 12.02)
(= (preu fish-and-chips) 7.33)
(= (preu chicken-fajitas) 2.35)
(= (preu teriyaki-chicken-donburi) 3.35)
(= (preu pork-sausage-roll) 3.56)
(= (preu philadelphia-maki) 2.74)
(= (preu califlower-penne) 7.76)
(= (preu cheeseburger) 23.75)
(= (preu ricotta-stuffed-ravioli) 3.95)
(= (preu pork-belly-buns) 2.97)

;; precios de los segundos
(= (preu barbecue-ribs) 10.82)
(= (preu pasta-and-beans) 7.29)
(= (preu tiramisù) 24.86)
(= (preu chilli-con-carne) 23.85)
(= (preu califlower-penne) 7.76)
(= (preu ebiten-maki) 4.09)
(= (preu salmon-nigiri) 15.7)
(= (preu califlower-penne) 7.76)
(= (preu lasagne) 8.36)
(= (preu souvlaki) 12.02)
(= (preu meatballs-with-sauce) 21.65)
(= (preu california-maki) 11.81)
(= (preu cheeseburger) 23.75)
(= (preu mushroom-risotto) 21.83)
(= (preu chilli-con-carne) 23.85)
(= (preu califlower-penne) 7.76)
(= (preu mushroom-risotto) 21.83)
(= (preu salmon-nigiri) 15.7)
(= (preu fish-and-chips) 7.33)
(= (preu califlower-penne) 7.76)

  ;;Calorias del dia
    (= (calorias-dia lunes) 0)
    (= (calorias-dia martes) 0)
    (= (calorias-dia miercoles) 0)
    (= (calorias-dia jueves) 0)
    (= (calorias-dia viernes) 0)
    (= (preuTotal) 0)
  
  ;; incompatibilidades primero vs. segundo
  (incompatible fettuccine-alfredo salmon-nigiri)
  (incompatible califlower-penne chilli-con-carne)
  (incompatible caprese-salad barbecue-ribs)
  (incompatible chicken-milanese tiramisù)
  (incompatible pappardelle-alla-bolognese salmon-nigiri)

  ;; platos del mismo "giro" (para mismoTipo)
  (mismoTipo fish-and-chips fettuccine-alfredo)
  (mismoTipo pappardelle-alla-bolognese pizza)
  (mismoTipo salmon-nigiri mushroom-risotto)
  (mismoTipo mushroom-risotto cheeseburger)
  
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
      (assignado-primero miercoles philadelphia-maki)
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
