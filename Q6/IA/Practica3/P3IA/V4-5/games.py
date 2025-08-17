from faker import Faker
from faker_food import FoodProvider
import random

fake = Faker()
fake.add_provider(FoodProvider)

class GestMenuProblemGenerator:
    def __init__(self):
        self.dias = ["lunes", "martes", "miercoles", "jueves", "viernes"]
        
    def generate_platos(self, num_primeros=10, num_segundos=10):
        """Genera platos aleatorios con nombres usando faker"""
        primeros = []
        segundos = []
        
        for _ in range(num_primeros):
            dish_name = fake.dish().lower().replace(" ", "-").replace("'", "")
            primeros.append(dish_name)
            
        for _ in range(num_segundos):
            dish_name = fake.dish().lower().replace(" ", "-").replace("'", "")
            segundos.append(dish_name)
            
        return primeros, segundos
    
    def generate_calorias(self, platos):
        """Genera calorías aleatorias para los platos"""
        calorias = {}
        for plato in platos:
            calorias[plato] = random.randint(200, 1200)
        return calorias
    
    def generate_precios(self, primeros, segundos):
        """Genera precios aleatorios para los platos"""
        precios = {}
        
        # Primeros: precios entre 2-4 euros
        for plato in primeros:
            precios[plato] = round(random.uniform(2.0, 4.0), 2)
            
        # Segundos: precios entre 4-25 euros
        for plato in segundos:
            precios[plato] = round(random.uniform(4.0, 25.0), 2)
            
        return precios
    
    def generate_incompatibilidades(self, primeros, segundos, num_incomp=5):
        """Genera incompatibilidades aleatorias entre primeros y segundos"""
        incompatibilidades = []
        for _ in range(num_incomp):
            primero = random.choice(primeros)
            segundo = random.choice(segundos)
            incompatibilidades.append((primero, segundo))

        return incompatibilidades
    
    def generate_mismo_tipo(self, platos, num_grupos=2):
        """Genera grupos de platos del mismo tipo"""
        mismo_tipo = []
        platos_copy = platos.copy()
        random.shuffle(platos_copy)
        
        for i in range(0, min(len(platos_copy), num_grupos * 2), 2):
            if i + 1 < len(platos_copy):
                mismo_tipo.append((platos_copy[i], platos_copy[i + 1]))
                
        return mismo_tipo
    
    def generate_goal_constraints(self, dias_laborables):
        """Genera restricciones del goal"""
        constraints = []
    
        min_cal = 1000
        max_cal = 1500
        
        for dia in dias_laborables:
            constraints.append(f"(>= (calorias-dia {dia}) {min_cal})")
            constraints.append(f"(<= (calorias-dia {dia}) {max_cal})")
            
        return constraints, min_cal, max_cal
    
    def generate_problem(self, problem_name="gestmenu-generated", num_dias=5, 
                        num_primeros=10, num_segundos=10, with_assignments=True):
        """Genera un problema completo"""
        
        # Seleccionar días laborables
        dias_laborables = self.dias[:num_dias]
        
        # Generar platos
        primeros, segundos = self.generate_platos(num_primeros, num_segundos)
        todos_platos = primeros + segundos
        
        # Generar propiedades
        calorias = self.generate_calorias(todos_platos)
        precios = self.generate_precios(primeros, segundos)
        incompatibilidades = self.generate_incompatibilidades(primeros, segundos)
        mismo_tipo_primeros = self.generate_mismo_tipo(primeros)
        mismo_tipo_segundos = self.generate_mismo_tipo(segundos)
        goal_constraints, min_cal, max_cal = self.generate_goal_constraints(dias_laborables)
        
        # Generar asignación forzada aleatoria
        dia_forzado = random.choice(dias_laborables)
        plato_forzado = random.choice(primeros)
        
        # Construir el problema PDDL
        problem_content = f"""(define (problem {problem_name})
  (:domain GestMenu)

  (:objects
    ;; días laborables
    {' '.join(dias_laborables)} - dia

    ;; {len(primeros)} primeros
    {chr(10).join([f'    {plato}' for plato in primeros])}                         - primero

    ;; {len(segundos)} segundos
    {chr(10).join([f'    {plato}' for plato in segundos])}                - segundo
  )

(:init

  ;; Calorias de los platos
{chr(10).join([f'  (=(calorias {plato}) {calorias[plato]})' for plato in todos_platos])}

  ;;Precio plato
  ;; precios de los primeros
{chr(10).join([f'(= (preu {plato}) {precios[plato]})' for plato in primeros])}

;; precios de los segundos
{chr(10).join([f'(= (preu {plato}) {precios[plato]})' for plato in segundos])}

  ;;Calorias del dia
{chr(10).join([f'    (= (calorias-dia {dia}) 0)' for dia in dias_laborables])}
    (= (preuTotal) 0)
  
  ;; incompatibilidades primero vs. segundo
{chr(10).join([f'  (incompatible {inc[0]} {inc[1]})' for inc in incompatibilidades])}

  ;; platos del mismo "giro" (para mismoTipo)
{chr(10).join([f'  (mismoTipo {mt[0]} {mt[1]})' for mt in mismo_tipo_primeros + mismo_tipo_segundos])}
  
  (diaInicial {dias_laborables[0]})

  ;; días consecutivos
{chr(10).join([f'  (diaConsecutivo {dias_laborables[i]} {dias_laborables[i+1]})' for i in range(len(dias_laborables)-1)])}
)


  (:goal
    (and
      ;; queremos un primero y un segundo para cada día
{chr(10).join([f'      (hayprimero {dia})   (haysegundo {dia})' for dia in dias_laborables])}
{chr(10).join([f'      (impres {dia})' for dia in dias_laborables])}
      {'(assignado-primero ' + dia_forzado + ' ' + plato_forzado + ')' if with_assignments else ''}
{chr(10).join([f'    {constraint}' for constraint in goal_constraints])}
    )
  )

  (:metric minimize (preuTotal))
)
"""
        
        return problem_content, {
            'dias': dias_laborables,
            'primeros': primeros,
            'segundos': segundos,
            'calorias_range': (min_cal, max_cal),
            'total_platos': len(todos_platos),
            'incompatibilidades': len(incompatibilidades)
        }

def main():
    generator = GestMenuProblemGenerator()
    
    # Generar diferentes tipos de problemas
    problems = [
        ("easy", 5, 25, 25),      # 5 días, 25 primeros, 25 segundos
        ("medium", 5, 20, 20),    # 5 días, 20 primeros, 20 segundos
        ("hard", 5, 15, 15),    # 5 días, 15 primeros, 15 segundos
    ]
    
    for difficulty, num_dias, num_primeros, num_segundos in problems:
        problem_content, info = generator.generate_problem(
            problem_name=f"gestmenu-{difficulty}",
            num_dias=num_dias,
            num_primeros=num_primeros,
            num_segundos=num_segundos
        )
        
        # Guardar archivo
        filename = f"gestmenu-{difficulty}.pddl"
        with open(filename, 'w', encoding='utf-8') as f:
            f.write(problem_content)
        
        print(f"Generado {filename}:")
        print(f"  - {info['total_platos']} platos total")
        print(f"  - {len(info['dias'])} días")
        print(f"  - Rango calorías: {info['calorias_range'][0]}-{info['calorias_range'][1]}")
        print(f"  - {info['incompatibilidades']} incompatibilidades")
        print()

if __name__ == "__main__":
    main()