;;Ontology

;;; ---------------------------------------------------------
;;; RicoRico.clp
;;; Translated by owl2clips
;;; Translated to CLIPS from ontology RicoRico.ttl
;;; :Date 01/05/2025 18:26:53

(defclass Bebida
    (is-a USER)
    (role concrete)
    (pattern-match reactive)
    (slot Nombre
        (type STRING)
        (create-accessor read-write))
    (slot Alcohol
        (type SYMBOL)
        (create-accessor read-write))
    (slot Temperatura
        (type SYMBOL)
        (create-accessor read-write))
    (slot Precio
        (type FLOAT)
        (create-accessor read-write) 
        (default 0.0))
    (slot Formalidad
        (type INTEGER)
        (create-accessor read-write))
    (slot Zona
        (type STRING)
        (create-accessor read-write))
    (slot AptoDiabetico (type SYMBOL) (create-accessor read-write) (default TRUE))
)

(defclass Vino
    (is-a Bebida)
    (role concrete)
    (pattern-match reactive)
)

(defclass Epoca
    (is-a USER)
    (role concrete)
    (pattern-match reactive)
    (slot Nombre
        (type STRING)
        (create-accessor read-write))
)

(defclass Ingrediente
    (is-a USER)
    (role concrete)
    (pattern-match reactive)
    (slot Gluten
        (type SYMBOL)
        (create-accessor read-write))
    (slot Lactosa
        (type SYMBOL)
        (create-accessor read-write))
    (slot Nombre
        (type STRING)
        (create-accessor read-write))
    (slot Vegano
        (type SYMBOL)
        (create-accessor read-write))
    (slot Vegetariano
        (type SYMBOL)
        (create-accessor read-write))
    (slot Halal       (type SYMBOL) (create-accessor read-write) (default TRUE))       
    (slot AptoDiabetico (type SYMBOL) (create-accessor read-write) (default TRUE))     
)

(defclass Plato
    (is-a USER)
    (role concrete)
    (pattern-match reactive)
    (multislot tiene_ingrediente
        (type INSTANCE)
        (create-accessor read-write))
    (multislot en_epoca
        (type INSTANCE)
        (create-accessor read-write))
    (slot Localidad
        (type STRING)
        (create-accessor read-write))
    (slot Nombre
        (type STRING)
        (create-accessor read-write))
    (slot Precio
        (type FLOAT)
        (create-accessor read-write))
    (slot TiempoPreparacion
        (type FLOAT)
        (create-accessor read-write))
    (slot Tipo
        (type STRING)
        (create-accessor read-write))
    (slot Formalidad
        (type INTEGER)
        (create-accessor read-write))

)



;;Definstances

