# Mini Scheme

Aquest projecte és un mini intèrpret de Scheme implementat amb Python utilitzant ANTLR4.


## Descripció

L'intèrpret suporta operacions i funcions bàsiques d'Scheme que inclouen:
- Operacions aritmètiques
- Comparacions
- Operacions amb booleans
- Definició de funcions i constants
- Condicionals (if, cond)
- Operacions amb llistes
- Variables locals amb let
- Operacions d'entrada/sortida
- Funcions d'ordre superior

## Instal·lació

Generar el parser de la grmàtica.
```bash
make parser
```

## Utilització:
Per compilar el fitxer scheme.g4:
```bash
make parser
```
Per utilitzar l'intèrpret (primer s'ha d'executa make parser):
```bash
python3 scheme.py input_file    #El fitxer d'entrada ha de ser un .scm
```

Per netejar el directori:
```bash
make clean
```
Eliminarà els fitxers creats al compilar el fitxer .g4

## Característiques

- Operacions aritmètiques (+, -, /, *, mod):
```scheme
(+ 3 2)     ;Resultat: 5
```

- Comparacions (=, <>, <=, <, >, >=):
```scheme
(= 3 2)     ;Resultat: #f
```

- Operacions amb boleans (and, or, not):
```scheme
(not #t)    ;Resultat: #f
```

- Definició de funcions:
```scheme
(define (resta x y)
  (- x y))
```
- Definició de constants:
```scheme
(define y 5) ; y = 5
(define llista '(1, 2)) ;llista = [1,2]
```

- Operacions amb llistes (car, dr, cons, null?)
```scheme
(define llista '(1 2 3 4 5))
(car llista) ; Resultat: 1
(cdr llista) ; Resultat: (2 3 4 5)
(cons 0 llista) ; Resultat: (0 1 2 3 4 5)
(null? '()) ; Resultat: #t
(null? llista) ; Resultat: #f
```

- Operacions d'entrada i sortida (display, read, newline):
```scheme
(display "Text d'exemple")  ;Escriura per sortida "Text d'exemple"
(define x (read))           ; x = Entrada per canal estàndar
```

- Condicionals (if, cond):
```scheme
(if (= 1 1)
    "si"
    "no")  ; Resultat: "si"

(cond
  ((= 3 5) "igual")
  ((< 3 5) "menor")
  ((> 3 5) "major")) ; Resultat: "menor"
```

- Operacions d'ordre superior:
```scheme
(define (aplica-dos-cops f x)
  (f (f x)))
```

- Variable locals amb let:
```scheme
(let ((x 5)
     (y 3))
    (- x y))  ;Resultat: 2
```

## Observacions
- Escriure sense accents, si no no reconeixerà el caràcter

## Autor
Eudald Pizarro Camí (eudald.pizarro@estudiantat.upc.edu)