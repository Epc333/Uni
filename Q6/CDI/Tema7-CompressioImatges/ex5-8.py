

diccionari_ac = {
    '00': (0, 1), '01': (0, 2), '100': (0, 3), '1011': (0, 4),
    '1100': (1, 1), '11011': (1, 2), '1111001': (1, 3), '111110110': (1, 4),
    '11100': (2, 1), '11111001': (2, 2), '1111110111': (2, 3), '111111110100': (2, 4),
    '111010': (3, 1), '111110111': (3, 2), '111111110101': (3, 3), '1111111110001111': (3, 4),
    '111011': (4, 1), '1111111000': (4, 2), '1111111110010110': (4, 3), '1111111110010111': (4, 4),
    '1111010': (5, 1), '11111110111': (5, 2), '1111111110011110': (5, 3), '1111111110011111': (5, 4),
    '1111011': (6, 1), '111111110110': (6, 2), '1111111110100110': (6, 3), '1111111110100111': (6, 4),
    '11111010': (7, 1), '111111110111': (7, 2), '1111111110101110': (7, 3), '1111111110101111': (7, 4),
    '111111000': (8, 1), '111111111000000': (8, 2), '1111111110110110': (8, 3), '1111111110110111': (8, 4),
    '111111001': (9, 1), '1111111110111110': (9, 2), '1111111110111111': (9, 3), '1111111111000000': (9, 4),
    '111111010': (10, 1), '1111111111000111': (10, 2), '1111111111001000': (10, 3), '1111111111001001': (10, 4),
    '1111111001': (11, 1), '1111111111010000': (11, 2), '1111111111010001': (11, 3), '1111111111010010': (11, 4),
    '1111111010': (12, 1), '1111111111011001': (12, 2), '1111111111011010': (12, 3), '1111111111011011': (12, 4),
    '11111111000': (13, 1), '1111111111100010': (13, 2), '1111111111100011': (13, 3), '1111111111100100': (13, 4),
    '1111111111101011': (14, 1), '1111111111101100': (14, 2), '1111111111101101': (14, 3), '1111111111101110': (14, 4),
    '1111111111110101': (15, 1), '1111111111110110': (15, 2), '1111111111110111': (15, 3), '1111111111111000': (15, 4),
    '11111111001': (16, 1)
}

diccionari_dc ={
    '0' : -1,'1' : 1,
    '00' : -3,'01' : 2, '10': 2, '11': 3,
    '000' : -7, '001' : -6, '010' : -5, '011' : -4, '100' : 4, '101' : 5, '110' : 6, '111' : 7,
    '0000' : -15, '0001' : -14, '0010' : -13, '0011' : -12, '0100' : -11, '0101' : -10, '0110' : -9, '0111' : -8, 
    '1000' : 8, '1001' : 9, '1010' : 10, '1011' : 11, '1100' : 12, '1101' : 13, '1110' : 14,    '1111' : 15

}

def build_diccionari_dc(max_k):
    dic = {}
    dic[""] = 0
    for k in range(1, max_k+1):
        for i in range(1 << k):
            bits = format(i, f'0{k}b')
            if bits[0] == "1":
                val = i
            else:
                val = i - (1 << k) + 1
            dic[bits] = val
    return dic

diccionari_dc = build_diccionari_dc(10)

def exercici5(): #No gestiono bé que hi hagi mes de 15 zeros seguits
    coefs = [-6, 0, 6, 0, 0, 0, 1, -6, 0, 0, 0, 0, 0, 0, 0, 0, 2] 
    reversed_diccionari_ac = {v: k for k, v in diccionari_ac.items()}
    reversed_diccionari_dc = {v: k for k, v in diccionari_dc.items()}
    bits = ''
    zeros = 0
    for coef in coefs:
        if coef == 0:
            zeros += 1
        else:
            C = reversed_diccionari_dc[coef]
            R = len(C)
            cod = reversed_diccionari_ac[(zeros, R)]
            bits += cod
            bits += C
            zeros = 0

    if zeros > 0:
        C = reversed_diccionari_dc[0]
        R = len(C)
        cod = reversed_diccionari_ac[(zeros, R)]
        bits += cod
        bits += C
    bits += '1010'
    return bits

def exercici6(bits):
    coefs = []
    entrada_actual = ''
    while bits:
        # Leer el siguiente bit
        entrada_actual += bits[0]
        bits = bits[1:]
        if entrada_actual in diccionari_ac:
            [z, R] = diccionari_ac[entrada_actual]
            entrada_dc = bits[:R]
            bits = bits[R:]
            for i in range(z):
                coefs.append(0)
            coefs.append(diccionari_dc[entrada_dc])
            entrada_actual = ''

    return coefs

def exercici7():
    valors = [417, 264, 263, 399, 357, 253, 253, 351, 475, 450, 329, 295, 426, 352, 424, 259, 435, 464, 435, 336, 445, 283, 427, 401, 269, 408, 434, 242, 279, 242, 326, 282, 486, 353, 477, 467, 379, 289]
    codificat = ''
    dif = [valors[i] - valors[i-1] for i in range(1, len(valors))]
    dif = [valors[0]] + dif
    reversed_diccionari_dc = {v: k for k, v in diccionari_dc.items()}
    for d in dif:
        C = reversed_diccionari_dc[d]
        R = '1' * len(C) + '0'
        codificat += R + C

    return codificat

def exercici8():
    bits = "11111111101001110011111111100101110011111111010111110111111100101010111111101010111111111110010010000111111110101000111111101011011111110010010011111110000110111110011011111111010110010111111100101111111111110100101011111110001111111111110010110011111111101100101111111110010100011111111001111100111111101111111111111000011011111111010001000111111100000000111111001110011111010110111111101110011111111110010010011111110101111111111110100011011111110110001111111100111110"
    fila = 0
    coef = []
    while bits:
        while bits[0] == '1':
            fila += 1
            bits = bits[1:]
        bits = bits[1:]
        C = bits[:fila]
        bits = bits[fila:]
        coef.append(diccionari_dc[C])
        fila = 0

    reconstruir_coef = []
    for i in range(len(coef)):
        if i == 0:
            reconstruir_coef.append(coef[0])
        else:
            reconstruir_coef.append(reconstruir_coef[-1] + coef[i])

    return sum(reconstruir_coef) % 256


        


print(exercici5())
print(exercici6('1000111011100001101111111110010111011101011011011011111011100010111111111100111101111010'))
print(exercici7())
print(exercici8())