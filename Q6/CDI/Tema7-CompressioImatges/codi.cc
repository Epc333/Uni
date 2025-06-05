// Per compilar:
// g++ codi.cc -o codi `pkg-config --cflags --libs opencv4`
// Ja que al fer servir OpenCv, cal compilar amb el pkg-config

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

vector<vector<double>> trasspossar_mat(const vector<vector<double>> &mat){
    vector<vector<double>> matT(mat[0].size(), vector<double>(mat.size()));
    for (int i = 0; i < mat.size(); ++i)
        for (int j = 0; j < mat[0].size(); ++j)
            matT[j][i] = mat[i][j];
    return matT;
}

vector<vector<double>> multiplicar_mat(const vector<vector<double>> &mat, const vector<vector<double>> &matT){
    vector<vector<double>> I(mat.size(), vector<double>(matT[0].size(), 0));
    for (int i = 0; i < mat.size(); ++i)
        for (int j = 0; j < matT[0].size(); ++j)
            for (int k = 0; k < mat[0].size(); ++k)
                I[i][j] += mat[i][k] * matT[k][j];
    return I;
}

vector<vector<double>> hadamard(int n){
    if (n == 1)
        return {{1.0}};
    auto H = hadamard(n / 2);
    vector<vector<double>> result(n, vector<double>(n));
    for (int i = 0; i < n / 2; i++)
        for (int j = 0; j < n / 2; j++){
            result[i][j] = H[i][j];
            result[i + n / 2][j] = H[i][j];
            result[i][j + n / 2] = H[i][j];
            result[i + n / 2][j + n / 2] = -H[i][j];
        }

    return result;
}

void ordenar_mat(vector<vector<double>> &mat){
    vector<int> canvi_signes(mat.size());
    for (int i = 0; i < mat.size(); ++i){
        int anterior = mat[i][0];
        int total = 0;
        for (int j = 0; j < mat[i].size(); ++j){
            if (mat[i][j] != anterior){
                total++;
                anterior = mat[i][j];
            }
        }
        canvi_signes[i] = total;
    }
    vector<vector<double>> mat_ordenada(mat.size(), vector<double>(mat[0].size()));
    for (int i = 0; i < canvi_signes.size(); ++i){
        int fila = canvi_signes[i];
        for (int j = 0; j < mat[i].size(); ++j)
            mat_ordenada[fila][j] = mat[i][j];
    }
    mat = mat_ordenada;
}

int16_t swap_int16(int16_t val)
{
    uint16_t uval = static_cast<uint16_t>(val);
    uval = (uval << 8) | (uval >> 8);
    return static_cast<int16_t>(uval);
}

void guardarImatge(string nom_arxiu, const vector<vector<double>> &bloc)
{
    ofstream pgmFile(nom_arxiu);
    pgmFile << "P2" << endl;  // Escala de grisos
    pgmFile << "8 8" << endl; // Dimensions
    pgmFile << "255" << endl; // ValorMaxim
    for (int i = 0; i < bloc.size(); ++i)
    {
        for (int j = 0; j < bloc[0].size(); ++j)
        {
            pgmFile << round(((bloc[i][j]) + 1.0) * 127.5) << " ";
        }
        pgmFile << "\n";
    }
    pgmFile.close();
}

void exercici1(){
    vector<vector<double>> mat = {
        {-0.1270001, -0.2550914, 0.5493215, -0.4813478, 0.0850042, -0.071017, -0.4616458, 0.3999545},
        {-0.1270001, -0.1151297, -0.1522096, -0.5383493, 0.3783183, 0.5792566, 0.4206871, -0.0445851},
        {0.0, 0.6998081, -0.2028987, -0.5729236, -0.3166449, -0.174709, -0.0935843, -0.0362488},
        {0.5080005, -0.2392892, -0.0895602, -0.2667215, 0.2378796, -0.6312755, 0.3784413, 0.0848615},
        {0.3810004, -0.2144573, -0.6428685, -0.0300152, -0.0375409, 0.2384993, -0.4738768, 0.3343882},
        {-0.3810004, 0.354419, -0.2088789, 0.2194794, 0.5716879, -0.2094654, 0.0162808, 0.5161942},
        {0.6350006, 0.435687, 0.4110656, 0.1677951, 0.150976, 0.3525249, 0.0784293, 0.237912},
        {-0.1270001, -0.1151297, -0.0019934, 0.0433029, -0.58461, 0.0731773, 0.4763972, 0.6282189}};
    vector<vector<double>> matT = trasspossar_mat(mat);
    vector<vector<double>> resultat = multiplicar_mat(mat, matT);

    for (const auto& fila : resultat) {
        for (const auto& element : fila)
            cout << element << " ";
        cout << endl;
    }
}