;; Definstances actualizadas con instancias coherentes para la ontología RicoRico
(definstances init-instances

    ([Verano] of Epoca (Nombre "Verano"))
    ([Invierno] of Epoca (Nombre "Invierno"))
    ([Primavera] of Epoca (Nombre "Primavera"))
    ([Otono] of Epoca (Nombre "Otoño"))


    ([Agua] of Bebida
    (Nombre "Agua") (Alcohol false)
    (Precio 1.0)
    (Temperatura "Indiferente")
    (Formalidad 5)
    (Zona "Desconocida"))

([Cerveza] of Bebida
    (Nombre "Cerveza") (Alcohol true)
    (Precio 2.0)
    (Temperatura "Fría")
    (Formalidad 3)
    (Zona "Europa Occidental"))

([CervezaSinAlcohol] of Bebida
    (Nombre "Cerveza Sin Alcohol") (Alcohol false)
    (Precio 2.5)
    (Temperatura "Fría")
    (Formalidad 3)
    (Zona "Europa Occidental"))

([Zumo] of Bebida
    (Nombre "Zumo") (Alcohol false)
    (Precio 2.0)
    (Temperatura "Indiferente")
    (Formalidad 2)
    (Zona "Desconocida")
    (AptoDiabetico FALSE))

([CocaCola] of Bebida
    (Nombre "Coca-Cola")
    (Alcohol false)
    (Precio 1.8)
    (Temperatura "Fría")
    (Formalidad 2)
    (Zona "América del Norte")
    (AptoDiabetico FALSE))

([Pepsi] of Bebida
    (Nombre "Pepsi")
    (Alcohol false)
    (Precio 1.7)
    (Temperatura "Fría")
    (Formalidad 2)
    (Zona "América del Norte")
    (AptoDiabetico FALSE))

([FantaNaranja] of Bebida
    (Nombre "Fanta Naranja")
    (Alcohol false)
    (Precio 1.6)
    (Temperatura "Fría")
    (Formalidad 2)
    (Zona "Europa Occidental")
    (AptoDiabetico FALSE))

([Sprite] of Bebida
    (Nombre "Sprite")
    (Alcohol false)
    (Precio 1.6)
    (Temperatura "Fría")
    (Formalidad 2)
    (Zona "Europa Occidental")
    (AptoDiabetico FALSE))

([IncaKola] of Bebida
    (Nombre "Inca Kola")
    (Alcohol false)
    (Precio 1.5)
    (Temperatura "Fría")
    (Formalidad 2)
    (Zona "América Latina")
    (AptoDiabetico FALSE))

([Guaraná] of Bebida
    (Nombre "Guaraná")
    (Alcohol false)
    (Precio 1.5)
    (Temperatura "Fría")
    (Formalidad 2)
    (Zona "América Latina")
    (AptoDiabetico FALSE))

([KasNaranja] of Bebida
    (Nombre "Kas Naranja")
    (Alcohol false)
    (Precio 1.5)
    (Temperatura "Fría")
    (Formalidad 2)
    (Zona "Europa Occidental")
    (AptoDiabetico FALSE))

([Cava] of Bebida
    (Nombre "Cava") (Alcohol true)
    (Precio 10.0)
    (Temperatura "Fría")
    (Formalidad 10)
    (Zona "Europa Occidental"))

([VinoTinto] of Vino
    (Nombre "Vino Tinto") (Alcohol true)
    (Precio 8.0)
    (Temperatura "Caliente")
    (Formalidad 9)
    (Zona "Europa Occidental"))

([VinoBlanco] of Vino
    (Nombre "Vino Blanco") (Alcohol true)
    (Precio 7.0)
    (Temperatura "Fría")
    (Formalidad 7)
    (Zona "Europa Occidental"))

([VinoRosado] of Vino
    (Nombre "Vino Rosado") (Alcohol true)
    (Precio 8.0)
    (Temperatura "Fría")
    (Formalidad 8)
    (Zona "Europa Occidental"))

([Champan] of Bebida
    (Nombre "Champán") (Alcohol true)
    (Precio 15.0)
    (Temperatura "Fría")
    (Formalidad 10)
    (Zona "Europa Occidental"))

([Vermut] of Bebida
    (Nombre "Vermut") (Alcohol true)
    (Precio 7.0)
    (Temperatura "Fría")
    (Formalidad 7)
    (Zona "Europa Occidental"))

([AguaConGas] of Bebida
    (Nombre "Agua con Gas") (Alcohol false)
    (Precio 1.5)
    (Temperatura "Fría")
    (Formalidad 6)
    (Zona "Europa Occidental"))

([Sake] of Bebida
    (Nombre "Sake") (Alcohol true)
    (Precio 10.0)
    (Temperatura "Caliente")
    (Formalidad 8)
    (Zona "Asia Oriental"))

([Soju] of Bebida
    (Nombre "Soju") (Alcohol true)
    (Precio 6.0)
    (Temperatura "Indiferente")
    (Formalidad 7)
    (Zona "Asia Oriental"))

([TeFrio] of Bebida
    (Nombre "Té Frío") (Alcohol false)
    (Precio 2.0)
    (Temperatura "Fría")
    (Formalidad 3)
    (Zona "Asia Oriental"))

([Mezcal] of Bebida
    (Nombre "Mezcal") (Alcohol true)
    (Precio 9.0)
    (Temperatura "Indiferente")
    (Formalidad 7)
    (Zona "América Latina"))

([Tequila] of Bebida
    (Nombre "Tequila") (Alcohol true)
    (Precio 8.0)
    (Temperatura "Indiferente")
    (Formalidad 7)
    (Zona "América Latina"))

([Whisky] of Bebida
    (Nombre "Whisky") (Alcohol true)
    (Precio 12.0)
    (Temperatura "Indiferente")
    (Formalidad 9)
    (Zona "América del Norte"))

([Bourbon] of Bebida
    (Nombre "Bourbon") (Alcohol true)
    (Precio 12.0)
    (Temperatura "Indiferente")
    (Formalidad 9)
    (Zona "América del Norte"))

([TintoDeVerano] of Bebida
    (Nombre "Tinto de Verano") (Alcohol true)
    (Precio 5.0)
    (Temperatura "Fría")
    (Formalidad 4)
    (Zona "Europa Occidental"))

([Arak] of Bebida
    (Nombre "Arak") (Alcohol true)
    (Precio 7.0)
    (Temperatura "Indiferente")
    (Formalidad 7)
    (Zona "África del Norte"))

([Lassi] of Bebida
    (Nombre "Lassi") (Alcohol false)
    (Precio 3.0)
    (Temperatura "Fría")
    (Formalidad 5)
    (Zona "Asia del Sur")
    (AptoDiabetico FALSE))

([Chai] of Bebida
    (Nombre "Chai") (Alcohol false)
    (Precio 2.5)
    (Temperatura "Caliente")
    (Formalidad 6)
    (Zona "Asia del Sur")
    (AptoDiabetico FALSE))


([TeVerde] of Bebida
    (Nombre "Té Verde")
    (Alcohol false)
    (Precio 1.8)
    (Temperatura "Caliente")
    (Formalidad 3)
    (Zona "Asia Oriental")
    (AptoDiabetico TRUE))

([InfusionHierbas] of Bebida
    (Nombre "Infusión de Hierbas")
    (Alcohol false)
    (Precio 2.0)
    (Temperatura "Caliente")
    (Formalidad 3)
    (Zona "Desconocida")
    (AptoDiabetico TRUE))

([AguaLimon] of Bebida
    (Nombre "Agua con Limón")
    (Alcohol false)
    (Precio 1.2)
    (Temperatura "Fría")
    (Formalidad 7)
    (Zona "Desconocida")
    (AptoDiabetico TRUE))

([Sobia] of Bebida
  (Nombre "Sobia")
  (Alcohol false)
  (Precio 2.0)
  (Temperatura "Fría")
  (Formalidad 4)
  (Zona "África del Norte")
  (AptoDiabetico FALSE))

;; Jugo de dátiles (típico de Magreb)
([JugoDatiles] of Bebida
  (Nombre "Jugo de Dátiles")
  (Alcohol false)
  (Precio 2.5)
  (Temperatura "Fría")
  (Formalidad 4)
  (Zona "África del Norte")
  (AptoDiabetico FALSE))

;; Agua de flor de azahar
([AguaAzahar] of Bebida
  (Nombre "Agua de Flor de Azahar")
  (Alcohol false)
  (Precio 1.2)
  (Temperatura "Fría")
  (Formalidad 5)
  (Zona "África del Norte")
  (AptoDiabetico TRUE))


([Almendras] of Ingrediente
  (Nombre "Almendras")
  (Gluten false) (Lactosa false)
  (Vegano true)   (Vegetariano true)
  (AptoDiabetico TRUE))

([Limon] of Ingrediente
  (Nombre "Limón")
  (Gluten false) (Lactosa false)
  (Vegano true)   (Vegetariano true)
  (AptoDiabetico TRUE))

([Aceitunas] of Ingrediente
  (Nombre "Aceitunas")
  (Gluten false) (Lactosa false)
  (Vegano true)   (Vegetariano true)
  (AptoDiabetico TRUE))

([Caldo] of Ingrediente
  (Nombre "Caldo")
  (Gluten false) (Lactosa false)
  (Vegano false)  (Vegetariano false)
  (AptoDiabetico TRUE))  ;; o FALSE si lleva grasa animal
    ([Nachos] of Ingrediente
         (Nombre "Nachos")
         (Gluten true) (Lactosa false)
         (Vegano true) (Vegetariano true))
    ([Tomate] of Ingrediente
         (Nombre "Tomate")
         (Gluten false) (Lactosa false)
         (Vegano true) (Vegetariano true))
    ([Lechuga] of Ingrediente
         (Nombre "Lechuga")
         (Gluten false) (Lactosa false)
         (Vegano true) (Vegetariano true))
    ([Queso] of Ingrediente
         (Nombre "Queso")
         (Gluten false) (Lactosa true)
         (Vegano false) (Vegetariano true) )
    ([Harina] of Ingrediente
         (Nombre "Harina")
         (Gluten true) (Lactosa false)
         (Vegano true) (Vegetariano true) )
    ([AceiteOliva] of Ingrediente
         (Nombre "Aceite de Oliva")
         (Gluten false) (Lactosa false)
         (Vegano true) (Vegetariano true) )
    ([Vinagre] of Ingrediente
        (Nombre "Vinagre")
        (Gluten false) (Lactosa false)
        (Vegano true) (Vegetariano true) )
    ([Carne] of Ingrediente
         (Nombre "Carne de Res")
         (Gluten false) (Lactosa false)
         (Vegano false) (Vegetariano false) )
    ([Pollo] of Ingrediente
         (Nombre "Pollo")
         (Gluten false) (Lactosa false)
         (Vegano false) (Vegetariano false) )
    ([Arroz] of Ingrediente
         (Nombre "Arroz")
         (Gluten false) (Lactosa false)
         (Vegano true) (Vegetariano true) )
    ([Atun] of Ingrediente
         (Nombre "Atún")
         (Gluten false) (Lactosa false)
         (Vegano false) (Vegetariano false) )
    ([Alga] of Ingrediente
         (Nombre "Alga Nori")
         (Gluten false) (Lactosa false)
         (Vegano true) (Vegetariano true) )
    ([PimientoRojo] of Ingrediente
         (Nombre "Pimiento Rojo")
         (Gluten false) (Lactosa false)
         (Vegano true) (Vegetariano true))
    ([PimientoVerde] of Ingrediente
         (Nombre "Pimiento Verde")
         (Gluten false) (Lactosa false)
         (Vegano true) (Vegetariano true))
    ([Pasta] of Ingrediente
      (Nombre "Pasta")
      (Gluten true)   (Lactosa false)
      (Vegano true)   (Vegetariano true))
    ([Piña] of Ingrediente
      (Nombre "Piña")
      (Gluten false)  (Lactosa false)
      (Vegano true)   (Vegetariano true))
    ([Leche] of Ingrediente
        (Nombre "Leche")
        (Gluten false)  (Lactosa true)
        (Vegano false)  (Vegetariano true))
    ([Huevos] of Ingrediente
        (Nombre "Huevos")
        (Gluten false)  (Lactosa false)
        (Vegano false)  (Vegetariano true))
    ([Chocolate] of Ingrediente
        (Nombre "Chocolate")
        (Gluten false)  (Lactosa true)
        (Vegano false)  (Vegetariano true)
        (AptoDiabetico false)  
        )

    ([Azucar] of Ingrediente
        (Nombre "Azúcar")
        (Gluten false)  (Lactosa false)
        (Vegano true)   (Vegetariano true)
        (AptoDiabetico false)
        )

    ([Frutas] of Ingrediente
        (Nombre "Frutas variadas")
        (Gluten false)  (Lactosa false)
        (Vegano true)   (Vegetariano true))
    
    ([EspeciasCurry] of Ingrediente
        (Nombre "Especias Curry")
        (Gluten false) (Lactosa false)
        (Vegano true) (Vegetariano true) )
    ([Especias] of Ingrediente
        (Nombre "Especias")
        (Gluten false) (Lactosa false)
        (Vegano true) (Vegetariano true) )
    ([Ajo] of Ingrediente
        (Nombre "Ajo")
        (Gluten false) (Lactosa false)
        (Vegano true) (Vegetariano true) )
    ([Quinoa] of Ingrediente
        (Nombre "Quinoa")
        (Gluten false) (Lactosa false)
        (Vegano true) (Vegetariano true) )
    ([Espinaca] of Ingrediente
        (Nombre "Espinaca")
        (Gluten false) (Lactosa false)
        (Vegano true) (Vegetariano true) )
    ([Zanahoria] of Ingrediente
        (Nombre "Zanahoria")
        (Gluten false) (Lactosa false)
        (Vegano true) (Vegetariano true) )
    ([Calabaza] of Ingrediente
        (Nombre "Calabaza")
        (Gluten false) (Lactosa false)
        (Vegano true) (Vegetariano true) )
    ([Garbanzos] of Ingrediente
        (Nombre "Garbanzos")
        (Gluten false) (Lactosa false)
        (Vegano true) (Vegetariano true) )
    ([Lentejas] of Ingrediente
        (Nombre "Lentejas")
        (Gluten false) (Lactosa false)
        (Vegano true) (Vegetariano true) )
    ([LecheCoco] of Ingrediente
        (Nombre "Leche de Coco")
        (Gluten false) (Lactosa false)
        (Vegano true) (Vegetariano true) )
    ([Champiñones] of Ingrediente
        (Nombre "Champiñones")
        (Gluten false) (Lactosa false)
        (Vegano true) (Vegetariano true) )
    ([Brocoli] of Ingrediente
        (Nombre "Brocoli")
        (Gluten false) (Lactosa false)
        (Vegano true) (Vegetariano true) )
    ([Alcachofa] of Ingrediente
        (Nombre "Alcachofa")
        (Gluten false) (Lactosa false)
        (Vegano true) (Vegetariano true) )
    ([Albahaca] of Ingrediente
        (Nombre "Albahaca")
        (Gluten false) (Lactosa false)
        (Vegano true) (Vegetariano true) )
    ([Berenjena] of Ingrediente
        (Nombre "Berenjena")
        (Gluten false) (Lactosa false)
        (Vegano true) (Vegetariano true) )
    ([Patata] of Ingrediente
        (Nombre "Patata")
        (Gluten false) (Lactosa false)
        (Vegano true) (Vegetariano true) )
    ([Cebolla] of Ingrediente
        (Nombre "Cebolla")
        (Gluten false) (Lactosa false)
        (Vegano true) (Vegetariano true) )
    ([SalsaTeriyaki] of Ingrediente
        (Nombre "Salsa teriyaki")
        (Gluten true) (Lactosa false)
        (Vegano true) (Vegetariano true) 
        (AptoDiabetico false))
    ([SalsaSoja] of Ingrediente
        (Nombre "Salsa soja")
        (Gluten true) (Lactosa false)
        (Vegano true) (Vegetariano true) )
    ([Sésamo] of Ingrediente
        (Nombre "Sésamo")
        (Gluten false) (Lactosa false)
        (Vegano true) (Vegetariano true) )
    ([Hmburguesa] of Ingrediente
        (Nombre "Hamburguesa")
        (Gluten false) (Lactosa false)
        (Vegano false) (Vegetariano false) )
    ([HamburguesaVegetal] of Ingrediente
        (Nombre "Hamburguesa Vegetal")
        (Gluten false) (Lactosa false)
        (Vegano true) (Vegetariano true) )
    ([PanSinGluten] of Ingrediente
        (Nombre "Pan Sin Gluten")
        (Gluten false) (Lactosa false)
        (Vegano true) (Vegetariano true) )
    ([Pan] of Ingrediente
        (Nombre "Pan")
        (Gluten true) (Lactosa false)
        (Vegano true) (Vegetariano true) )
    ([Aguacate] of Ingrediente
        (Nombre "Aguacate")
        (Gluten false) (Lactosa false)
        (Vegano true) (Vegetariano true) )
    ([Cacao] of Ingrediente
        (Nombre "Cacao")
        (Gluten false) (Lactosa false)
        (Vegano true) (Vegetariano true) (AptoDiabetico false))
    ([Sirope] of Ingrediente
        (Nombre "Sirope")
        (Gluten false) (Lactosa false)
        (Vegano true) (Vegetariano true) (AptoDiabetico false))
    ([HarinaArroz] of Ingrediente
        (Nombre "Harina de Arroz")
        (Gluten false) (Lactosa false)
        (Vegano true) (Vegetariano true) (AptoDiabetico false))
    ([Nueces] of Ingrediente
        (Nombre "Nueces")
        (Gluten false) (Lactosa false)
        (Vegano true) (Vegetariano true) )
    ([Levadura] of Ingrediente
        (Nombre "Levadura")
        (Gluten false) (Lactosa false)
        (Vegano true) (Vegetariano true) )
    ([Canela] of Ingrediente
        (Nombre "Canela")
        (Gluten false) (Lactosa false)
        (Vegano true) (Vegetariano true) )
    ([FrijolDulce] of Ingrediente
        (Nombre "Frijol Dulce")
        (Gluten false) (Lactosa false)
        (Vegano true) (Vegetariano true) )
    ([Manzana] of Ingrediente
        (Nombre "Manzana")
        (Gluten false) (Lactosa false)
        (Vegano true) (Vegetariano true) )
    ([Naranja] of Ingrediente
        (Nombre "Naranja")
        (Gluten false) (Lactosa false)
        (Vegano true) (Vegetariano true) )
    ([Kiwi] of Ingrediente
        (Nombre "Kiwi")
        (Gluten false) (Lactosa false)
        (Vegano true) (Vegetariano true) )
    ([Fresas] of Ingrediente
        (Nombre "Fresas")
        (Gluten false) (Lactosa false)
        (Vegano true) (Vegetariano true) )
    ([Calabacín] of Ingrediente
        (Nombre "Calabacín")
        (Gluten false) (Lactosa false)
        (Vegano true) (Vegetariano true) )
    ([Espinaca] of Ingrediente
        (Nombre "Espinaca")
        (Gluten false) (Lactosa false)
        (Vegano true) (Vegetariano true) )
    ([Seitan] of Ingrediente
        (Nombre "Seitan")
        (Gluten true) (Lactosa false)
        (Vegano true) (Vegetariano true) )
    ([Frankfurt] of Ingrediente
        (Nombre "Frankfurt")
        (Gluten false) (Lactosa false)
        (Vegano false) (Vegetariano false) (Halal false))
    ([Salchicha] of Ingrediente
        (Nombre "Salchicha")
        (Gluten false) (Lactosa false)
        (Vegano false) (Vegetariano false) (Halal false))
    ([Pepinillo] of Ingrediente
        (Nombre "Pepinillo")
        (Gluten false) (Lactosa false)
        (Vegano true) (Vegetariano true) )
    ([Cuscus] of Ingrediente
        (Nombre "Cuscus")
        (Gluten true) (Lactosa false)
        (Vegano true) (Vegetariano true) )
    
    
    
    ;;Platos principales



    ([ArrozCurry] of Plato
        (Nombre "Arroz con Curry")
        (Localidad "India")
        (Precio 13.0)
        (TiempoPreparacion 1.2)
        (Tipo "Principal")
        (Formalidad 5)
        (en_epoca [Verano] [Primavera] [Otono] [Invierno])
        (tiene_ingrediente [Arroz] [PimientoRojo] [Ajo] [EspeciasCurry] [AceiteOliva]) )

     ([Risotto] of Plato
        (Nombre "Risotto de Setas")
        (Localidad "España")
        (Precio 13.0)
        (TiempoPreparacion 1.2)
        (Tipo "Principal")
        (Formalidad 8)
        (en_epoca [Otono] [Invierno]) 
        (tiene_ingrediente [Arroz] [Champiñones] [Ajo] [Cebolla] [AceiteOliva]) )

    ([CalabazinRelleno] of Plato
        (Nombre "Calabacín relleno de verduras y tofu")
        (Localidad "España")
        (Precio 9.0)
        (TiempoPreparacion 1.0)
        (Tipo "Principal")
        (Formalidad 7)
        (en_epoca [Verano] [Otono])
        (tiene_ingrediente [Calabacín] [Tofu] [Cebolla] [Ajo] [Tomate] [AceiteOliva]) )
    
    ([QuinoaSalteada] of Plato
        (Nombre "Quinoa Salteada con Vegetales")
        (Localidad "Perú")
        (Precio 11.5)
        (TiempoPreparacion 1.0)
        (Tipo "Principal")
        (Formalidad 5)
        (en_epoca [Primavera] [Verano])
        (tiene_ingrediente [Quinoa] [Espinaca] [Ajo] [AceiteOliva] [PimientoRojo]) )
    
    ([Ensalada] of Plato
        (Nombre "Ensalada Mixta")
        (Localidad "España")
        (Precio 8.5)
        (TiempoPreparacion 0.3)
        (Tipo "Principal")
        (Formalidad 4)
        (en_epoca [Verano] [Primavera])
        (tiene_ingrediente [Lechuga] [Tomate] [AceiteOliva]) )

    ([EnsaladaAlgas] of Plato
        (Nombre "Ensalada de Algas Wakame")
        (Localidad "Japón")
        (Precio 7.5)
        (TiempoPreparacion 0.2)
        (Tipo "Principal")
        (Formalidad 4)
        (en_epoca [Verano] [Primavera])
        (tiene_ingrediente [Alga] [SalsaSoja] [Zanahoria] [Vinagre]) )

    ([Gyozas] of Plato
        (Nombre "Gyozas")
        (Localidad "Japón")
        (Precio 9.0)
        (TiempoPreparacion 1.4)
        (Tipo "Principal")
        (Formalidad 6)
        (en_epoca [Otono] [Invierno])
        (tiene_ingrediente [Ajo] [SalsaSoja] [Carne] [Calabacín]) )

    ([Raviolis] of Plato
        (Nombre "Raviolis de berenjena con manzana")
        (Localidad "España")
        (Precio 8.5)
        (TiempoPreparacion 0.3)
        (Tipo "Principal")
        (Formalidad 8)
        (en_epoca [Otono] [Invierno])
        (tiene_ingrediente [Berenjena] [Pasta] [Manzana] [Cebolla] [AceiteOliva]) )
    
    ([PastaTomate] of Plato
        (Nombre "Pasta con Tomate")
        (Localidad "Italia")
        (Precio 12.0)
        (TiempoPreparacion 1.0)
        (Tipo "Principal")
        (Formalidad 3)
        (en_epoca [Primavera] [Otono])
        (tiene_ingrediente [Pasta] [Tomate] [AceiteOliva]) )
    
    ([Pizza] of Plato
        (Nombre "Pizza con Piña")
        (Localidad "Italia")
        (Precio 14.5)
        (TiempoPreparacion 1.5)
        (Tipo "Principal")
        (Formalidad 1)
        (en_epoca [Primavera] [Verano] [Otono] [Invierno])
        (tiene_ingrediente [Harina] [Queso] [Pollo] [Piña] [AceiteOliva]) )
   
    ([Sushi] of Plato
        (Nombre "Sushi Clásico")
        (Localidad "Japón")
        (Precio 18.0)
        (TiempoPreparacion 1.2)
        (Tipo "Principal")
        (Formalidad 5)
        (en_epoca [Primavera] [Verano] [Otono] [Invierno])
        (tiene_ingrediente [Arroz] [Alga] [Atun]) )

    ([TacoCarne] of Plato
        (Nombre "Taco de Carne")
        (Localidad "México")
        (Precio 9.0)
        (TiempoPreparacion 0.5)
        (Tipo "Principal")
        (Formalidad 2)
        (en_epoca [Primavera] [Verano] [Otono] [Invierno])
        (tiene_ingrediente [Harina] [Carne] [Queso]) )

    ([TacosVegetales] of Plato
        (Nombre "Tacos Veganos")
        (Localidad "México")
        (Precio 9.0)
        (TiempoPreparacion 1.0)
        (Tipo "Principal")
        (Formalidad 2)
        (en_epoca [Primavera] [Verano] [Otono] [Invierno])
        (tiene_ingrediente [Harina] [PimientoRojo] [Tomate] [Lechuga] [AceiteOliva]) )
    
    ([Paella] of Plato
        (Nombre "Paella Valenciana")
        (Localidad "España")
        (Precio 15.0)
        (TiempoPreparacion 2.0)
        (Tipo "Principal")
        (Formalidad 8)
        (en_epoca [Primavera] [Verano] [Otono] [Invierno])
        (tiene_ingrediente [Arroz] [Pollo] [AceiteOliva] [Tomate]) )

    ([NachosQueso] of Plato
        (Nombre "Nachos con Queso y Guacamole")
        (Localidad "México")
        (Precio 9.0)
        (TiempoPreparacion 0.5)
        (Tipo "Principal")
        (Formalidad 1)
        (en_epoca [Primavera] [Verano] [Otono] [Invierno])
        (tiene_ingrediente [Nachos] [Queso] [Aguacate] [Cebolla] [Tomate]) )

    ([PaellaVegetal] of Plato
        (Nombre "Paella de Verduras")
        (Localidad "España")
        (Precio 13.0)
        (TiempoPreparacion 1.4)
        (Tipo "Principal")
        (Formalidad 8)
        (en_epoca [Primavera] [Verano] [Otono] [Invierno])
        (tiene_ingrediente [Arroz] [Pimiento] [Alcachofa] [AceiteOliva]) )

    ([Brochetas] of Plato
        (Nombre "Brochetas Caprese")
        (Localidad "Estados Unidos")
        (Precio 7.0)
        (TiempoPreparacion 0.4)
        (Tipo "Principal")
        (Formalidad 5)
        (en_epoca [Primavera] [Verano] [Otono] [Invierno])
        (tiene_ingrediente [Tomate] [Queso] [Albahaca] [AceiteOliva]) )

    ([EnsaladaPatatas] of Plato
        (Nombre "Ensalada de Patata")
        (Localidad "Alemania")
        (Precio 7.0)
        (TiempoPreparacion 0.6)
        (Tipo "Principal")
        (Formalidad 4)
        (en_epoca [Verano] [Primavera]) 
        (tiene_ingrediente [Patata] [Cebolla] [Vinagre] [AceiteOliva]) )

    ([SopaAgridulce] of Plato
        (Nombre "Sopa Agridulce")
        (Localidad "China")
        (Precio 6.0)
        (TiempoPreparacion 0.9)
        (Tipo "Principal")
        (Formalidad 6)
        (en_epoca [Otono] [Invierno])
        (tiene_ingrediente [Vinagre] [Azucar] [Champiñones] [Tofu] [Zanahoria] [Brocoli]))
    
    ([PastaPesto] of Plato
        (Nombre "Pasta al Pesto")
        (Localidad "Italia")
        (Precio 12.0)
        (TiempoPreparacion 1.1)
        (Tipo "Principal")
        (Formalidad 6)
        (en_epoca [Primavera] [Verano])
        (tiene_ingrediente [Pasta] [Albahaca] [Nueces] [AceiteOliva]) )
    
    ([PatatasGratinadas] of Plato
        (Nombre "Patatas Gratinadas")
        (Localidad "Francia")
        (Precio 10.0)
        (TiempoPreparacion 1.2)
        (Tipo "Principal")
        (Formalidad 4)
        (en_epoca [Otono] [Invierno])
        (tiene_ingrediente [Patata] [Queso] [Leche]))

    ([EnsaladaEmbutido] of Plato
        (Nombre "Ensalada de Carne fría")
        (Localidad "Francia")
        (Precio 10.0)
        (TiempoPreparacion 1.2)
        (Tipo "Principal")
        (Formalidad 4)
        (en_epoca [Verano])
        (tiene_ingrediente [Carne] [Pan] [Pepinillo] [Vinagre] [Lechuga] [AceiteOliva]) )

    ([MacAndCheese] of Plato
        (Nombre "Mac and Cheese")
        (Localidad "Canadá")
        (Precio 7.5)
        (TiempoPreparacion 1.0)
        (Tipo "Principal")
        (Formalidad 1)
        (en_epoca [Primavera] [Otono] [Invierno])
        (tiene_ingrediente [Pasta] [Queso] [Leche] [AceiteOliva] [Nueces]))

    ([CuscusVerduras] of Plato
        (Nombre "Cuscus con Verduras")
        (Localidad "Canadá")
        (Precio 7.5)
        (TiempoPreparacion 1.0)
        (Tipo "Principal")
        (Formalidad 6)
        (en_epoca [Primavera] [Verano] [Otono])
        (tiene_ingrediente [Cuscus] [Queso] [AceiteOliva] [Pimiento] [Zanahoria] [Cebolla]))

    ([GarbanzosEnsalada] of Plato
        (Nombre "Ensalada de Garbanzos con Especias")
        (Localidad "Marruecos")
        (Precio 7.5)
        (TiempoPreparacion 1.0)
        (Tipo "Principal")
        (Formalidad 5)
        (en_epoca [Verano])
        (tiene_ingrediente [Cuscus] [Garbanzos] [AceiteOliva] [Pimiento] [Garbanzos] [Especias]))

    ([HotDogGlutenFree] of Plato
        (Nombre "HotDog GlutenFree")
        (Localidad "Estados Unidos")
        (Precio 7.5)
        (TiempoPreparacion 0.7)
        (Tipo "Segundo")
        (Formalidad 1)
        (en_epoca [Primavera] [Verano] [Otono] [Invierno])
        (tiene_ingrediente [PanSinGluten] [Frankfurt] ))

    ([HotDog] of Plato
        (Nombre "HotDog")
        (Localidad "Estados Unidos")
        (Precio 5.5)
        (TiempoPreparacion 0.7)
        (Tipo "Segundo")
        (Formalidad 1)
        (en_epoca [Primavera] [Verano] [Otono] [Invierno])
        (tiene_ingrediente [Pan] [Frankfurt] ))
    
    ([DedosPollo] of Plato
        (Nombre "Dedos de Pollo")
        (Localidad "Estados Unidos")
        (Precio 8.5)
        (TiempoPreparacion 1.0)
        (Tipo "Segundo")
        (Formalidad 1)
        (tiene_ingrediente [Pollo] [PanSinGluten] ))

    ([SalchichaPlato] of Plato
        (Nombre "Salchicha con Patatas Asadas")
        (Localidad "Alemania")
        (Precio 8.5)
        (TiempoPreparacion 1.0)
        (Tipo "Segundo")
        (Formalidad 3)
        (en_epoca [Primavera] [Verano] [Otono] [Invierno])
        (tiene_ingrediente [Salchicha] [Patatas] ))

    ([Lasana] of Plato
        (Nombre "Lasaña de Espinacas")
        (Localidad "España")
        (Precio 11.0)
        (TiempoPreparacion 1.5)
        (Tipo "Segundo")
        (Formalidad 9)
        (en_epoca [Otono] [Invierno])
        (tiene_ingrediente [Espinaca] [Nueces] [Ajo] [Cebolla] [Harina] [AceiteOliva]) )

    ([Milanesa] of Plato
            (Nombre "Milanesa con patatas")
            (Localidad "México")
            (Precio 7.0)
            (TiempoPreparacion 0.8)
            (Tipo "Segundo")
            (Formalidad 4)
            (en_epoca [Primavera] [Verano] [Otono] [Invierno])
            (tiene_ingrediente [Patatas] [Carne] [Huevo] [Harina] [AceiteOliva]) )

    ([Quesadilla] of Plato
            (Nombre "Quesadilla frita")
            (Localidad "México")
            (Precio 6.5)
            (TiempoPreparacion 0.7)
            (Tipo "Segundo")
            (Formalidad 4)
            (en_epoca [Primavera] [Verano] [Otono] [Invierno])
            (tiene_ingrediente [Carne] [Queso] [Huevo] [Tomate]) )

    ([Ratatouille] of Plato
        (Nombre "Ratatouille")
        (Localidad "Francia")
        (Precio 11.5)
        (TiempoPreparacion 1.3)
        (Tipo "Segundo")
        (Formalidad 9)
        (en_epoca [Verano])
        (tiene_ingrediente [Berenjena] [Tomate] [Pimiento]) )

    ([TeriyakiTofu] of Plato
        (Nombre "Tofu al Teriyaki")
        (Localidad "Japón")
        (Precio 14.0)
        (TiempoPreparacion 1.2)
        (Tipo "Segundo")
        (Formalidad 6)
        (en_epoca [Otono] [Invierno])
        (tiene_ingrediente [Tofu] [SalsaTeriyaki] [Cebolla] [Sésamo]) )

    ([SalteadoVerduras] of Plato
        (Nombre "Salteado de Verduras al Wok")
        (Localidad "China")
        (Precio 10.5)
        (TiempoPreparacion 1.0)
        (Tipo "Segundo")
        (Formalidad 7)
        (en_epoca [Primavera] [Verano])
        (tiene_ingrediente [Brocoli] [Zanahoria] [Pimiento] [SalsaSoja]) )

    ([PokeBowl] of Plato
        (Nombre "PokeBowl")
        (Localidad "Corea")
        (Precio 13.5)
        (TiempoPreparacion 0.5)
        (Tipo "Segundo")
        (Formalidad 5)
        (en_epoca [Verano])
        (tiene_ingrediente [Arroz] [Tofu] [Zanahoria] [Cebolla] [Alga] [Aguacate]) )

    ([TimbalQuinoa] of Plato
        (Nombre "Timbal de quinoa con verduras salteadas")
        (Localidad "España")
        (Precio 15.5)
        (TiempoPreparacion 1.4)
        (Tipo "Segundo")
        (Formalidad 7)
        (en_epoca [Primavera] [Otono])
        (tiene_ingrediente [Quinoa] [Calabacín] [EspeciasCurry] [Zanahoria]) )

    ([FiletesTofu] of Plato
        (Nombre "Filetitos de tofu marinado")
        (Localidad "España")
        (Precio 15.5)
        (TiempoPreparacion 1.1)
        (Tipo "Segundo")
        (Formalidad 8)
        (en_epoca [Otono] [Invierno]) 
        (tiene_ingrediente [Tofu] [SalsaSoja] [Ajo] [Cebolla]) )

    ([SeitanPlato] of Plato
        (Nombre "Seitan con pure de Patata")
        (Localidad "España")
        (Precio 16.5)
        (TiempoPreparacion 0.9)
        (Tipo "Segundo")
        (Formalidad 8)
        (en_epoca [Otono] [Invierno])
        (tiene_ingrediente [Seitan] [Patata] [Nueces] [AceiteOliva]) )

    ([LomoSaltado] of Plato
        (Nombre "Lomo Salteado")
        (Localidad "Perú")
        (Precio 11.0)
        (TiempoPreparacion 1.2)
        (Tipo "Segundo")
        (Formalidad 5)
        (en_epoca [Primavera] [Verano] [Otono] [Invierno])
        (tiene_ingrediente [Carne] [Cebolla] [Tomate]) )

    ([Arepa] of Plato
        (Nombre "Arepa")
        (Localidad "Colombia")
        (Precio 9.5)
        (TiempoPreparacion 1.0)
        (Tipo "Segundo")
        (Formalidad 2)
        (en_epoca [Primavera] [Verano] [Otono] [Invierno])
        (tiene_ingrediente [Harina] [Tomate] [Queso] [Huevo]) )

    ([HamburguesaVegana] of Plato
        (Nombre "Hamburguesa Vegana")
        (Localidad "Estados Unidos")
        (Precio 12.5)
        (TiempoPreparacion 1.3)
        (Tipo "Segundo")
        (Formalidad 4)
        (en_epoca [Primavera] [Verano] [Otono] [Invierno])
        (tiene_ingrediente [HamburguesaVegetal] [PanSinGluten] [Lechuga] [Cebolla] [Tomate]) )

    ([HamburguesaCarne] of Plato
        (Nombre "Hamburguesa")
        (Localidad "Estados Unidos")
        (Precio 11.5)
        (TiempoPreparacion 1.3)
        (Tipo "Segundo")
        (Formalidad 4)
        (en_epoca [Primavera] [Verano] [Otono] [Invierno])
        (tiene_ingrediente [Hamburguesa] [Pan] [Lechuga] [Cebolla] [Tomate]) )

    ([CurryLentejas] of Plato
        (Nombre "Curry de Lentejas")
        (Localidad "India")
        (Precio 9.5)
        (TiempoPreparacion 1.2)
        (Tipo "Segundo")
        (Formalidad 6)
        (en_epoca [Otono] [Invierno])
        (tiene_ingrediente [Lentejas] [LecheCoco] [Curry] [Tomate]) )

    ([KarahiVegetariano] of Plato
        (Nombre "Karahi Vegetariano")
        (Localidad "Pakistán")
        (Precio 10.5)
        (TiempoPreparacion 1.3)
        (Tipo "Segundo")
        (Formalidad 7)
        (en_epoca [Otono] [Invierno])
        (tiene_ingrediente [Tomate] [Pimiento] [Garbanzos] [Especias]) )

    ([TagineVerduras] of Plato
        (Nombre "Tajín de Verduras")
        (Localidad "Marruecos")
        (Precio 11.5)
        (TiempoPreparacion 1.5)
        (Tipo "Segundo")
        (Formalidad 8)
        (en_epoca [Otono] [Invierno])
        (tiene_ingrediente [Zanahoria] [Calabaza] [Garbanzos]) )

    ([Filete] of Plato
        (Nombre "Filete a la Plancha")
        (Localidad "Argentina")
        (Precio 16.0)
        (TiempoPreparacion 1.3)
        (Tipo "Segundo")
        (Formalidad 9)
        (en_epoca [Primavera] [Verano] [Otono] [Invierno])
        (tiene_ingrediente [Carne] [AceiteOliva]) )

    ([PolloAsado] of Plato
        (Nombre "Pollo Asado con Hierbas")
        (Localidad "España")
        (Precio 14.0)
        (TiempoPreparacion 1.5)
        (Tipo "Segundo")
        (Formalidad 7)
        (en_epoca [Otono] [Invierno])
        (tiene_ingrediente [Pollo] [AceiteOliva] [Especias]) )

    ([TofuGrillado] of Plato
        (Nombre "Tofu Grillado con Verduras")
        (Localidad "Japón")
        (Precio 13.0)
        (TiempoPreparacion 1.2)
        (Tipo "Segundo")
        (Formalidad 8)
        (en_epoca [Primavera] [Verano]) 
        (tiene_ingrediente [Tofu] [Pimiento] [Zucchini] [AceiteSesamo]) )

    ([ArrozConLeche] of Plato
        (Nombre "Arroz con Leche")
        (Localidad "España")
        (Precio 5.0)
        (TiempoPreparacion 0.8)
        (Tipo "Postre")
        (Formalidad 2)
        (en_epoca [Primavera] [Verano] [Otono] [Invierno])
        (tiene_ingrediente [Arroz] [Leche] [Azucar]) )

    ([TartaChocolate] of Plato
        (Nombre "Tarta de Chocolate")
        (Localidad "Francia")
        (Precio 6.5)
        (TiempoPreparacion 1.2)
        (Tipo "Postre")
        (Formalidad 7)
        (en_epoca [Primavera] [Verano] [Otono] [Invierno])
        (tiene_ingrediente [Harina] [Huevos] [Azucar] [Chocolate]) )

    ([HeladoFrutas] of Plato
        (Nombre "Helado de Frutas")
        (Localidad "Italia")
        (Precio 5.5)
        (TiempoPreparacion 0.5)
        (Tipo "Postre")
        (Formalidad 4)
        (en_epoca [Verano])
        (tiene_ingrediente [Leche] [Azucar] [Frutas]) )

    ([MousseChocolate] of Plato
        (Nombre "Mousse de Chocolate Vegana")
        (Localidad "Francia")
        (Precio 6.0)
        (TiempoPreparacion 1.0)
        (Tipo "Postre")
        (Formalidad 9)
        (en_epoca [Primavera] [Verano] [Otono] [Invierno])
        (tiene_ingrediente [Aguacate] [Cacao] [Sirope] [LecheCoco]))

    ([Tangyuan] of Plato
        (Nombre "Tangyuan - Bolas de Arroz Dulces")
        (Localidad "China")
        (Precio 5.0)
        (TiempoPreparacion 0.7)
        (Tipo "Postre")
        (Formalidad 8)
        (en_epoca [Invierno])
        (tiene_ingrediente [HarinaArroz] [Azucar] [Agua] [Sésamo]))

    ([Mochi] of Plato
        (Nombre "Mochi - Pastel de Arroz")
        (Localidad "Japón")
        (Precio 5.5)
        (TiempoPreparacion 0.8)
        (Tipo "Postre")
        (Formalidad 6)
        (en_epoca [Invierno])
        (tiene_ingrediente [HarinaArroz] [Azucar] [FrijolDulce] [Agua]))

    ([Hotteok] of Plato
        (Nombre "Hotteok - Panqueques Dulces Coreanos")
        (Localidad "Corea")
        (Precio 4.5)
        (TiempoPreparacion 0.9)
        (Tipo "Postre")
        (Formalidad 5)
        (en_epoca [Invierno])
        (tiene_ingrediente [HarinaTrigo] [Azucar] [Nueces] [Canela] [Levadura]))

    ([MacedoniaFrutas] of Plato
        (Nombre "Macedonia de Frutas Frescas")
        (Localidad "España")
        (Precio 5.0)
        (TiempoPreparacion 0.5)
        (Tipo "Postre")
        (Formalidad 5)
        (en_epoca [Verano])
        (tiene_ingrediente [Manzana] [Naranja] [Kiwi] [Fresas]))

    ([EnsaladaFrutasNueces] of Plato
     (Nombre "Ensalada de Frutas con Nueces")
     (Localidad "España")
     (Precio 5.5)
     (TiempoPreparacion 0.5)
     (Tipo "Postre")
     (Formalidad 4)
     (en_epoca [Verano] [Primavera])
     (tiene_ingrediente [Frutas] [Nueces]) )

  ;; 2) Mousse de aguacate y leche de coco
  ([MousseAguacate] of Plato
     (Nombre "Mousse de Aguacate y Leche de Coco")
     (Localidad "Francia")
     (Precio 6.0)
     (TiempoPreparacion 0.8)
     (Tipo "Postre")
     (Formalidad 6)
     (en_epoca [Verano] [Otono])
     (tiene_ingrediente [Aguacate] [LecheCoco]) )

  ;; 3) Parfait de coco y nueces
  ([ParfaitCocoNueces] of Plato
     (Nombre "Parfait de Coco y Nueces")
     (Localidad "Canadá")
     (Precio 6.5)
     (TiempoPreparacion 0.7)
     (Tipo "Postre")
     (Formalidad 5)
     (en_epoca [Primavera] [Verano])
     (tiene_ingrediente [LecheCoco] [Nueces]) )

  ;; 4) Brochetas de frutas variadas
  ([BrochetasFruta] of Plato
     (Nombre "Brochetas de Frutas Variadas")
     (Localidad "México")
     (Precio 5.0)
     (TiempoPreparacion 0.4)
     (Tipo "Postre")
     (Formalidad 3)
     (en_epoca [Verano])
     (tiene_ingrediente [Manzana] [Naranja] [Kiwi] [Fresas]) )

    ([CouscousCordero] of Plato
  (Nombre "Couscous de Cordero al Estilo Marroquí")
  (Localidad "Marruecos")
  (Precio 14.0)
  (TiempoPreparacion 2.0)
  (Tipo "Principal")
  (Formalidad 8)
  (en_epoca [Primavera] [Verano] [Otono] [Invierno])
  (tiene_ingrediente [Cuscus] [Carne] [Zanahoria] [Calabaza] [Garbanzos] [Especias] [AceiteOliva]))

