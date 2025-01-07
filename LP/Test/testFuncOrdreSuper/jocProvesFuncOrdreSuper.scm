
(define (aplica-dos-cops f x)
  (f (f x)))
(define (dobla x) (* x 2))

(define (map func llista)
  (cond
    ((null? llista) '())
    (else (cons (func (car llista)) (map func (cdr llista))))))

(define (filter predicat llista)
  (cond
    ((null? llista) '())  ;
    ((predicat (car llista))
     (cons (car llista) (filter predicat (cdr llista))))
    (#t (filter predicat (cdr llista)))))  

(define (parell? x) (= (mod x 2) 0))


(define (main)
    (display "Joc de proves per operacions d'ordre superior i del main")
    (newline)
    (display "Prova de la funcio aplica-dos-cops, dobla, map i filter")
    (newline)
    (display (aplica-dos-cops dobla 5))
    (newline)
    (display (map dobla '(1 2 3 4)))
    (newline)
    (display (filter parell? '(1 2 3 4)))
    (newline)
  )

; 20
; (2 4 6 8)
; (2 4)