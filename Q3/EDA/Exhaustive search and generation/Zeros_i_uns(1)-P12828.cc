#include <iostream>
#include <vector>
using namespace std;

void escriure_tires (vector<int>& sol_parcial, int i) {
    if (i == int(sol_parcial.size())) {
        for (int it = 0; it < i; ++it) {
            if (it == 0) cout << sol_parcial[it];
            else cout << " " << sol_parcial[it];
        }
        cout << endl;
    }
    else {
        sol_parcial[i] = 0;
        escriure_tires(sol_parcial, i+1);
        sol_parcial[i] = 1;
        escriure_tires(sol_parcial, i+1);
    }
}

void zeros_i_uns(int n){
    vector<int> solparcial (n);
    escriure_tires(solparcial, 0);
}

int main () {
    int n;
    cin >> n;
    zeros_i_uns(n);
}