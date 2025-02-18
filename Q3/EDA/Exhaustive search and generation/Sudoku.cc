#include <iostream>
#include <vector>

using namespace std;

int calcularQuadrat(int fila, int columna) {
    int aux = 3*(fila / 3) + columna / 3;
    return aux;
}

void resol (vector<vector<int>>& Sudoku, vector<vector<bool>>& VisitatsFila, vector<vector<bool>>& VisitatsColumna, vector<vector<bool>>& VisitatsQuadrat, int fila, int columna){
    if (fila == 9) {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                cout << Sudoku[i][j];
                if (j < 8) cout << " ";
            }
            cout << endl;
        }
        cout << endl;
        return;
    }
    else {
        if (Sudoku[fila][columna] != 0 and not VisitatsFila[fila][Sudoku[fila][columna]-1] and not VisitatsColumna[columna][Sudoku[fila][columna]-1] and not VisitatsQuadrat[calcularQuadrat(fila, columna)][Sudoku[fila][columna]-1]){
            int aux = Sudoku[fila][columna] - 1;
            VisitatsFila[fila][aux] = VisitatsColumna[columna][aux] = VisitatsQuadrat[calcularQuadrat(fila, columna)][aux] = true;
            resol(Sudoku, VisitatsFila, VisitatsColumna, VisitatsQuadrat, fila + (columna+1)/9, (columna+1)%9);
        }
        else {
            for (int n = 1; n <= 9; ++n) {
                if (not VisitatsFila[fila][n-1] and not VisitatsColumna[columna][n-1] and not VisitatsQuadrat[calcularQuadrat(fila, columna)][n-1]) {
                    VisitatsFila[fila][n-1] = VisitatsColumna[columna][n-1] = VisitatsQuadrat[calcularQuadrat(fila, columna)][n-1] = true;
                    Sudoku[fila][columna] = n;
                    resol(Sudoku, VisitatsFila, VisitatsColumna, VisitatsQuadrat, fila + (columna+1)/9, (columna+1)%9);
                    VisitatsFila[fila][n-1] = VisitatsColumna[columna][n-1] = VisitatsQuadrat[calcularQuadrat(fila, columna)][n-1] = false;
                    Sudoku[fila][columna] = 0;
                }
            }
        }
    }
}

void resol (vector<vector<int>>& Sudoku) {
    vector<vector<bool>> VisitatsFila (9, vector<bool>(9, false));
    vector<vector<bool>> VisitatsColumna (9, vector<bool>(9, false));
    vector<vector<bool>> VisitatsQuadrat (9, vector<bool>(9, false));
    resol (Sudoku, VisitatsFila, VisitatsColumna, VisitatsQuadrat, 0, 0);

}

int main() {
    int n;
    cin >> n;
    cout << n << endl;
    for (int k = n; k > 0; --k) {
        vector<vector<int>> Sudoku (9, vector<int>(9));
       for (int i = 0; i < 9; ++i) 
            for (int j = 0; j < 9; ++j) {
                char c;
                cin >> c;
                if (c == '.') Sudoku[i][j] = 0;
                else Sudoku[i][j] = c - '0';  // Corrected line
            }

        resol (Sudoku);
    }
}