;; Tagine de pollo con limón y aceitunas
([TaginePolloLimon] of Plato
  (Nombre "Tajine de Pollo con Limón y Aceitunas")
  (Localidad "Marruecos")
  (Precio 13.5)
  (TiempoPreparacion 1.8)
  (Tipo "Principal")
  (Formalidad 8)
  (en_epoca [Primavera] [Verano] [Otono] [Invierno])
  (tiene_ingrediente [Pollo] [Limón] [Aceitunas] [Especias] [AceiteOliva] [Cebolla]))

;; Pastilla de pichón (o pollo)
([Pastilla] of Plato
  (Nombre "Pastilla de Pichón")
  (Localidad "Marruecos")
  (Precio 12.0)
  (TiempoPreparacion 2.2)
  (Tipo "Principal")
  (Formalidad 9)
  (en_epoca [Otono] [Invierno])
  (tiene_ingrediente [Pollo] [Harina] [Huevos] [Almendras] [Azucar] [Canela]))

;; Harira (sopa tradicional marroquí)
([Harira] of Plato
  (Nombre "Harira")
  (Localidad "Marruecos")
  (Precio 7.0)
  (TiempoPreparacion 1.0)
  (Tipo "Principal")
  (Formalidad 6)
  (en_epoca [Invierno])
  (tiene_ingrediente [Lentejas] [Garbanzos] [Tomate] [Cebolla] [Especias] [AceiteOliva]))

