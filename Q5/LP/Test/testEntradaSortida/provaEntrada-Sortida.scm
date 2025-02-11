(display "Joc de proves per operacions d'entrada i sortida")
(newline)
;Comentari, no s'ha d'evaluar

(display "Prova de la funcio read")
(newline)
(display "Introdueix un nombre enter: ")
(define a (read))
(display "El nombre introduit es: ")
(display a)
(newline)

(display "Prova de llegir una cadena de text")
(newline)
(display "Introdueix una cadena de text: ") ;Escriure " "
(define b (read))
(display "La cadena de text introduida es: ")
(display b)
(newline)

(display "Prova de llegir una llista")
(newline)
(display "Introdueix una llista de nombres enters:") ;Escriure ente '( ) separats per ,
(define llista (read))
(display "La llista introduida es: ")
(display llista)
(newline)

(display "Prova de llegir dos nombres seguits:")
(newline)
(define c (read))
(define d (read))
(display "Els nombres introduits son: ")
(display c)
(display " i ")
(display d)
(newline)


;La funció newline i display no les provare explicament ja que ja les he provat en altres jocs de proves
