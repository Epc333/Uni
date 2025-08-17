(defmodule preguntas (export ?ALL))

(defmodule preguntas
    (import MAIN ?ALL)
    (export ?ALL)
)

(defrule preguntas::main_rule
	(declare (salience 10))
	=> 
	(preguntar_dieta)
	(focus construct)
)


(deffunction preguntas::preguntar_dieta ()
   (bind ?respuesta (pregunta "Que dieta sigue? ¿vegana o vegetariana" vegana vegetariana))

   ;; calculamos TRUE/FALSE
   (bind ?es-vegetariana (eq ?respuesta vegetariana))
   (bind ?es-vegana      (eq ?respuesta vegana))

    (make-instance dieta of Dieta 
                  (Nombre       "dieta")
                  (Vegetariana  ?es-vegetariana)
                  (Vegana       ?es-vegana))
)


(deffunction preguntas::pregunta (?pregunta $?valores)
    (progn$
        (?var ?valores)
        (lowcase ?var))
    (format t "¿%s? (%s) " ?pregunta (implode$ ?valores))
    (bind ?respuesta (read))
    (while (not (member$ (lowcase ?respuesta) ?valores)) do
        (format t "¿%s? (%s) " ?pregunta (implode$ ?valores))
        (bind ?respuesta (read))
    )
  ?respuesta
)