;; Msemen (tortitas marroquíes)
([Msemen] of Plato
  (Nombre "Msemen")
  (Localidad "Marruecos")
  (Precio 5.5)
  (TiempoPreparacion 1.2)
  (Tipo "Segundo")
  (Formalidad 4)
  (en_epoca [Primavera] [Verano] [Otono] [Invierno])
  (tiene_ingrediente [Harina] [AceiteOliva] [Agua]))

;; Ful medames (habas guisadas, Egipto)
([FulMedames] of Plato
  (Nombre "Ful Medames")
  (Localidad "Egipto")
  (Precio 8.0)
  (TiempoPreparacion 1.0)
  (Tipo "Principal")
  (Formalidad 5)
  (en_epoca [Primavera] [Verano] [Otono] [Invierno])
  (tiene_ingrediente [FrijolDulce] [AceiteOliva] [Ajo] [Limón] [Especias]))

;; Koshari (plato nacional de Egipto)
([Koshari] of Plato
  (Nombre "Koshari")
  (Localidad "Egipto")
  (Precio 9.5)
  (TiempoPreparacion 1.3)
  (Tipo "Principal")
  (Formalidad 7)
  (en_epoca [Primavera] [Verano] [Otono] [Invierno])
  (tiene_ingrediente [Arroz] [Pasta] [Lentejas] [Tomate] [Cebolla] [AceiteOliva]))