void exercici2()
{
    vector<vector<double>> mat = {
        {0.0, 0.0, 0.0, -0.61835, 0.63059, -0.2135, 0.41763, 0.0},
        {0.5, -0.45227, -0.08362, -0.52322, -0.29104, 0.2745, -0.1949, -0.2582},
        {0.0, 0.60302, -0.50175, -0.04757, 0.04851, 0.3355, 0.02784, -0.5164},
        {0.5, 0.15076, 0.3345, 0.23783, -0.24254, -0.1525, 0.64037, -0.2582},
        {0.0, 0.60302, 0.41812, -0.47565, -0.33955, -0.061, -0.22274, 0.2582},
        {0.5, 0.15076, -0.58537, 0.04757, -0.04851, -0.3355, -0.02784, 0.5164},
        {0.5, 0.15076, 0.3345, 0.23783, 0.58209, 0.2135, -0.41763, 0.0},
        {0.0, 0.0, 0.0, 0.0, 0.0, 0.76249, 0.38979, 0.5164}};
    int n = mat.size();
    for (int fila = 0; fila < n; ++fila)
        for (int columna = 0; columna < n; ++columna)
        {
            vector<vector<double>> bloc(n, vector<double>(n));
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    bloc[i][j] = mat[fila][i] * mat[columna][j];
                }
            }
            string nom_arxiu = to_string(fila) + "_" + to_string(columna) + ".pgm";
            guardarImatge(nom_arxiu, bloc);
        }
}

void exercici3()
{
    ifstream file("imatge", ios::binary);
    uint16_t n, m;
    uint8_t n_b, C;
    file.read(reinterpret_cast<char *>(&n), 2); // Llegim 2 bytes
    file.read(reinterpret_cast<char *>(&m), 2);
    file.read(reinterpret_cast<char *>(&n_b), 1); // Llegim 1 byte
    file.read(reinterpret_cast<char *>(&C), 1);
    n = (n >> 8) | (n << 8); // Conversió necessaria, ja que al llegir, estem llegint en ordre little-endian
    m = (m >> 8) | (m << 8);
    //cout << "n: " << n << ", m: " << m << ", n_b: " << (int)n_b << ", C: " << (int)C << endl;

    int num_blocs = (n * m) / n_b / n_b;
    int num_coeficients = C * (C + 1) / 2;

    vector<vector<int16_t>> blocs(num_blocs, vector<int16_t>(num_coeficients));
    for (int i = 0; i < num_blocs; ++i)
        for (int j = 0; j < num_coeficients; ++j){
            int16_t valor;
            file.read(reinterpret_cast<char *>(&valor), sizeof(valor));
            valor = swap_int16(valor);
            blocs[i][j] = valor;
        }

    auto H = hadamard(n_b);
    ordenar_mat(H); // Ordenar la matriu H en funció del nombre de canvis de signes
    for (int i = 0; i < H.size(); ++i)
        for (int j = 0; j < H[0].size(); ++j)
            H[i][j] /= sqrt(n_b);

    Mat img(n, m, CV_8U); // Imatge de sortida
    int idx_bloc = 0;
    for (int by = 0; by < n / n_b; ++by)
        for (int bx = 0; bx < m / n_b; ++bx)
        {
            // Construir Bq
            vector<vector<double>> Bq(n_b, vector<double>(n_b, 0.0));
            int idx = 0;
            for (int i = 0; i < n_b; ++i)
                for (int j = 0; j < n_b; ++j)
                    if (i + j < C)
                        Bq[i][j] = blocs[idx_bloc][idx++];

            // block = H * Bq * Ht
            auto temp = multiplicar_mat(H, Bq);
            auto Ht = trasspossar_mat(H);
            auto block = multiplicar_mat(temp, Ht);

            for (int i = 0; i < n_b; ++i)
                for (int j = 0; j < n_b; ++j){
                    int val = round(block[i][j] + 128.0);
                    val = max(0, min(255, val));
                    img.at<uchar>(by * n_b + i, bx * n_b + j) = static_cast<uchar>(val); // Assignar el valor a la imatge
                }

            ++idx_bloc;
        }
    imwrite("imatge.jpg", img);
}

