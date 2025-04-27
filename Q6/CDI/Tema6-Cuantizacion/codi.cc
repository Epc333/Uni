#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream> //Per les imatges
#include <climits>
#include <cmath>
#include <cstdint> //Per unitX_t
using namespace std;

pair<pair<int, int>, vector<vector<int>>> cuantizarEscalarmente(vector<vector<int>>& bloque) {
    int Max = INT_MIN, Min = INT_MAX;
    for (const auto& fila : bloque) {
        for (int valor : fila) {
            Max = max(Max, valor);
            Min = min(Min, valor);
        }
    }
    double factor = (Max + 1.0 - Min) / 32;
    vector<vector<int>> m(bloque.size(), vector<int>(bloque[0].size()));
    for (int i = 0; i < bloque.size(); ++i) {
        for (int j = 0; j < bloque[i].size(); ++j) {
            double valor = bloque[i][j] - Min;
            int valorInt = int(valor / factor);
            m[i][j] = valorInt;
        }
    }
    return {{Min, Max}, m};
}

void exercici1() {
    vector<vector<int>> bloque = {
        {102, 108, 112, 111, 109, 101, 91, 88}, 
        {108, 119, 119, 109, 94, 74, 75, 83}, 
        {113, 120, 121, 111, 86, 66, 77, 89},
        {110, 117, 113, 104, 81, 70, 78, 90}, 
        {102, 109, 106, 93, 77, 78, 82, 94}, 
        {102, 89, 91, 85, 82, 83, 80, 90}, 
        {104, 81, 76, 88, 89, 89, 81, 77}, 
        {112, 101, 101, 102, 97, 91, 81, 71}
    };
    
    auto resultat = cuantizarEscalarmente(bloque);
    cout << "[[" << resultat.first.first << ", " << resultat.first.second << "], [";
    for (int i = 0; i < resultat.second.size(); ++i) {
        cout << "[";
        for (int j = 0; j < resultat.second[i].size(); ++j) {
            cout << resultat.second[i][j];
            if (j != resultat.second[i].size() - 1) cout << " ";
        }
        cout << "]";
        if (i != resultat.second.size() - 1) cout << ", ";
    }
    cout << "]]" << endl;
}

void exercici2(){
    int n = 7168, m = 5120, n_b = 16, nivells = 256, n_c = 8, bitsMin = 8, bitsMax = 8, bitsNivell, pixelesPerBloc, bitsNivellPerBloc, total;
    bitsNivell = log2(n_c);
    pixelesPerBloc = n_b * n_b;
    bitsNivellPerBloc = bitsNivell * pixelesPerBloc;
    total = bitsNivellPerBloc + bitsMin + bitsMax;
    double resposta1 = double(total) / pixelesPerBloc;

    int entrades_diccionari = 2048, numeroBlocs = (n*m) / n_b / n_b, bitsIndex, bitsTotIndex, bitsEntrada, bitsDiccionari;
    bitsIndex = ceil(log2(entrades_diccionari));
    bitsTotIndex = bitsIndex * numeroBlocs;
    bitsEntrada = pixelesPerBloc * 8;
    bitsDiccionari = entrades_diccionari * bitsEntrada;

    int bitsTotals = bitsTotIndex + bitsDiccionari, pixels = n * m;
    double resposta2 = double(bitsTotals) / pixels;

    cout << "Resposta pregunta 1: " << resposta1 << endl;
    cout << "Resposta pregunta 2: " << resposta2 << endl;


}

void printImatge(vector<vector<uint8_t>> imatge, uint16_t m, uint16_t n) {
    ofstream pgmFile("imatgeDecodificada.pgm", ios::binary);
    
    // Capçalera PGM
    pgmFile << "P5" << endl;             // Format binar
    pgmFile << m << " " << n << endl;    // Amplada i alçada
    pgmFile << "255" << endl;            // Valor màxim
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            unsigned char pixel = static_cast<unsigned char>(
                max(0, min(255, static_cast<int>(imatge[i][j])))
            );
            pgmFile.write(reinterpret_cast<char*>(&pixel), 1);
        }
    }
    pgmFile.close();
}