;; Molokhia (estofado de hojas verdes, Egipto)
([Molokhia] of Plato
  (Nombre "Molokhia")
  (Localidad "Egipto")
  (Precio 10.0)
  (TiempoPreparacion 1.2)
  (Tipo "Principal")
  (Formalidad 8)
  (en_epoca [Otono] [Invierno])
  (tiene_ingrediente [Espinaca] [Ajo] [AceiteOliva] [Caldo])) 

)


;; DefModules

;; módulo MAIN
(defmodule MAIN
    (export ?ALL)
)

;; módulo input, contiene las reglas para leer la entrada del usuario
(defmodule input 
    (import MAIN ?ALL)
    (export ?ALL)
)

;; módulo abstraccion, sirve para moldear los datos de entrada para el problema abstacto
(defmodule abstraccion 
    (import MAIN ?ALL)
    (import input ?ALL)
    (export ?ALL)
)

;; módulo asociacionHeuristica, contiene las reglas de asociación heurística para generar una solución abstracta
(defmodule asociacionHeuristica 
    (import MAIN ?ALL)
    (import abstraccion ?ALL)
    (export ?ALL)
)

;; módulo refinamiento, contiene las reglas de refinamiento para generar una solución concreta a partir de la solución abstracta
(defmodule refinamiento 
    (import MAIN ?ALL)
    (import asociacionHeuristica ?ALL) 
    (import input ?ALL)   
    (export ?ALL)
)

;; módulo impresionSolucion, contiene las reglas para imprimir la solución final
(defmodule impresionSolucion 
    (import MAIN ?ALL)
    (import refinamiento ?ALL)
    (export ?ALL)
)

;; DefTemplates

;; Plantilla de datos de entrada del usuario
(deftemplate input::InfoEvento
    (slot Nombre
        (type STRING)
        )
    (slot Fecha
        (type STRING)
        )
    (slot Localidad
        (type STRING)
        )
    (slot TipoEvento
        (type STRING)
        )
    (slot Presupuesto
        (type FLOAT)
        )
    (slot numComensales
        (type INTEGER)
        )
(multislot dietas
    (type SYMBOL)
)
    (multislot alergias
        (type STRING)
        )
    (slot Alcohol
        (type STRING)
        )
)

;; Plantilla de datos de abstracción del evento
(deftemplate abstraccion::InfoEventoA
    (slot Temporada
        (type STRING)
        )
    (slot Area
        (type STRING)
        )
    (slot tipoPlatos
        (type STRING)
        )
    (slot precioPlatos
        (type STRING)
        )
    (slot complejidadPlatos
        (type STRING)
        )
(multislot dietas
    (type SYMBOL)
)
    (multislot alergias
        (type STRING)
        )
    (slot Alcohol
        (type STRING)
        )
)

;; Plantilla de datos de solución abstracta
(deftemplate asociacionHeuristica::SolAbstracta
    (slot temperaturaMenu
        (type STRING)
    )
    (slot areaMenu
        (type STRING)
        )
    (slot tipoMenu
        (type STRING)
        )
    (slot precioMenu
        (type STRING)
        )
    (slot complejidadMenu
        (type STRING)
        )
(multislot dietas
    (type SYMBOL)
)
    (multislot alergias
        (type STRING)
        )
    (slot Alcohol
        (type STRING)
        )
)

;; Plantilla de datos de refinamiento
(deftemplate refinamiento::CandidateMenu
  (slot nombre (type STRING))
  (slot instancia (type INSTANCE))
  (slot score (type FLOAT)))

;; Plantilla de datos de menú seleccionado
(deftemplate refinamiento::SelectedMenu
  (slot plato      (type INSTANCE))
  (slot nombre     (type STRING))
  (slot precio     (type FLOAT))
  (slot score      (type FLOAT))
  (slot tipo       (type STRING))
  (slot orden      (type INTEGER))    ;; 1 = mejores, 2 = segundos, 3 = terceros, 
)

;; Plantilla de datos de bebida candidata para el menú final
(deftemplate refinamiento::CandidateBebida
  (slot nombre (type STRING))
  (slot instancia (type INSTANCE))
  (slot score (type FLOAT)))

;; Plantilla de datos de bebida seleccionada para el menú final
(deftemplate refinamiento::SelectedBebida
  (slot bebida     (type INSTANCE))
  (slot nombre     (type STRING))
  (slot precio     (type FLOAT) (default 0.0))
  (slot score      (type FLOAT))
  (slot orden      (type INTEGER)))

;; Plantilla de datos de todo el menú
(deftemplate CombinedMenu
  (slot principal (type STRING))
  (slot segundo   (type STRING))
  (slot postre    (type STRING))
  (slot bebida    (type STRING))
  (slot total     (type FLOAT))
  (slot score      (type FLOAT)))



;; Deffunctions
;; Función para seleccionar una opción de un conjunto dado
(deffunction input::selectorOpcion ($?opciones)
    (printout t "Selecciona una opcion de entre: " crlf)
    (printout t (implode$ $?opciones) crlf)
    (bind ?eleccion (read))

    (while (not(member$ ?eleccion $?opciones)) do
        (printout t "Por favor, selecciona una opcion de entre: " crlf)
        (printout t (implode$ $?opciones) crlf)
        (bind ?eleccion (read))
    )
    (return ?eleccion)
)

;; Función para introducir un entero en un intervalo dado
(deffunction input::introEnInterval (?min ?max)
    (printout t "Introduce un entero entre " ?min " y " ?max " " crlf)
    (bind ?valor (read))
    (while (or (< ?valor ?min) (> ?valor ?max)) do 
        (printout t "Por favor, introduce un entero " ?min " y " ?max " " crlf)
        (bind ?valor (read))
    )
    (return ?valor)
)

;; Función para comprobar si la entrada del usuario es válida
(deffunction input::entradaValida(?entrada $?opciones) 
    (bind $?entradaSeq (explode$ ?entrada))
    (bind ?comprobando 1) 
    (bind ?numElementos (length$ $?entradaSeq))
    (bind ?valida TRUE)
    (while (and (<= ?comprobando ?numElementos) ?valida) do 
        (bind ?valida (member$ (nth$ ?comprobando $?entradaSeq) $?opciones))
        (bind ?comprobando (+ ?comprobando 1))
    )
    (return ?valida)
) 

;; Función para seleccionar múltiples opciones de un conjunto dado
(deffunction input::selectorOpciones(?min ?max $?opciones)
    (bind ?mensaje "incializacion mensaje")
    (if (= ?min ?max) then 
        (printout t "Seleccione " ?min " opciones de entre: " crlf)            

    else 
        (printout t "Seleccione entre " ?min " y " ?max " opciones de entre: " crlf)            
    ) 

    (printout t (implode$ $?opciones) crlf) 

    (bind ?entrada (read)) 
    (bind ?numRespuestas (length$ (explode$ ?entrada))) 
    (bind ?respuestaNoValida (not (entradaValida ?entrada $?opciones))) 

    (while (or (or (< ?numRespuestas ?min) (> ?numRespuestas ?max)) ?respuestaNoValida) do  
        (printout t "Introduzca una entrada valida" crlf)
        (bind ?entrada (read)) 
        (bind ?numRespuestas (length$ (explode$ ?entrada))) 
        (bind ?respuestaNoValida (not (entradaValida ?entrada $?opciones)))
    )

    (return (explode$ ?entrada))
)

;; Lectura Entrada

;; Función para leer el nombre del evento
(deffunction input::readNombre ()
    (printout t "Introduce el nombre del evento: " crlf)
    (bind ?nombre (read))
    (return ?nombre)
)

;; Función para leer la localidad del evento
(deffunction input::readLocalidad ()
    (printout t "Introduce el pais del evento: " crlf)
    (bind ?localidad (readline))
    (return ?localidad)
)

;; Función para leer el tipo de evento
(deffunction input::readTipoEvento ()
    (printout t "Introduce el tipo de evento (boda, cumpleaños, conferencia, etc.): " crlf)
    (bind ?tipoEvento (read))
    (return ?tipoEvento)
)

;; Función para leer en que fecha se celebrará el evento
(deffunction input::readFecha ()
    (printout t "Introduce la fecha del evento (dd/mm/aaaa): " crlf)
    (bind ?fecha (read))
    (return ?fecha)
)

;; Función para leer el presupuesto por persona del evento
(deffunction input::readPresupuesto ()
    (printout t "Introduce el presupuesto por persona del evento: " crlf)
    (bind ?presupuesto (read))
    (while (< ?presupuesto 0) do ;; Presupesto no negativo
        (printout t "Por favor, introduce un presupuesto positivo: " crlf)
        (bind ?presupuesto (read))
    )
    (return ?presupuesto)
)

;; Función para leer el número de comensales del evento
(deffunction input::readNumComensales ()
    (printout t "Introduce el número de comensales: " crlf)
    (bind ?numComensales (read))
    (while (< ?numComensales 1) do
        (printout t "Por favor, introduce un número de comensales positivo: " crlf)
        (bind ?numComensales (read))
    )
    (return ?numComensales)
)

;; Función para leer el tipo de dieta del evento
(deffunction input::readDietas ()
  (printout t "Selecciona dietas (elige de: vegetariana, vegana, sin-gluten, sin-lactosa, sin-restricciones). Escribe fin para terminar:" crlf)
  (bind ?lista (create$))
  (bind ?opcs (create$ vegetariana vegana sin-gluten sin-lactosa sin-restricciones halal diabetica ))
  (bind ?d (read))                    
  (while (neq ?d fin) do             
    (if (member$ ?d ?opcs) then
      (bind ?lista (create$ ?lista ?d))
    else
      (printout t "Opción inválida. Elige una de: " (implode$ ?opcs) crlf))
    (bind ?d (read)))
  (return ?lista))