void exercici4()
{
    int N = 8;
    vector<vector<int>> original ={
        {129, 121, 110, 96, 81, 66, 58, 53}, {126, 125, 119, 109, 96, 84, 70, 61}, {129, 125, 126, 119, 111, 112, 88, 80}, {126, 127, 127, 119, 118, 118, 107, 101}, {130, 127, 127, 127, 128, 125, 122, 118}, {128, 132, 129, 130, 129, 127, 130, 128}, {131, 128, 133, 131, 130, 133, 130, 128}, {127, 128, 130, 130, 126, 126, 128, 129}
    };

    vector<vector<int>> Q = {
        {16,11,10,16,24,40,51,61},
        {12,12,14,19,26,58,60,55},
        {14,13,16,24,40,57,69,56},
        {14,17,22,29,51,87,80,62},
        {18,22,37,56,68,109,103,77},
        {24,35,55,64,81,104,113,92},
        {49,64,78,87,103,121,120,101},
        {72,92,95,98,112,100,103,99}
    };

    vector<vector<double>> dct(8, vector<double>(8));

    for (int u = 0; u < N; u++) {
        for (int v = 0; v < N; v++) {
            double sum = 0.0;
            for (int x = 0; x < N; x++) {
                for (int y = 0; y < N; y++) {
                    sum += (original[x][y] - 128) * 
                        cos((2 * x + 1) * u * M_PI / 16.0) *
                        cos((2 * y + 1) * v * M_PI / 16.0);
                }
            }
            double aux, aux2;
            if (u == 0) aux = 1.0 / sqrt(2.0);
            else aux = 1.0;
            if (v == 0) aux2 = 1.0 / sqrt(2.0);
            else aux2 = 1.0;
            dct[u][v] = 0.25 * aux * aux2 * sum;
        }
    }

    vector<vector<int>> quantitzat(8, vector<int>(8));
    for (int u = 0; u < 8; u++) {
        for (int v = 0; v < 8; v++) {
            quantitzat[u][v] = round(dct[u][v] / Q[u][v]);
        }
    }

    vector<vector<double>> reconstruccio(8, vector<double>(8));
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++) {
            double sum = 0.0;
            for (int u = 0; u < N; u++) {
                for (int v = 0; v < N; v++) {
                    double cu, cv;
                    if (u == 0) cu = 1.0 / sqrt(2.0);
                    else cu = 1.0;
                    if (v == 0) cv = 1.0 / sqrt(2.0);
                    else cv = 1.0;
                    sum += cu * cv * quantitzat[u][v] * Q[u][v] *
                           cos((2 * x + 1) * u * M_PI / 16.0) *
                           cos((2 * y + 1) * v * M_PI / 16.0);
                }
            }
            reconstruccio[x][y] = round(0.25 * sum + 128);
        }
    }
    for (int i = 0; i < reconstruccio.size(); ++i){
        for (int j = 0; j < reconstruccio[0].size(); ++j)        {
            cout << reconstruccio[i][j] << " ";
        }
        cout << endl;
    }
}

int main(){
    //exercici1();
    //exercici2();
    //exercici3();
    exercici4();
}
