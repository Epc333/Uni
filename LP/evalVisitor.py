from schemeParser import schemeParser 
from schemeVisitor import schemeVisitor

class ReturnException(Exception):
    def __init__(self, value):
        self.value = value

class EvalVisitor(schemeVisitor):
    def __init__(self):
        self.ts = [{}] #Pila per gestionar variables locals en diferents scopes
        self.functions = {} #Diccionari per definir funcions (del usuari)
        self.globals = {} #Diccionari per definir variables globals, constants i funcions predefinides
        self.input_buffer = [] #Serveix per llegir input
        self.init_builtins()

    def visitRoot(self, ctx):
        '''
        Funcio per visitar el node root i avaluar el programa
        '''
        results = []
        for expr in ctx.expr():
            result = self.visit(expr)
            if result is not None:
                results.append(result)

        if 'main' in self.functions:
            main = self.functions['main']
            self.ts.append({})
            for i, arg in enumerate(results):
                self.ts[-1][main[0][i]] = arg
            for expr in main[1]:
                result = self.visit(expr)
            self.ts.pop()
            return result   
    
    def init_builtins(self):
        '''
        Funcio per inicialitzar les operacions simples
        '''
        # Operadors aritmètics 
        self.globals['+'] = '+'
        self.globals['-'] = '-'
        self.globals['*'] = '*'
        self.globals['/'] = '/'
        self.globals['mod'] = 'mod'

        # Operadors de comparació
        self.globals['='] = '='
        self.globals['>'] = '>'
        self.globals['<'] = '<'
        self.globals['>='] = '>='
        self.globals['<='] = '<='
        self.globals['<>'] = '<>'

        # Operdors de llistes
        self.globals['car'] = 'car'
        self.globals['cdr'] = 'cdr'
        self.globals['cons'] = 'cons'
        self.globals['null?'] = 'null?'

        # Entrada/sortida
        self.globals['newline'] = 'newline'
        self.globals['read'] = 'read'

        # Operadors booleans
        self.globals['and'] = 'and'
        self.globals['or'] = 'or'
        self.globals['not'] = 'not'

    def operar(self, operator, args):
        if operator == '+':
            return args[0] + args[1] if len(args) > 1 else args[0]
        elif operator == '-':
            return args[0] - sum(args[1:]) if len(args) > 1 else -args[0]
        elif operator == '*':
            result = 1
            for arg in args:
                result *= arg
            return result
        elif operator == '/':
            result = args[0]
            for arg in args[1:]:
                result /= arg
            return result
        elif operator == 'mod':
            return args[0] % args[1]
        elif operator == '=':
            return args[0] == args[1]
        elif operator == '>':
            return args[0] > args[1]
        elif operator == '<':
            return args[0] < args[1]
        elif operator == '>=':
            return args[0] >= args[1]
        elif operator == '<=':
            return args[0] <= args[1]
        elif operator == '<>':
            return args[0] != args[1]
        elif operator == 'car':
            return args[0][0]
        elif operator == 'cdr':
            return args[0][1:]
        elif operator == 'cons':
            return [args[0]] + args[1]
        elif operator == 'null?':
            return len(args[0]) == 0
        elif operator == 'newline':
            print()
            return None
        elif operator == 'read':
            return self.read()
        elif operator == 'and':
            return all(args)
        elif operator == 'or':
            return any(args)
        elif operator == 'not':
            return not args[0]
    
    def read(self):
        '''
        Funcio per llegir input
        '''
        if not self.input_buffer:
            usr_input = input() #Llegeix l'input
            if usr_input.startswith('\'('):  #Comprova si es una llista
                self.input_buffer = [usr_input]
            elif usr_input.startswith('"') or usr_input.startswith("'"):  #Comprova si es un string
                self.input_buffer = [usr_input]
            else:
                self.input_buffer = usr_input.split()

        text = self.input_buffer.pop(0)
        if text.startswith('\'('):
            return self.readList(text)
        elif text.startswith('"') or text.startswith("'"):
            return text[1:-1]
        elif text.isdigit():
            return float(text) if '.' in text else int(text)
            
        else:
            return text

    def visitChild(self, ctx):
        '''
        Funció per visitar els fills del node
        '''
        result = []
        for child in ctx.getChildren():
            if child.getChildCount() > 1:
                result.append(self.visitChild(child))
            else:
                result.append(child.getText())
        return ' '.join(result)

    def visitDisplay(self, ctx):
        '''
        Funció per mostrar el resultat d'una expressió
        '''
        children = list(ctx.getChildren())[2:-1]
        if not children:
            result = ''
        elif len(children) ==1:
            result = self.visit(children[0])
        else:
            concatenat =[]
            for child in children:
                concatenat.append(self.visitChild(child))
            concatenat = (' '.join(concatenat))
            if concatenat.startswith('"') or concatenat.startswith("'"):
                result = concatenat[1:-1]
            else:
                result = concatenat
            
        print(result, end=' ')
        return result

    def readList(self, text):
        '''
        Funcio per llegir llistes
        '''
        text = text.replace("'", "").replace("(", "").replace(")", "")
    
        # Separar els elements per les comes
        numeros = []
        for num in text.split(","):
            num = num.strip()
            if num.isdigit():
                if '.' in text:
                    return float(text)
                return int(text)
                
        return numeros
       
    def visitGlobals(self, ctx):
        '''
        Funcio per avaluar variables globals
        '''
        args = [self.visit(expr) for expr in ctx[1:]]
        return self.operar(self.visit(ctx[0]), args)

    def visitDefine(self, ctx):
        '''
        Funcio per definir variables i funcions
        Permet definir variables globals i funcions
        '''
        children = list(ctx.getChildren())
        func_args = list(children[2].getChildren())
        if len(func_args) == 1:  # Es tracta d'una variable
            nom = children[2].getText()
            valor = self.visit(children[3])
            self.globals[nom] = valor
        else:  # Es tracta d'una funció
            nom = func_args[1].getText()
            arguments = [arg.getText() for arg in func_args[2:-1]]  # Llista d'arguments
            cos = children[3:-1]  # Llista d'operacions
            self.functions[nom] = (arguments, cos)  # Afegim la funció al diccionari
        return None

    def visitEvaluarFuncionsStack(self, ctx, parametros):
        '''
        Funció per avaluar funcions amb arguments
        '''
        operator = self.visit(ctx.expr()[0])
        variables, body = self.functions[operator]
        local_env = {variables[i]: parametros[i] for i in range(len(variables))}
        self.ts.append(local_env)
        resultado = None
        for expr in body:
            resultado = self.visit(expr)
        self.ts.pop()
        return resultado

    def visitIf(self, ctx):
        '''
        Funcio per avaluar if
        Permet avaluar una condicio i retornar un valor depenent de si es certa o falsa
        '''
        cond = self.visit(ctx.expr()[1])
        return self.visit(ctx.expr()[2]) if cond else self.visit(ctx.expr()[3])

    def visitCond(self, ctx):
        '''
        Funcio per avaluar condicionals amb cond
        Permet avaluar multiples condicions i retornar el resultat de la primera que sigui certa
        '''
        exprs = ctx.expr()
        for condicions in exprs[1:]:
                condicio = condicions.expr()
                if condicio and self.visit(condicio[0]):
                    if len(condicio) > 1:
                        return self.visit(condicio[1])
                    return None
        return None 

    def visitLet(self, ctx):
        '''
        Funcio per avaluar let
        Permet definir variables locals i avaluar expressions amb aquestes
        '''

        child = list(ctx.getChildren())
        variables = list(child[2].getChildren())
        ts_local = {}
        for var in variables[1:-1]:
            p, v, valor, p = list(var.getChildren())
            ts_local[v.getText()] = self.visit(valor)
        self.ts.append(ts_local)

        for c in child[3:-1]:
            result = self.visit(c)
        self.ts.pop()
        return result
    
    def visitBegin(self, ctx):
        '''
        Funcio per avaluar begin
        Permet avaluar una sequencia d'operacions
        '''
        for expr in ctx.expr()[1:]:
            result = self.visit(expr)
        return result

    def visitEvaluarExpressions(self, ctx):
        '''
        Funció per avaluar les operacions amb parentesis (les expressions)
        Determina quin tipus d'operacio es i la realitza
        Es primordial pel funcionament del programa
        '''
        exprs = ctx.expr()
        operator = self.visit(exprs[0])

        if operator in self.globals:
            return self.visitGlobals(exprs)
        
        elif operator == 'define': #Permet definir variables i funcions
            return self.visitDefine(ctx)
        
        elif operator == 'display': #Permet mostrar el resultat d'una expressió
            return self.visitDisplay(ctx)

        elif operator == "begin":   #Permet fer una sequencia d'operacions
            return self.visitBegin(ctx)

        elif operator in (self.ts[-1] | self.functions): #Serveix per evaular variables locals i funcions
            if operator in self.ts[-1]:
                parametros = [self.visit(expr) for expr in exprs[2:]]
            else:
                parametros = [self.visit(expr) for expr in exprs[1:]]
            return self.visitEvaluarFuncionsStack(ctx, parametros)
                
        elif operator == 'if':
            return self.visitIf(ctx)

        elif operator == 'cond':
            return self.visitCond(ctx)
        
        elif operator == 'let':
            return self.visitLet(ctx)

        raise Exception(f"Operador no valid: {operator}")
            
    def visitDefinirLlistes(self, ctx):
        '''
        Funció per definir llistes
        Llegeix els elements d'una llista literal i els retorna
        '''
        return list(map(self.visit, ctx.expr()))
    
    def visitTrue(self, ctx):
        return True

    def visitFalse(self, ctx):
        return False

    def visitAtom(self, ctx):
        '''
        Avalua variables, constants o literals numerics
        Cerca variables en l'entorn local o constants globals
        '''
        text = ctx.getText()

        for env in reversed(self.ts):
            if text in env:
                return env[text]
        
        if text in self.globals:
            return self.globals[text]
        
        elif text in self.functions:
            return text
        
        if text.isdigit():
            if '.' in text:
                return float(text)
            return int(text)
            
        else:
            return text  # Variable