;; Función para leer los ingredientes que producen alergias
(deffunction input::readAlergias ()
   (printout t "Introduce alergias una a una; escribe 'fin' cuando termines." crlf)
   (bind ?alist (create$))  
   (printout t "Alergia (o fin): " crlf)
   (bind ?a (readline))           
   (while (neq ?a "fin") do
     (bind ?alist (create$ ?alist ?a))
     (printout t "Alergia (o fin): " crlf)
     (bind ?a (readline))
   )
   (return ?alist)
)

;; Función para leer si la bebida debe contener alcohol
(deffunction input::readAlcohol ()
    (printout t "¿Quieres que la bebida contenga alcohol? (si/no/indiferente): " crlf)
    (bind ?alcohol (read))
    (while (not (member$ ?alcohol (create$ si no indiferente))) do
        (printout t "Respuesta inválida. Usa: si, no o indiferente: " crlf)
        (bind ?alcohol (read))
    )
    (return ?alcohol)
)

;; Función que mapea la localidad a un área geográfica
(deffunction mapLocalidadToArea (?loc)
    (if (or (eq ?loc "España") (eq ?loc "Italia") (eq ?loc "Francia")) then
        (return "Europa Occidental")
    else
    (if (or (eq ?loc "Japón") (eq ?loc "China") (eq ?loc "Corea")) then
        (return "Asia Oriental")
    else
    (if (or (eq ?loc "México") (eq ?loc "Perú") (eq ?loc "Colombia")) then
        (return "América Latina")
    else
    (if (or (eq ?loc "Estados Unidos") (eq ?loc "Canadá")) then
        (return "América del Norte")
    else
    (if (or (eq ?loc "India") (eq ?loc "Pakistán")) then
        (return "Asia del Sur")
    else
    (if (or (eq ?loc "Marruecos") (eq ?loc "Egipto")) then
        (return "África del Norte")
    else
    (if (or (eq ?loc "Alemania") (eq ?loc "Polonia")) then
        (return "Europa Central y del Este")
    else
        (return "Desconocida"))))))))
)

;; Función que mapea la fecha a una estación del año
(deffunction mapFechaToEpoca (?data)

  (bind ?slash (str-index "/" ?data))
  (bind ?dia_str (sub-string 1 (- ?slash 1) ?data))
  (bind ?dia  (string-to-field ?dia_str))

  (bind ?split (sub-string (+ ?slash 1) (str-length ?data) ?data))
  (bind ?slash2 (str-index "/" ?split))
  (bind ?mes_str (sub-string 1 (- ?slash2 1) ?split))
  (bind ?mes  (string-to-field ?mes_str))


  (if (or (and (= ?mes 3) (>= ?dia 21))
          (and (>  ?mes 3) (<= ?mes 5))
          (and (= ?mes 6) (<= ?dia 20)))
      then (return "Primavera")
    else
      (if (or (and (= ?mes 6) (>= ?dia 21))
              (and (>  ?mes 6) (<= ?mes 8))
              (and (= ?mes 9) (<= ?dia 20)))
          then (return "Verano")
        else
          (if (or (and (= ?mes 9) (>= ?dia 21))
                  (and (>  ?mes 9) (<= ?mes 11))
                  (and (= ?mes 12) (<= ?dia 20)))
              then (return "Otoño")
            else (return "Invierno")))))


;; Función que sirve para definir la formalidad del evento basado en el tipo de evento
(deffunction mapTipoEventoToTipoPlatos (?tipoEvento)
    (if (eq ?tipoEvento cumpleaños) then
        (return "informal"))
    (if (or (eq ?tipoEvento conferencia) (eq ?tipoEvento reunión) (eq ?tipoEvento boda)) then
        (return "formal"))
    (if (or (eq ?tipoEvento fiesta) (eq ?tipoEvento celebración)) then
        (return "informal"))
        (return "desconocido")
)

;; Calcula el presupuesto de los platos basado en el presupuesto total del evento
(deffunction mapPrecioPlatos (?presupuesto)
    (if (<= ?presupuesto 30) then
        (return "bajo"))
    (if (and (> ?presupuesto 30) (< ?presupuesto 40)) then
        (return "medio"))
    (if (>= ?presupuesto 40) then
        (return "alto"))
    (return "desconocido")
    
)

;; Calcula la complejidad de los platos basado en el presupuesto y el número de comensales
(deffunction mapComplejidadPlatos (?presupuesto ?numComensales)
    (if (< ?presupuesto 20) then
        (return "bajo")
    else if (and (>= ?presupuesto 20) (< ?presupuesto 50)) then
        (if (< ?numComensales 10) then
            (return "medio")
        else
            (return "alto")
        )
    else if (>= ?presupuesto 50) then
        (if (< ?numComensales 10) then
            (return "alto")
        else
            (return "extremo")
        )
    else
        (return "desconocido")
    )
)

;; Calcula la temperatura del menú basado en la época del año
(deffunction solTemperaturaMenu (?epoca)
    (if (or (eq ?epoca "Verano") (eq ?epoca "Primavera")) then (return "Fresco")
    else (return "Calido")
    )
)

;; Calcula la complejidad del menú basado en la complejidad de los platos y la formalidad del evento
(deffunction solComplejidadMenu (?complejidad ?tipo)
  (if (eq ?tipo "formal") then
      (if (eq ?complejidad "bajo") then (return "medio")
      else if (eq ?complejidad "medio") then (return "alto")
      else if (eq ?complejidad "alto") then (return "extremo")
      else (return "extremo"))
    else
      (if (eq ?complejidad "bajo") then (return "bajo")
      else if (eq ?complejidad "medio") then (return "bajo")
      else if (eq ?complejidad "alto") then (return "medio")
      else (return "alto"))
)
)

;; Calcula el score de un plato dado una solución abstracta y un plato concreto
(deffunction refinamiento::scorePlato (?plato ?sol ?pc)
   (bind ?s 0)
   
   
    (bind ?alList (fact-slot-value ?sol alergias))
   (if (> (length$ ?alList) 0) then
     (foreach ?ing (send ?plato get-tiene_ingrediente)
       (bind ?nomStr (send ?ing get-Nombre))  ;; STRING
       (foreach ?al ?alList
         (if (= (str-compare ?nomStr ?al) 0) then
             (return -9999)))))               ;; descartado

   ;; 1) Área
    (if (eq (mapLocalidadToArea (send ?plato get-Localidad))
            (fact-slot-value ?sol areaMenu)) then
        (if (eq (fact-slot-value ?sol tipoMenu) "formal") then
            (bind ?s (+ ?s 20))  ;; más relevante en eventos formales
        else
            (bind ?s (+ ?s 10))))

   
   ;; 2) Precio
   (bind ?pp (fact-slot-value ?pc Presupuesto))
   (bind ?prp (/ ?pp 4.0))
   (bind ?pr (send ?plato get-Precio))
   (if (< ?pr ?prp ) then (bind ?s (+ ?s 15)))
    ;;   (bind ?catPrecio (mapPrecioPlatos (send ?plato get-Precio)))
    ;;   (if (eq ?catPrecio (fact-slot-value ?sol precioMenu))
    ;;       then (bind ?s (+ ?s 2)))
   
   ;; 3) Complejidad
   (bind ?catComp  
         (if (< (send ?plato get-TiempoPreparacion) 0.5) then "bajo"
             else (if (< (send ?plato get-TiempoPreparacion) 1.0)
                       then "medio" else "alto")))
   (if (eq ?catComp (fact-slot-value ?sol complejidadMenu))
       then (bind ?s (- ?s 5)))

    (bind ?form (send ?plato get-Formalidad))
        (if (eq "formal" (fact-slot-value ?sol tipoMenu)) then 
        ;; Para eventos formales, favorecemos bebidas más formales
        (bind ?s (+ ?s (* ?form 0.5)))
    else 
        ;; Para eventos informales, favorecemos bebidas menos formales
        (bind ?bonus (- 10 ?form))
        (bind ?s (+ ?s (* ?bonus 0.5))))
    ;; 4) Epoca
    (bind ?temperaturaMenu (fact-slot-value ?sol temperaturaMenu))
    (bind ?sumadoFALSE FALSE)

    (do-for-all-instances ((?ep Epoca))
        (member$ ?ep (send ?plato get-en_epoca))

        (if (not ?sumadoFALSE) then  

            (if (eq ?temperaturaMenu "Fresco") then
                (if (or (eq (send ?ep get-Nombre) "Verano")
                        (eq (send ?ep get-Nombre) "Primavera"))
                    then
                        ;;(printout t "Fresco " (send ?plato get-Nombre) crlf)
                        (bind ?s (+ ?s 4))
                        (bind ?sumadoFALSE TRUE))) 

            (if (eq ?temperaturaMenu "Calido") then
                (if (and (or (eq (send ?ep get-Nombre) "Invierno")
                                (eq (send ?ep get-Nombre) "Otoño"))
                            (not (eq (send ?ep get-Nombre) "Verano"))
                            (not (eq (send ?ep get-Nombre) "Primavera")))
                    then
                        ;;(printout t "Calido " (send ?plato get-Nombre) crlf)
                        (bind ?s (+ ?s 4))
                        (bind ?sumadoFALSE TRUE))) 
        )
    )


   ;; 5) Dieta: recorremos ingredientes y devolvemos -9999 si alguno falla
      (bind ?ds (fact-slot-value ?sol dietas))
(foreach ?d ?ds
  (do-for-all-instances ((?ing Ingrediente))
      (member$ ?ing (send ?plato get-tiene_ingrediente))
    (if (eq ?d vegetariana) then
        (if (eq (send ?ing get-Vegetariano) false) then (return -9999)))
    (if (eq ?d vegana) then
        (if (eq (send ?ing get-Vegano) false) then (return -9999)))
    (if (eq ?d sin-gluten) then
        (if (eq (send ?ing get-Gluten) true) then (return -9999)))
    (if (eq ?d sin-lactosa) then
        (if (eq (send ?ing get-Lactosa) true) then (return -9999)))
    (if (eq ?d halal) then
        (if (eq (send ?ing get-Halal) false) then (return -9999)))
    (if (eq ?d diabetica) then
        (if (eq (send ?ing get-AptoDiabetico) false) then (return -9999)))
        ))
;; si todas pasan:
(bind ?s (+ ?s 3))

   (return ?s)
)

