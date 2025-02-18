def myLength(L):
    if L == []:
        return 0
    else:
        return 1 + myLength(L[1:])
    
def myMaximum(L):
    if myLength(L) == 1:
        return L[0]
    else:
        max_rest = myMaximum(L[1:])
        return L[0] if L[0] > max_rest else max_rest
    
def average(L):
    total = 0
    for num in L:
        total += num
    return total / myLength(L)

def buildPalindrome(L):
    return L[::-1] + L
    
def remove(L1, L2):
    if L1 == []:
        return []
    elif L1[0] in L2:
        return remove(L1[1:], L2)
    else:
        return [L1[0]] + remove(L1[1:], L2)


def flatten(L):
    if L == []:
        return []
    elif isinstance(L[0], list):
        return flatten(L[0]) + flatten(L[1:])
    else:
        return [L[0]] + flatten(L[1:])

def oddsNevens(L):
    if L == []:
        return ([], [])
    elif L[0] % 2 == 0:
        odds, evens = oddsNevens(L[1:])
        return (odds, [L[0]] + evens)
    else:
        odds, evens = oddsNevens(L[1:])
        return ([L[0]] + odds, evens)
    
def primeDivisors(n):
    return [d for d in range(2, n+1) if n % d == 0 and isPrime(d)]

def isPrime(n):
    if n < 2:
        return False
    for d in range(2, n):
        if n % d == 0:
            return False
    return True

print( myLength([1,3,6,1]))
print( myMaximum([4,3,1,5,4,5,2]))
print(myMaximum(['josep', 'jordi', 'albert']))
print(average([1,2,3]))
print(buildPalindrome(['pa','amb','oli']))
print(flatten([[2,6],[[8,1,4],[3,'uau']],[[],[1]],[[]]]))
print(remove([1,4,5,3,4,5,1,2,7,4,2], [2,4]))
print(oddsNevens([1,4,5,3,4,5,1,2,7,4,2]))
print(primeDivisors(255))