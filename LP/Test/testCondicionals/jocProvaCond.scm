(display "Joc de proves dels condicionals i booleans")
(newline)

(display "Prova de la condicio if")
(newline)
(display "Si la condicio es certa, es mostra el primer missatge")
(newline)
(if #t
    (display "La condicio es certa")
    (display "La condicio es falsa"))  
(newline)

(display "Si la condicio es falsa, es mostra el segon missatge")
(newline)
(display "Avaluarem la condicio not (true or false)")
(newline)
(if (not (or #t #f))
    (display "La condicio es certa")
    (display "La condicio es falsa"))
(newline)

(display "Prova de la condicio cond")
(newline)
(cond
    ((= 1 1) (display "1 es igual a 1"))
    ((= 1 2) (display "1 es igual a 2"))
    (else (display "No es compleix cap condicio")))
(newline)

(display "Prova d'and")
(newline)
(display "S'hauria de mostrar el segon missatge")
(newline)
(if (and #t #f)
    (display "La condicio es certa")
    (display "La condicio es falsa"))
(newline)