;; Calcula el score de una bebida segun los datos del problema abstracto y una bebida concreta
(deffunction refinamiento::scoreBebida (?bebida ?sol ?pc)
    (bind ?s 0)
    (bind ?alcohol-sol (fact-slot-value ?sol Alcohol))
    
    ;; 1) Filtrado por alcohol
    (if (eq ?alcohol-sol no) then
        (if (eq (send ?bebida get-Alcohol) true) then (return -9999)))
    (if (eq ?alcohol-sol si) then
        (if (eq (send ?bebida get-Alcohol) false) then (return -9999)))

    ;; 2) Formalidad
    (bind ?form (send ?bebida get-Formalidad))
    (if (eq "formal" (fact-slot-value ?sol tipoMenu)) then 
        ;; Para eventos formales, favorecemos bebidas más formales
        (bind ?s (+ ?s (* ?form 0.5)))
    else 
        ;; Para eventos informales, favorecemos bebidas menos formales
        (bind ?bonus (- 10 ?form))
        (bind ?s (+ ?s (* ?bonus 0.5))))

    ;; 5) Penalty para eventos informales si es vino o cava
    (if (eq "informal" (fact-slot-value ?sol tipoMenu)) then
        (bind ?nombre (send ?bebida get-Nombre))
        (if (or (str-index "Vino" ?nombre) (str-index "Cava" ?nombre)) then
            (bind ?s (- ?s 10))))

    ;; 3) Bonus por temperatura acorde al menú
    (bind ?tempMenu (fact-slot-value ?sol temperaturaMenu))
    (if (eq ?tempMenu "Fresco") then
        (if (or (eq (send ?bebida get-Temperatura) "Fría")
                (eq (send ?bebida get-Temperatura) "Indiferente"))
            then (bind ?s (+ ?s 5))))
    (if (eq ?tempMenu "Calido") then
        (if (or (eq (send ?bebida get-Temperatura) "Caliente")
                (eq (send ?bebida get-Temperatura) "Indiferente"))
            then (bind ?s (+ ?s 5))))

    (bind ?s (+ ?s 3))

    (bind ?pp (fact-slot-value ?pc Presupuesto))
   (bind ?prp (/ ?pp 4.0))
   (bind ?pr (send ?bebida get-Precio))
    ;; 4) Precio - normalizar y ajustar según presupuesto
    (if (< ?pr ?prp ) then (bind ?s (+ ?s 10)))
    ;; Penalización si la bebida es demasiado cara
    (if (> ?pr (* ?prp 1.5)) then (bind ?s (- ?s 10)))

    ;;Zona de origen
    (bind ?areaMenu (fact-slot-value ?sol areaMenu))
    (bind ?areaBebida (send ?bebida get-Zona))
    (if (eq ?areaMenu ?areaBebida) then
        (bind ?s (+ ?s 10)))

    (bind ?ds (fact-slot-value ?sol dietas))
    (if (eq ?ds diabetica) then 
        (if (eq (send ?bebida get-AptoDiabetico) false) then (return -9999)))
    ;;(printout t "Score bebida " (send ?bebida get-Nombre) ": " ?s crlf)

    (return ?s)
)

;; Devuelve una lista sin elmentos repetidos
(deffunction refinamiento::lista-unica (?lista)
  (bind ?resultado (create$))
  (foreach ?elem ?lista
    (if (not (member$ ?elem ?resultado)) then
      (bind ?resultado (create$ ?resultado ?elem))))
  (return ?resultado))

;; Devuelve el número de ingredientes repetidos en los platos
(deffunction refinamiento::ingredientesRepetidos (?p1 ?p2 ?p3)
  (bind ?all (create$))
  ;; Recorre los platos y crea una lista de todos los ingredientes
  (foreach ?p (create$ ?p1 ?p2 ?p3)
    (do-for-all-instances ((?i Ingrediente))
        (member$ ?i (send ?p get-tiene_ingrediente))
      (bind ?all (create$ ?all (send ?i get-Nombre)))))
  (bind ?total (length$ ?all))
  (bind ?unique (length$ (refinamiento::lista-unica ?all)))
  ;; Devuelve la diferencia entre el total y los ingredientes únicos
  (return (- ?total ?unique)))



;; Devuelve los 3 mejores candidatos de un tipo concreto, ordenados por score
(deffunction refinamiento::top3CandidatesPorTipo (?tipo)
  (bind ?top1 nil) (bind ?score1 -1e+30)
  (bind ?top2 nil) (bind ?score2 -1e+30)
  (bind ?top3 nil) (bind ?score3 -1e+30)
    ;; Recorre todos los CandidateMenu
  (do-for-all-facts ((?c CandidateMenu))
      TRUE
    (if (eq (send (fact-slot-value ?c instancia) get-Tipo) ?tipo) then
      (bind ?sc (fact-slot-value ?c score))
      (if (> ?sc ?score1) then
          (bind ?top3 ?top2) (bind ?score3 ?score2)
          (bind ?top2 ?top1) (bind ?score2 ?score1)
          (bind ?top1 ?c)    (bind ?score1 ?sc)
       else
         (if (> ?sc ?score2) then
             (bind ?top3 ?top2) (bind ?score3 ?score2)
             (bind ?top2 ?c)    (bind ?score2 ?sc)
          else
             (if (> ?sc ?score3) then
                 (bind ?top3 ?c) (bind ?score3 ?sc))))))
  (return (create$ ?top1 ?top2 ?top3))
)

;; Devuelve los 3 mejores candidatos de bebida, ordenados por score
(deffunction refinamiento::top3CandidatesBebida ()
  (bind ?top1 nil) (bind ?score1 -1e+30)
  (bind ?top2 nil) (bind ?score2 -1e+30)
  (bind ?top3 nil) (bind ?score3 -1e+30)
  ;; Recorre todos los CandidateBebida
  (do-for-all-facts ((?c CandidateBebida)) TRUE
    (bind ?sc (fact-slot-value ?c score))
    (if (> ?sc ?score1) then
        (bind ?top3 ?top2) (bind ?score3 ?score2)
        (bind ?top2 ?top1) (bind ?score2 ?score1)
        (bind ?top1 ?c)    (bind ?score1 ?sc)
      else
        (if (> ?sc ?score2) then
            (bind ?top3 ?top2) (bind ?score3 ?score2)
            (bind ?top2 ?c)    (bind ?score2 ?sc)
          else
            (if (> ?sc ?score3) then
                (bind ?top3 ?c) (bind ?score3 ?sc)))))
  (return (create$ ?top1 ?top2 ?top3))
)

;; Para un input concreto, devuelve el manú más caro de los CombinedMenu
(deffunction maxMenuFact (?pr)
  (bind ?bestFact nil)
  (bind ?bestTotal -1e+30)
  (do-for-all-facts ((?c CombinedMenu)) TRUE
    (bind ?t (fact-slot-value ?c total))
    (if (and (> ?t ?bestTotal) (< ?t ?pr)) then
      (bind ?bestTotal ?t)
      (bind ?bestFact ?c)))
  (return ?bestFact)
)

;; Para un input concreto, devuelve el manú más barato de los CombinedMenu
(deffunction minMenuFact (?pr)
  (bind ?bestFact nil)
  (bind ?bestTotal 1e+30)
  (do-for-all-facts ((?c CombinedMenu)) TRUE
    (bind ?t (fact-slot-value ?c total))
    (if (and (< ?t ?bestTotal) (< ?t ?pr)) then
      (bind ?bestTotal ?t)
      (bind ?bestFact ?c)))
  (return ?bestFact)
)

;; Para un input concreto, devuelve el menú más cercano al punto medio entre el más caro y el más barato
(deffunction midMenuFact (?pr)
  ;; Obtiene los fact‐address de los menús más caro y más barato
  (bind ?maxF (maxMenuFact ?pr))
  (bind ?minF (minMenuFact ?pr))
  (bind ?maxT (fact-slot-value ?maxF total))
  (bind ?minT (fact-slot-value ?minF total))
  ;; Calcula el punto medio
  (bind ?mid (/ (+ ?maxT ?minT) 2))

  ;; Variables para el mejor candidato y su “distancia” al medio
  (bind ?bestF nil)
  (bind ?bestDiff (+ ?maxT ?minT))  ;; valor inicial muy grande
  ;; Recorre todos los CombinedMenu
  (do-for-all-facts ((?c CombinedMenu)) TRUE
    (bind ?t (fact-slot-value ?c total))
    ;; Ignora extremos (igual a max o min)
    (if (and (neq ?t ?maxT) (neq ?t ?minT)) then
      (bind ?diff (abs (- ?t ?mid)))
      ;; Si está más cerca del medio que el actual “mejor”, lo actualizamos
      (if (< ?diff ?bestDiff) then
        (bind ?bestDiff ?diff)
        (bind ?bestF ?c))))
  ;; Devuelve el mejor encontrado, o el más caro si no hay ninguno intermedio
  (if (neq ?bestF nil)
      then (return ?bestF)
      else (return ?maxF)))

;; Para un total concreto, devuelve el score máximo entre todos los CombinedMenu con ese total
(deffunction highestScoreForTotal (?target)
  (bind ?best -1)
  (do-for-all-facts ((?c CombinedMenu)) (eq (fact-slot-value ?c total) ?target)
    (bind ?s (fact-slot-value ?c score))
    (if (> ?s ?best) then (bind ?best ?s)))
  (return ?best))



;; Defrules


(defrule MAIN::init
    (declare (salience 10))
    =>
    (printout t "--Sistema de cátering RicoRico--" crlf)
    ;(printout t "Vamos al input" crlf)
    (focus input)
)

(defrule MAIN::vuelve-de-input
    (declare (salience 9))
    =>
    ;(printout t "Vuelve del input" crlf)
)

(defrule MAIN::init-a-abstraccion
    (declare (salience 8))
    =>
    ;(printout t "Vamos a la abstraccion" crlf)
    (focus abstraccion)
)

(defrule MAIN::vuelve-de-abstraccion
    (declare (salience 7))
    =>
    ;(printout t "Vuelve de abstraccion" crlf)
)

(defrule MAIN::init-a-asociacionHeuristica
    (declare (salience 6))
    =>
    ;(printout t "Vamos a la asociacionHeuristica" crlf)
    (focus asociacionHeuristica)
)

(defrule MAIN::vuelve-de-asociacionHeuristica
    (declare (salience 5))
    =>
    ;(printout t "Vuelve de asociacionHeuristica" crlf)
)

(defrule MAIN::init-a-refinamiento
    (declare (salience 4))
    =>
    ;(printout t "Vamos al refinamiento" crlf)
    (focus refinamiento)
)

(defrule MAIN::vuelve-de-refinamiento
    (declare (salience 3))
    =>
    ;(printout t "Vuelve de refinamiento" crlf)
)


(defrule MAIN::init-a-impresion
    (declare (salience 2))
    =>
    ;(printout t "Vamos a impresionSolucion" crlf)
    (focus impresionSolucion)
)

(defrule MAIN::vuelve-de-impresion
    (declare (salience 1))
    =>
    ;(printout t "Volvemos de impresionSolucion" crlf)
)

(defrule MAIN::fin
    (declare (salience -20))
    =>
    ;(printout t "Fin del sistema experto" crlf)
)

;; Regla para leer la información del evento y crear el hecho InfoEvento
(defrule input::readInfoEvento
    (declare (salience 10))
    =>
    (printout t "Bienvenido al sistema de planificación de eventos." crlf)
    (printout t "Por favor, introduce la información del evento." crlf)
    (bind ?nombre (readNombre))
    (bind ?localidad (readLocalidad))
    (bind ?tipoEvento (readTipoEvento))
    (bind ?fecha (readFecha))
    (bind ?presupuesto (readPresupuesto))
    (bind ?numComensales (readNumComensales))
    (bind $?dietas (readDietas))
    (bind $?alergias (readAlergias))
    (bind ?alcohol (readAlcohol))

    (assert (InfoEvento
        (Nombre ?nombre)
        (Fecha ?fecha)
        (Localidad ?localidad)
        (TipoEvento ?tipoEvento)
        (Presupuesto ?presupuesto)
        (numComensales ?numComensales)
        (dietas $?dietas)
        (alergias $?alergias)
        (Alcohol ?alcohol))
    )

) 

;; Regla para generar la información abstracta del evento
(defrule abstraccion::absInfoEventoA
   (InfoEvento 
      (Localidad     ?loc)
      (Fecha         ?f)
      (dietas         $?d)
      (TipoEvento    ?te)
      (Presupuesto   ?p)
      (numComensales ?nc)
      (alergias      $?alergias)
      (Alcohol       ?alcohol))
   (not (InfoEventoA))
   =>

   (bind ?epoca (mapFechaToEpoca ?f))
   (bind ?area  (mapLocalidadToArea ?loc))
   (bind ?tP    (mapTipoEventoToTipoPlatos ?te))
   (bind ?pP    (mapPrecioPlatos ?p))
   (bind ?cP    (mapComplejidadPlatos ?p ?nc))

   (assert (InfoEventoA
     (Area              ?area)
     (Temporada         ?epoca)
     (dietas $?d)
     (tipoPlatos        ?tP)
     (precioPlatos      ?pP)
     (complejidadPlatos ?cP)
    (alergias          $?alergias)
    (Alcohol           ?alcohol)
     ))
)

