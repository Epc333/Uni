(definstances init-instances
    ;;Épocas del año
    ([Verano] of Epoca (Nombre "Verano"))
    ([Invierno] of Epoca (Nombre "Invierno"))
    ([Primavera] of Epoca (Nombre "Primavera"))
    ([Otono] of Epoca (Nombre "Otoño"))

    ;;Bebidas genéricas
    ([Agua]    of Bebida (Nombre "Agua"))
    ([Cerveza] of Bebida (Nombre "Cerveza"))
    ([Refresco] of Bebida (Nombre "Refresco"))

    ;;Vinos
    ([VinoTinto]  of Vino (Nombre "Vino Tinto"))
    ([VinoBlanco] of Vino (Nombre "Vino Blanco"))
    ([VinoRosado] of Vino (Nombre "Vino Rosado"))

    ;;Ingredientes con temporada y propiedades
    ([Tomate] of Ingrediente
         (Nombre "Tomate")
         (Gluten false) (Lactosa false)
         (Vegano true) (Vegetariano true)
         (en_epoca [Verano]) )
    ([Lechuga] of Ingrediente
         (Nombre "Lechuga")
         (Gluten false) (Lactosa false)
         (Vegano true) (Vegetariano true)
         (en_epoca [Primavera]) )
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
         (Vegano true) (Vegetariano true)
         (en_epoca [Verano]) )
    ([PimientoVerde] of Ingrediente
         (Nombre "Pimiento Verde")
         (Gluten false) (Lactosa false)
         (Vegano true) (Vegetariano true)
         (en_epoca [Primavera]) )
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
        (Vegano false)  (Vegetariano true))
    ;; Dulces y edulcorantes
    ([Azucar] of Ingrediente
        (Nombre "Azúcar")
        (Gluten false)  (Lactosa false)
        (Vegano true)   (Vegetariano true))
    ;; Frutas y derivados
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
    ([Nuez] of Ingrediente
        (Nombre "Nuez")
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
        (Vegano true) (Vegetariano true) )
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
        (Vegano true) (Vegetariano true) )
    ([Sirope] of Ingrediente
        (Nombre "Sirope")
        (Gluten false) (Lactosa false)
        (Vegano true) (Vegetariano true) )
    ([HarinaArroz] of Ingrediente
        (Nombre "Harina de Arroz")
        (Gluten false) (Lactosa false)
        (Vegano true) (Vegetariano true) )
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
    
    

    ;;Platos típicos con ingredientes, localidad, precio y tiempo de preparación
    ([PaellaVegetariana] of Plato
        (Nombre "Paella Vegetariana")
        (Localidad "España")
        (Precio 14.5)
        (TiempoPreparacion 1.8)
        (Tipo "Principal")
        (tiene_ingrediente [Arroz] [PimientoVerde] [PimientoRojo] [AceiteOliva] [Alga]) )
    
    ([TacosVegetales] of Plato
        (Nombre "Tacos Veganos")
        (Localidad "México")
        (Precio 9.0)
        (TiempoPreparacion 1.0)
        (Tipo "Principal")
        (tiene_ingrediente [Harina] [PimientoRojo] [Tomate] [Lechuga] [AceiteOliva]) )
    ([CurryVegetariano] of Plato
        (Nombre "Curry Vegetariano")
        (Localidad "India")
        (Precio 13.0)
        (TiempoPreparacion 1.2)
        (Tipo "Principal")
        (tiene_ingrediente [Arroz] [PimientoRojo] [Ajo] [EspeciasCurry] [AceiteOliva]) )
    
    ([QuinoaSalteada] of Plato
        (Nombre "Quinoa Salteada con Vegetales")
        (Localidad "Perú")
        (Precio 11.5)
        (TiempoPreparacion 1.0)
        (Tipo "Principal")
        (tiene_ingrediente [Quinoa] [Espinaca] [Ajo] [AceiteOliva] [PimientoRojo]) )
    
    ([Ensalada] of Plato
        (Nombre "Ensalada Mixta")
        (Localidad "España")
        (Precio 8.5)
        (TiempoPreparacion 0.3)
        (Tipo "Principal")
        (tiene_ingrediente [Lechuga] [Tomate] [AceiteOliva]) )
    
    ([PastaTomate] of Plato
        (Nombre "Pasta con Tomate")
        (Localidad "Italia")
        (Precio 12.0)
        (TiempoPreparacion 1.0)
        (Tipo "Principal")
        (tiene_ingrediente [Pasta] [Harina] [Tomate] [AceiteOliva]) )
    
    ([PizzaHawaiana] of Plato
        (Nombre "Pizza Hawaiana")
        (Localidad "Italia")
        (Precio 14.5)
        (TiempoPreparacion 1.5)
        (Tipo "Principal")
        (tiene_ingrediente [Harina] [Queso] [Pollo] [Piña] [AceiteOliva]) )
   
    ([SushiClasico] of Plato
        (Nombre "Sushi Clásico")
        (Localidad "Japón")
        (Precio 18.0)
        (TiempoPreparacion 1.2)
        (Tipo "Principal")
        (tiene_ingrediente [Arroz] [Alga] [Atun]) )
   
    ([TacoCarne] of Plato
        (Nombre "Taco de Carne")
        (Localidad "México")
        (Precio 9.0)
        (TiempoPreparacion 0.5)
        (Tipo "Principal")
        (tiene_ingrediente [Harina] [Carne] [Queso]) )
    
    ([Paella] of Plato
        (Nombre "Paella Valenciana")
        (Localidad "España")
        (Precio 15.0)
        (TiempoPreparacion 2.0)
        (Tipo "Principal")
        (tiene_ingrediente [Arroz] [Pollo] [AceiteOliva]) )
    

    ;; Nuevas instancias: Segundos
    
    ([SopaAgridulce] of Plato
        (Nombre "Sopa Agridulce China")
        (Localidad "China")
        (Precio 6.0)
        (TiempoPreparacion 0.9)
        (Tipo "Segundo")
        (tiene_ingrediente [Vinagre] [Azucar] [Champiñones] [Tofu] [Zanahoria] [Brocoli]))
    
    ([PaellaVegetal] of Plato
        (Nombre "Paella de Verduras")
        (Localidad "España")
        (Precio 13.0)
        (TiempoPreparacion 1.4)
        (Tipo "Segundo")
        (tiene_ingrediente [Arroz] [Pimiento] [Alcachofa] [AceiteOliva]) )

    ([PastaPesto] of Plato
        (Nombre "Pasta al Pesto")
        (Localidad "Italia")
        (Precio 12.0)
        (TiempoPreparacion 1.1)
        (Tipo "Segundo")
        (tiene_ingrediente [Pasta] [Albahaca] [Nuez] [AceiteOliva]) )

    ([Ratatouille] of Plato
        (Nombre "Ratatouille Provenzal")
        (Localidad "Francia")
        (Precio 11.5)
        (TiempoPreparacion 1.3)
        (Tipo "Segundo")
        (tiene_ingrediente [Berenjena] [Tomate] [Pimiento]) )

    ([PatatasGratinadas] of Plato
        (Nombre "Patatas Gratinadas")
        (Localidad "Francia")
        (Precio 10.0)
        (TiempoPreparacion 1.2)
        (Tipo "Segundo")
        (tiene_ingrediente [Patata] [Queso] [Leche]))

    ([TeriyakiTofu] of Plato
        (Nombre "Tofu al Teriyaki")
        (Localidad "Japón")
        (Precio 14.0)
        (TiempoPreparacion 1.2)
        (Tipo "Segundo")
        (tiene_ingrediente [Tofu] [SalsaTeriyaki] [Cebolla] [Sésamo]) )

    ([SalteadoVerduras] of Plato
        (Nombre "Salteado de Verduras al Wok")
        (Localidad "China")
        (Precio 10.5)
        (TiempoPreparacion 1.0)
        (Tipo "Segundo")
        (tiene_ingrediente [Brocoli] [Zanahoria] [Pimiento] [SalsaSoja]) )

    ([BibimbapVegano] of Plato
        (Nombre "Bibimbap Vegano")
        (Localidad "Corea")
        (Precio 13.5)
        (TiempoPreparacion 1.5)
        (Tipo "Segundo")
        (tiene_ingrediente [Arroz] [Tofu] [Zanahoria] [Cebolla] [Alga] [Champiñones]) )

    ([LomoSaltado] of Plato
        (Nombre "Lomo Saltado")
        (Localidad "Perú")
        (Precio 11.0)
        (TiempoPreparacion 1.2)
        (Tipo "Segundo")
        (tiene_ingrediente [Carne] [Cebolla] [Tomate]) )

    ([Arepa] of Plato
        (Nombre "Arepa")
        (Localidad "Colombia")
        (Precio 9.5)
        (TiempoPreparacion 1.0)
        (Tipo "Segundo")
        (tiene_ingrediente [Harina] [Tomate] [Queso] [Huevo]) )

    ([BurgerVegana] of Plato
        (Nombre "Hamburguesa Vegana BBQ")
        (Localidad "Estados Unidos")
        (Precio 12.5)
        (TiempoPreparacion 1.3)
        (Tipo "Segundo")
        (tiene_ingrediente [HamburguesaVegetal] [PanSinGluten] [Lechuga] [Cebolla] [Tomate]) )

    ([Hmburguesa] of Plato
        (Nombre "Hamburguesa")
        (Localidad "Estados Unidos")
        (Precio 11.5)
        (TiempoPreparacion 1.3)
        (Tipo "Segundo")
        (tiene_ingrediente [Hamburguesa] [Pan] [Lechuga] [Cebolla] [Tomate]) )

    ([MacAndCheese] of Plato
        (Nombre "Mac and Cheese")
        (Localidad "Canadá")
        (Precio 7.5)
        (TiempoPreparacion 1.0)
        (Tipo "Segundo")
        (tiene_ingrediente [Pasta] [Queso] [Leche] [AceiteOliva] [Nuez]))

    ([CurryLentejas] of Plato
        (Nombre "Curry de Lentejas")
        (Localidad "India")
        (Precio 9.5)
        (TiempoPreparacion 1.2)
        (Tipo "Segundo")
        (tiene_ingrediente [Lentejas] [LecheCoco] [Curry] [Tomate]) )

    ([KarahiVegetariano] of Plato
        (Nombre "Karahi Vegetariano")
        (Localidad "Pakistán")
        (Precio 10.5)
        (TiempoPreparacion 1.3)
        (Tipo "Segundo")
        (tiene_ingrediente [Tomate] [Pimiento] [Garbanzos] [Especias]) )

    ([TagineVerduras] of Plato
        (Nombre "Tajín de Verduras")
        (Localidad "Marruecos")
        (Precio 11.5)
        (TiempoPreparacion 1.5)
        (Tipo "Segundo")
        (tiene_ingrediente [Zanahoria] [Calabaza] [Garbanzos]) )

    ([FileteRes] of Plato
        (Nombre "Filete de Res a la Plancha")
        (Localidad "Argentina")
        (Precio 16.0)
        (TiempoPreparacion 1.3)
        (Tipo "Segundo")
        (tiene_ingrediente [Carne] [AceiteOliva]) )

    ([PolloAsado] of Plato
        (Nombre "Pollo Asado con Hierbas")
        (Localidad "España")
        (Precio 14.0)
        (TiempoPreparacion 1.5)
        (Tipo "Segundo")
        (tiene_ingrediente [Pollo] [AceiteOliva]) )

    ([TofuGrillado] of Plato
        (Nombre "Tofu Grillado con Verduras")
        (Localidad "Japón")
        (Precio 13.0)
        (TiempoPreparacion 1.2)
        (Tipo "Segundo")
        (tiene_ingrediente [Tofu] [Pimiento] [Zucchini] [AceiteSesamo]) )

    ;; Nuevas instancias: Postres
    ([ArrozConLeche] of Plato
        (Nombre "Arroz con Leche")
        (Localidad "España")
        (Precio 5.0)
        (TiempoPreparacion 0.8)
        (Tipo "Postre")
        (tiene_ingrediente [Arroz] [Leche] [Azucar]) )

    ([TartaChocolate] of Plato
        (Nombre "Tarta de Chocolate")
        (Localidad "Francia")
        (Precio 6.5)
        (TiempoPreparacion 1.2)
        (Tipo "Postre")
        (tiene_ingrediente [Harina] [Huevos] [Azucar] [Chocolate]) )

    ([HeladoFrutas] of Plato
        (Nombre "Helado de Frutas")
        (Localidad "Italia")
        (Precio 5.5)
        (TiempoPreparacion 0.5)
        (Tipo "Postre")
        (tiene_ingrediente [Leche] [Azucar] [Frutas]) )

    ([MousseChocolate] of Plato
        (Nombre "Mousse de Chocolate")
        (Localidad "Francia")
        (Precio 6.0)
        (TiempoPreparacion 1.0)
        (Tipo "Postre")
        (tiene_ingrediente [Aguacate] [Cacao] [Sirope] [LecheCoco]))

    ([Tangyuan] of Plato
        (Nombre "Tangyuan - Bolas de Arroz Dulces")
        (Localidad "China")
        (Precio 5.0)
        (TiempoPreparacion 0.7)
        (Tipo "Postre")
        (tiene_ingrediente [HarinaArroz] [Azucar] [Agua] [Sésamo]))

    ([Mochi] of Plato
        (Nombre "Mochi - Pastel de Arroz")
        (Localidad "Japón")
        (Precio 5.5)
        (TiempoPreparacion 0.8)
        (Tipo "Postre")
        (tiene_ingrediente [HarinaArroz] [Azucar] [FrijolDulce] [Agua]))

    ([Hotteok] of Plato
        (Nombre "Hotteok - Panqueques Dulces Coreanos")
        (Localidad "Corea")
        (Precio 4.5)
        (TiempoPreparacion 0.9)
        (Tipo "Postre")
        (tiene_ingrediente [HarinaTrigo] [Azucar] [Nueces] [Canela] [Levadura]))
    ([MacedoniaFrutas] of Plato
        (Nombre "Macedonia de Frutas Frescas")
        (Localidad "España")
        (Precio 5.0)
        (TiempoPreparacion 0.5)
        (Tipo "Postre")
        (tiene_ingrediente [Manzana] [Naranja] [Kiwi] [Fresas] [Sirope]))

)