void exercici3_4() {
    ifstream file("imatge", ios::binary);
    uint16_t n, m;
    uint8_t n_b, b;
    file.read(reinterpret_cast<char*>(&n), 2); // Llegim 2 bytes
    file.read(reinterpret_cast<char*>(&m), 2);
    file.read(reinterpret_cast<char*>(&n_b), 1); // Llegim 1 byte
    file.read(reinterpret_cast<char*>(&b), 1);
    n = (n >> 8) | (n << 8); // Conversió necessaria, ja que al llegir, estem llegint en ordre little-endian
    m = (m >> 8) | (m << 8);
    
    vector<vector<uint8_t>> imagenReconstruida(n, vector<uint8_t>(m));

    for (int x = 0; x <  n / n_b; ++x) {
        for (int y = 0; y <  m / n_b; ++y) {
            uint8_t min, max;
            file.read(reinterpret_cast<char*>(&min), 1);
            file.read(reinterpret_cast<char*>(&max), 1);
            double factor = (max + 1.0 - min) / (1 << b); // 2^b 

            vector<vector<uint8_t>> bloc(n_b, vector<uint8_t>(n_b));
            int bitsPerProcessar = 0;
            uint8_t byteActual = 0;
            for (int i = 0; i < n_b; i++) {
                for (int j = 0; j < n_b; j++) {
                    uint8_t nivell = 0;
                    
                    for (int bit = 0; bit < b; bit++) {
                        if (bitsPerProcessar == 0) { //LLegir byte, no queden bits per processar
                            file.read(reinterpret_cast<char*>(&byteActual), 1);
                            bitsPerProcessar = 8;
                        }

                        nivell <<= 1; 
                        nivell |= ((byteActual & 0x80) >> 7);  //Agafem el bit més significatiu
                        byteActual <<= 1;
                        --bitsPerProcessar;
                    }
                    bloc[i][j] = nivell;
                    double valor = min + factor * nivell + factor/2; // factor/2 per centrar al interval
                    int posX = x * n_b + i;
                    int posY = y * n_b + j;
                    imagenReconstruida[posX][posY] = static_cast<uint8_t>(round(valor));
                }
            }
        }
    }
    printImatge(imagenReconstruida, m, n);
}

void exercici5_6() {
    ifstream file("imatge", ios::binary);
    uint16_t n, m, e_diccionario;
    uint8_t n_b;
    file.read(reinterpret_cast<char*>(&n), 2); // Llegim 2 bytes
    file.read(reinterpret_cast<char*>(&m), 2);
    file.read(reinterpret_cast<char*>(&n_b), 1); // Llegim 1 byte
    file.read(reinterpret_cast<char*>(&e_diccionario), 2);

    n = (n >> 8) | (n << 8); // Conversió necessaria, ja que al llegir, estem llegint en ordre little-endian
    m = (m >> 8) | (m << 8);
    e_diccionario = (e_diccionario >> 8) | (e_diccionario << 8);

    vector<vector<vector<uint8_t>>> diccionari (e_diccionario, vector<vector<uint8_t>>(n_b, vector<uint8_t>(n_b)));
    for (int entrada = 0; entrada < e_diccionario; ++entrada)  // Per cada entrada del diccionari llegim el bloc
        for(int i = 0; i < n_b; ++i) 
            for (int j = 0; j < n_b; ++j) {
                uint8_t valor;
                file.read(reinterpret_cast<char*>(&valor), 1);
                diccionari[entrada][i][j] = valor;
            }
    
    int bitsPorIndice = ceil(log2(e_diccionario)); 
    vector<vector<uint16_t>> indexs (n / n_b, vector<uint16_t>(m / n_b));

    int bitsPerProcessar = 0;
    uint8_t byteActual = 0;
    for (int x = 0; x < n / n_b; ++x)
            for(int y = 0; y < m / n_b; ++y) {
                uint16_t index = 0;
                for (int bit = 0; bit < bitsPorIndice; bit++) {
                    if (bitsPerProcessar == 0) { //LLegir byte, no queden bits per processar
                        file.read(reinterpret_cast<char*>(&byteActual), 1);
                        bitsPerProcessar = 8;
                    }
                    index <<= 1; 
                    index |= ((byteActual & 0x80) >> 7);  //Agafem el bit més significatiu
                    byteActual <<= 1;
                    --bitsPerProcessar;
                }
                indexs[x][y] = index;
            }
    
    vector<vector<uint8_t>> imatgeDecodificada(n, vector<uint8_t>(m));
    for (int x = 0; x < n / n_b; ++x)
        for (int y = 0; y < m / n_b; ++y) {
            uint16_t index = indexs[x][y];
            for (int i = 0; i < n_b; ++i)  //Copiar el bloc
                for (int j = 0; j < n_b; ++j) {
                    int posX = x * n_b + i;
                    int posY = y * n_b + j;
                    imatgeDecodificada[posX][posY] = diccionari[index][i][j];
                }
            
        }
    printImatge(imatgeDecodificada, m, n);
}

int main(){
    //exercici1();
    //exercici2();
    //exercici3_4();
    exercici5_6();
}