;; Regla para generar la solución abstracta 
(defrule asociacionHeuristica::defSolAbstracta
    (InfoEventoA
        (Area ?area)
        (Temporada ?temp)
        (dietas $?dietas)
        (tipoPlatos ?tP)
        (precioPlatos ?pP)
        (complejidadPlatos ?cP)
        (alergias $?alergias)
        (Alcohol ?alcohol)
        )
        (not (SolAbstracta))
        =>
        (bind ?temperatura (solTemperaturaMenu ?temp))
        (bind ?cM (solComplejidadMenu ?cP ?tP))
        (assert (SolAbstracta
            (temperaturaMenu ?temperatura)
            (areaMenu ?area)
            (tipoMenu ?tP)
            (precioMenu ?pP)
            (complejidadMenu ?cM)
            (dietas $?dietas)
            (alergias $?alergias)
            (Alcohol ?alcohol)
        ))
)

;; Regla para generar candidatos de platos
(defrule refinamiento::genera-candidatos
    (declare (salience 100))
   ?sol <- (SolAbstracta)
   ?pc <- (InfoEvento)
   (not (CandidateMenu))    
   =>
   ;; Bucle que itera sobre todas las instancias de Plato
   (do-for-all-instances ((?p Plato))
       TRUE
     
    ;; Calculamos el score del plato segun los datos del evento
     (bind ?sc (scorePlato ?p ?sol ?pc))
     
    ;; Si el score es mayor que -1000, lo consideramos candidato
     (if (> ?sc -1000) then
         (assert (CandidateMenu
                    (nombre    (send ?p get-Nombre))
                    (instancia ?p)
                    (score     ?sc))))))

;; Regla para generar candidatos de bebidas
(defrule refinamiento::genera-candidatos-bebidas
    (declare (salience 99))
   ?sol <- (SolAbstracta)
   ?pc <- (InfoEvento)
   (not (CandidateBebida))    
   =>
   ;; Bucle que itera sobre todas las instancias de Bebida
   (do-for-all-instances ((?b Bebida))
       TRUE
     
     ;; Calculamos el score de la bebida segun los datos del evento
     (bind ?sc (scoreBebida ?b ?sol ?pc))
     
     ;; Si el score es mayor que -1000, lo consideramos candidato
     (if (> ?sc -1000) then
         (assert (CandidateBebida
                    (nombre    (send ?b get-Nombre))
                    (instancia ?b)
                    (score     ?sc)))))
                    )
 

;; PRINCIPALES
;; Selecciona los 3 mejores principales candidatos (según el score)
(defrule refinamiento::select-principales-top3
  (SolAbstracta)
  (not (SelectedMenu (tipo "Principal") (orden 1)))
  =>
  ;; obtenemos los 3 fact‐addresses
  (bind $?cands (refinamiento::top3CandidatesPorTipo "Principal"))
  (bind ?c1 (nth$ 1 $?cands))
  (bind ?c2 (nth$ 2 $?cands))
  (bind ?c3 (nth$ 3 $?cands))

  ;; y los agregamos a SelectedMenu como plato Principal
  (assert (SelectedMenu
            (plato  (fact-slot-value ?c1 instancia))
            (nombre (send (fact-slot-value ?c1 instancia) get-Nombre))
            (precio (send (fact-slot-value ?c1 instancia) get-Precio))
            (score  (fact-slot-value ?c1 score))
            (tipo   "Principal")
            (orden  1)))
  (assert (SelectedMenu
            (plato  (fact-slot-value ?c2 instancia))
            (nombre (send (fact-slot-value ?c2 instancia) get-Nombre))
            (precio (send (fact-slot-value ?c2 instancia) get-Precio))
            (score  (fact-slot-value ?c2 score))
            (tipo   "Principal")
            (orden  2)))
  (assert (SelectedMenu
            (plato  (fact-slot-value ?c3 instancia))
            (nombre (send (fact-slot-value ?c3 instancia) get-Nombre))
            (precio (send (fact-slot-value ?c3 instancia) get-Precio))
            (score  (fact-slot-value ?c3 score))
            (tipo   "Principal")
            (orden  3)))
)


;; SEGUNDOS
;; Selecciona los 3 mejores segundos candidatos (según el score)
(defrule refinamiento::select-segundos-top3
  (SolAbstracta)
  (not (SelectedMenu (tipo "Segundo") (orden 1)))
  =>
  (bind $?cands (refinamiento::top3CandidatesPorTipo "Segundo"))
  (bind ?c1 (nth$ 1 $?cands))
  (bind ?c2 (nth$ 2 $?cands))
  (bind ?c3 (nth$ 3 $?cands))

  (assert (SelectedMenu
            (plato  (fact-slot-value ?c1 instancia))
            (nombre (send (fact-slot-value ?c1 instancia) get-Nombre))
            (precio (send (fact-slot-value ?c1 instancia) get-Precio))
            (score  (fact-slot-value ?c1 score))
            (tipo   "Segundo")
            (orden  1)))
  (assert (SelectedMenu
            (plato  (fact-slot-value ?c2 instancia))
            (nombre (send (fact-slot-value ?c2 instancia) get-Nombre))
            (precio (send (fact-slot-value ?c2 instancia) get-Precio))
            (score  (fact-slot-value ?c2 score))
            (tipo   "Segundo")
            (orden  2)))
  (assert (SelectedMenu
            (plato  (fact-slot-value ?c3 instancia))
            (nombre (send (fact-slot-value ?c3 instancia) get-Nombre))
            (precio (send (fact-slot-value ?c3 instancia) get-Precio))
            (score  (fact-slot-value ?c3 score))
            (tipo   "Segundo")
            (orden  3)))
)


;; POSTRES
;; Selecciona los 3 mejores postres candidatos (segun el score)
(defrule refinamiento::select-postres-top3
  (SolAbstracta)
  (not (SelectedMenu (tipo "Postre") (orden 1)))
  =>
  (bind $?cands (refinamiento::top3CandidatesPorTipo "Postre"))
  (bind ?c1 (nth$ 1 $?cands))
  (bind ?c2 (nth$ 2 $?cands))
  (bind ?c3 (nth$ 3 $?cands))

  (assert (SelectedMenu
            (plato  (fact-slot-value ?c1 instancia))
            (nombre (send (fact-slot-value ?c1 instancia) get-Nombre))
            (precio (send (fact-slot-value ?c1 instancia) get-Precio))
            (score  (fact-slot-value ?c1 score))
            (tipo   "Postre")
            (orden  1)))
  (assert (SelectedMenu
            (plato  (fact-slot-value ?c2 instancia))
            (nombre (send (fact-slot-value ?c2 instancia) get-Nombre))
            (precio (send (fact-slot-value ?c2 instancia) get-Precio))
            (score  (fact-slot-value ?c2 score))
            (tipo   "Postre")
            (orden  2)))
  (assert (SelectedMenu
            (plato  (fact-slot-value ?c3 instancia))
            (nombre (send (fact-slot-value ?c3 instancia) get-Nombre))
            (precio (send (fact-slot-value ?c3 instancia) get-Precio))
            (score  (fact-slot-value ?c3 score))
            (tipo   "Postre")
            (orden  3)))
)

;; BEBIDAS

;; Selecciona las 3 mejores bebidas candidatas (segun el score)
(defrule refinamiento::select-bebidas-top3
    (SolAbstracta)
   (not (SelectedBebida (orden 1)))
   =>
   (bind $?cands (refinamiento::top3CandidatesBebida))
   (bind ?c1 (nth$ 1 $?cands))
   (bind ?c2 (nth$ 2 $?cands))
   (bind ?c3 (nth$ 3 $?cands))
   
   (if (neq ?c1 nil) then
       (assert (SelectedBebida
                 (bebida   (fact-slot-value ?c1 instancia))
                 (nombre   (send (fact-slot-value ?c1 instancia) get-Nombre))
                 (precio   (send (fact-slot-value ?c1 instancia) get-Precio))
                 (score    (fact-slot-value ?c1 score))
                 (orden    1))))
   (if (neq ?c2 nil) then     
       (assert (SelectedBebida
                 (bebida   (fact-slot-value ?c2 instancia))
                 (nombre   (send (fact-slot-value ?c2 instancia) get-Nombre))
                 (precio   (send (fact-slot-value ?c2 instancia) get-Precio)) 
                 (score    (fact-slot-value ?c2 score))
                 (orden    2))))
   (if (neq ?c3 nil) then
       (assert (SelectedBebida
                 (bebida   (fact-slot-value ?c3 instancia))
                 (nombre   (send (fact-slot-value ?c3 instancia) get-Nombre))
                 (precio   (send (fact-slot-value ?c3 instancia) get-Precio))
                 (score    (fact-slot-value ?c3 score))
                 (orden    3))))
)


;; Se usa para evitar imprimir un menú más de una vez
(deftemplate PrintedCombinedMenu (slot done (type SYMBOL)))

;; Regla que combina los platos y la bebida seleccionada en un único menú
(defrule refinamiento::combine-selected
   (declare (salience 1))
   (SelectedMenu (tipo "Principal") (nombre ?n1) (precio ?p1) (score ?s1) (plato ?pl1))
   (SelectedMenu (tipo "Segundo")   (nombre ?n2) (precio ?p2) (score ?s2) (plato ?pl2))
   (SelectedMenu (tipo "Postre")    (nombre ?n3) (precio ?p3) (score ?s3) (plato ?pl3))
   (SelectedBebida (nombre ?nb) (precio ?pb) (score ?sb))
   (not (CombinedMenu (principal ?n1) (segundo ?n2) (postre ?n3) (bebida ?nb)))
   =>

   ;; Evitamos combinaciones con más de 3 ingredientes repetidos
   (bind ?repe (refinamiento::ingredientesRepetidos ?pl1 ?pl2 ?pl3))
   (if (> ?repe 3) then
     (return))

   (bind ?total (+ ?p1 ?p2 ?p3 ?pb))
   (bind ?s (+ ?s1 ?s2 ?s3 ?sb))
   (assert (CombinedMenu
             (principal ?n1)
             (segundo   ?n2)
             (postre    ?n3)
             (bebida    ?nb)
             (total     ?total)
             (score     ?s))))


;; Regla de impresión de los menús, imprimer uno caro, otro intermedio y el último barato
(defrule impresionSolucion::print-menus
   (declare (salience -50))
   (CombinedMenu)
   ?pc <- (InfoEvento)
   (not (PrintedCombinedMenu (done yes)))
   =>
   ;; Obtenemos los fact-address de cada menú
   (bind ?pr (fact-slot-value ?pc Presupuesto))
   (bind ?maxFact (maxMenuFact ?pr))
   (bind ?midFact (midMenuFact ?pr))
   (bind ?minFact (minMenuFact ?pr))

   (printout t crlf
   "Aunque no sea la bebida principal el agua siempre esta disponible" crlf
     "*** MENÚ MÁS CARO ***" crlf
     " Total: " (fact-slot-value ?maxFact total) " $" crlf
     "  P: "   (fact-slot-value ?maxFact principal) crlf
     "  S: "   (fact-slot-value ?maxFact segundo) crlf
     "  Po: "  (fact-slot-value ?maxFact postre) crlf 
     "  B: "   (fact-slot-value ?maxFact bebida) crlf crlf

     "*** MENÚ INTERMEDIO ***" crlf
     " Total: " (fact-slot-value ?midFact total) " $" crlf
     "  P: "   (fact-slot-value ?midFact principal) crlf
     "  S: "   (fact-slot-value ?midFact segundo) crlf
     "  Po: "  (fact-slot-value ?midFact postre) crlf
     "  B: "   (fact-slot-value ?midFact bebida) crlf crlf

     "*** MENÚ MÁS BARATO ***" crlf
     " Total: " (fact-slot-value ?minFact total) " $" crlf
     "  P: "   (fact-slot-value ?minFact principal) crlf
     "  S: "   (fact-slot-value ?minFact segundo) crlf
     "  Po: "  (fact-slot-value ?minFact postre) crlf
     "  B: "   (fact-slot-value ?minFact bebida) crlf)

   ;; Marcamos para que no vuelva a imprimirse
   (assert (PrintedCombinedMenu (done yes)))
)



