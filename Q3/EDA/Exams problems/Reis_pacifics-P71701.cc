#include <iostream>
#include <vector>
using namespace std;

bool hi_ha_rei (vector<vector<char>>& sol_parcial, int files, int columnes) {
    for(int i = -1; i <= 1; ++i) {
        int aux_i = files + i;
        if (aux_i >= 0 and aux_i < sol_parcial.size()){
            for (int j = -1; j <= 1; ++j) {
                int aux_j = columnes + j;
                if (aux_j >= 0 and aux_j < sol_parcial.size()){
                    if (sol_parcial[aux_i][aux_j] == 'K') return true;
                }
            }
        }
    }
    return false;
}

void colocar_reis(int n, int r, int total, int files, int columnes, vector<vector<char>>& sol_parcial) {
    if (files == n) return;
    if (total == r) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << sol_parcial[i][j] << " ";
            }
            cout << endl;
        }
        cout << "----------" << endl;
    }
    else {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (not hi_ha_rei(sol_parcial, i, j)){
                sol_parcial[i][j] = 'K';
                colocar_reis(n, r, total+1, i + (j + 1)/n, (j + 1)%n, sol_parcial);
                sol_parcial[i][j] = '.';
                }
            }
        }

    }
}

void colocar_reis(int n, int r){
    vector<vector<char>> sol_parcial (n, vector<char>(n, '.'));
    int i = 0, j = 0, total = 0;
    colocar_reis(n, r, total, i, j, sol_parcial);
}

int main() {
    int n, r;
    cin >> n >> r;
    colocar_reis(n, r);
}