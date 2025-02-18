def max_parenthesization(nums, ops):
    n = len(nums)
    
    # Inicialitzem la taula de DP
    dp = [[0] * n for _ in range(n)]
    split = [[-1] * n for _ in range(n)]  # Per reconstruir la parentització
    
    # Cas base: només un nombre
    for i in range(n):
        dp[i][i] = nums[i]

    # Omplir la taula de DP
    for length in range(2, n + 1):  # Longitud de la subexpressió
        for i in range(n - length + 1):
            j = i + length - 1
            dp[i][j] = float('-inf')  # Inicialitzem amb el mínim valor possible
            
            for k in range(i, j):  # Punt de partició
                if ops[k] == '+':
                    value = dp[i][k] + dp[k + 1][j]
                elif ops[k] == '*':
                    value = dp[i][k] * dp[k + 1][j]
                
                if value > dp[i][j]:
                    dp[i][j] = value
                    split[i][j] = k  # Guardem el punt de partició

    return dp[0][n-1], reconstruct_parenthesis(nums, ops, split, 0, n - 1)

# Funció per reconstruir la parentització
def reconstruct_parenthesis(nums, ops, split, i, j):
    if i == j:
        return str(nums[i])
    k = split[i][j]
    left = reconstruct_parenthesis(nums, ops, split, i, k)
    right = reconstruct_parenthesis(nums, ops, split, k + 1, j)
    return f"({left} {ops[k]} {right})"

nums = [6, 3, 2, 5]
ops = ['*', '+', '*']