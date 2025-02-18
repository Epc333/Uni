#include <iostream>
#include <vector>

using namespace std;

int calcularQuadrat(int fila, int columna) {
    int aux = 3*(fila / 3) + columna / 3;
    return aux;
}

void resol (const vector<vector<char>>& Sudoku, vector<vector<int>>& solparcial, int fila, int columna, vector<vector<bool>>& VisitatsFila, vector<vector<bool>>& VisitatsColumna, vector<vector<vector<bool>>>& VisitatsQuadrat){
    if (fila == 9) {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                cout << solparcial[i][j];
                if (j < 8) cout << " ";
            }
            cout << endl;
        }
        cout << endl;
        return;
    }
    else {
        for (int n = 1; n <= 9; ++n) {
            if ((Sudoku[fila][columna] == '.' or int(Sudoku[fila][columna]-'0') == n) and not VisitatsColumna[columna][n-1] and not VisitatsFila[fila][n-1] and not VisitatsQuadrat[fila/3][columna/3][n-1]){
                VisitatsColumna[columna][n-1] = VisitatsFila[fila][n-1] = VisitatsQuadrat[fila/3][columna/3][n-1] = true;
                solparcial[fila][columna] = n;
                resol(Sudoku, solparcial, fila + (columna+1)/9, (columna+1)%9, VisitatsFila, VisitatsColumna, VisitatsQuadrat);
                VisitatsColumna[columna][n-1] = VisitatsFila[fila][n-1] = VisitatsQuadrat[fila/3][columna/3][n-1] = false;
            }
        }

    }

}

void resol (const vector<vector<char>>& Sudoku, vector<vector<char>>& solparcial, int fila, int columna, vector<vector<bool>>& VisitatsFila, vector<vector<bool>>& VisitatsColumna, vector<vector<vector<bool>>>& VisitatsQuadrat){
    if (fila == 9) {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                cout << solparcial[i][j];
                if (j < 8) cout << " ";
            }
            cout << endl;
        }
        cout << endl;
        return;
    }
    else {
        for (int n = 1; n <= 9; ++n) {
            if ((Sudoku[fila][columna] == '.' or int(Sudoku[fila][columna]-'0') == n) and not VisitatsColumna[columna][n-1] and not VisitatsFila[fila][n-1] and not VisitatsQuadrat[fila/3][columna/3][n-1]){
                VisitatsColumna[columna][n-1] = VisitatsFila[fila][n-1] = VisitatsQuadrat[fila/3][columna/3][n-1] = true;
                solparcial[fila][columna] = char(n) + '0';
                resol(Sudoku, solparcial, fila + (columna+1)/9, (columna+1)%9, VisitatsFila, VisitatsColumna, VisitatsQuadrat);
                if(Sudoku[fila][columna] == '.')VisitatsColumna[columna][n-1] = VisitatsFila[fila][n-1] = VisitatsQuadrat[fila/3][columna/3][n-1] = false;
            }
        }

    }

}

void resol (vector<vector<char>>& Sudoku, vector<vector<char>>& solparcialchar, int fila, int columna, vector<vector<bool>>& VisitatsFila, vector<vector<bool>>& VisitatsColumna, vector<vector<bool>>& VisitatsQuadrat) {
    if (fila == 9) {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                cout << solparcialchar[i][j];
                if (j < 8) cout << " ";
            }
            cout << endl;
        }
        cout << endl;
        return;
    }
    else {
        cout << fila << endl;
        /*if (Sudoku[fila][columna] != '.') {
            int aux = int(Sudoku[fila][columna] - '0')-1;
            solparcialchar[fila][columna] = Sudoku[fila][columna];
            resol(Sudoku, solparcialchar, fila + (columna+1)/9, (columna+1)%9, VisitatsFila, VisitatsColumna, VisitatsQuadrat);
            //return;
            //VisitatsColumna[columna][aux] = VisitatsFila[fila][aux] = VisitatsQuadrat[calcularQuadrat(fila, columna)][aux] = false;
        }*/
        /*if (Sudoku[fila][columna] != '.') {
            int aux = int(Sudoku[fila][columna] - '0')-1;
            VisitatsColumna[columna][aux] = VisitatsFila[fila][aux] = VisitatsQuadrat[calcularQuadrat(fila, columna)][aux] = true;
            resol(Sudoku, fila + (columna+1)/9, (columna+1)%9, VisitatsFila, VisitatsColumna, VisitatsQuadrat);
        }*/
        //else {
            for (int n = 1; n <= 9; ++n) {
                if (Sudoku[fila][columna] == '.' and not VisitatsColumna[columna][n-1] and not VisitatsFila[fila][n-1] and not VisitatsQuadrat[calcularQuadrat(fila, columna)][n-1]){
                   VisitatsColumna[columna][n-1] = VisitatsFila[fila][n-1] = VisitatsQuadrat[calcularQuadrat(fila, columna)][n-1] = true;
                   //Sudoku[fila][columna] = char(n) + '0'; 
                   solparcialchar[fila][columna] = char(n) + '0';
                   resol(Sudoku, solparcialchar, fila + (columna+1)/9, (columna+1)%9, VisitatsFila, VisitatsColumna, VisitatsQuadrat);
                   VisitatsColumna[columna][n-1] = VisitatsFila[fila][n-1] = VisitatsQuadrat[calcularQuadrat(fila, columna)][n-1] = false;
                }
            }
        //}
    }
}

void resol (vector<vector<char>>& Sudoku) {
    vector<vector<int>> solparcial (9, vector<int>(9));
    vector<vector<char>> solparcialchar(9, vector<char>(9, '.'));
    int fila = 0;
    int columna = 0;
    vector<vector<bool>> VisitatsFila (9, vector<bool> (9, false));
    vector<vector<bool>> VisitatsColumna (9, vector<bool> (9, false));
    vector<vector<bool>> VisitatsQuadrat (9, vector<bool> (9, false));
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (Sudoku[i][j] != '.') {
                int aux = int(Sudoku[fila][columna] - '0')-1;
                VisitatsFila[i][aux] = VisitatsColumna[j][aux] = VisitatsQuadrat [calcularQuadrat(i,j)][aux] = true;
                solparcialchar[fila][columna] = Sudoku[fila][columna];
            }
        }
    }
    vector<vector<vector<bool>>> VisitatsQua(3, vector<vector<bool>>(3, vector<bool> (9, false)));
    resol(Sudoku, solparcialchar, fila, columna, VisitatsFila, VisitatsColumna, VisitatsQuadrat);

}

int main() {
    int n;
    cin >> n;
    cout << n << endl;
    for (int k = n; k > 0; --k) {
        vector<vector<char>> Sudoku (9, vector<char>(9));
        for (int i = 0; i < 9; ++i) 
            for (int j = 0; j < 9; ++j) 
                cin >> Sudoku[i][j];
        resol (Sudoku);
    }
}