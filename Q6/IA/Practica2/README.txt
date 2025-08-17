INFORMACIÓN DEL PRIMER PROTOTIPO:

    El sistema tiene en cinco clases:
    - Bebida
    - Vino
    - Época
    - Ingrediente
    - Plato

    No se han modelado las clases Evento ni Menú explícitamente, ya que:
    - Evento es tratado como la entrada del usuario.
    - Menú es el resultado que genera el sistema.

    El sistema está organizado en cinco módulos secuenciales:

    1. Módulo de Input
    Recopila la información proporcionada por el usuario:
    - Nombre del evento
    - Fecha
    - Localidad
    - Tipo de evento
    - Presupuesto
    - Número de comensales
    - Restricciones dietéticas

    Esta información se almacena en el template InfoEvento.

    2. Módulo de Abstracción
    Procesa los datos de entrada para deducir información relevante. Por ejemplo:
    - A partir de la fecha 01/07/2025, se deduce que la estación es verano.

    La información procesada se guarda en el template InfoEventoA.

    3. Módulo de Asociación Heurística
    Crea un nuevo template SolucionAbstracta donde guarda las características del menú.
    Ejemplo:
    - Si es verano -> Temperatura menú = Fresco

    4. Módulo de Refinamiento
    Se recorren todas las instancias de platos y se puntúan según:
    - Coincidencia con los atributos de SolucionAbstracta (+ puntuación).
    - Incompatibilidades con las restricciones dietéticas (- puntuación).

    Platos con puntuación > -1000 se almacenan en CandidateMenu.

    De ahí, se selecciona los tres mejores platos de cada tipo (principal, segundo, postre) y se guardan en los templates SelectedMenu.

    5. Módulo de Impresión de la Solución
    Se muestra al usuario la propuesta final de los menus (SelectedMenu).

CÓMO EJECUTAR EL SISTEMA

    1. Abrir CLIPS en el terminal.
    2. Ejecutar los siguientes comandos:

    (clear)
    (load RicoRico.clp)
    (reset)
    (run)


    3. Introducir los datos solicitados. Por ejemplo:

    Cumple Lola  
    España  
    cumpleaños  
    17/07/2025  
    30  
    15  
    vegetariana  

FUNCIONALIDADES PENDIENTES

    - Gestionar bebidas (aún no implementado).
    - Ajustar mejor las puntuaciones para mejorar la selección de platos.
    - Ajustar los 3 menus para que sean el caro, el medio y el barato.

