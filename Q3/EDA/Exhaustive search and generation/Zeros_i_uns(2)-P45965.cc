#include <iostream>
#include <vector>
using namespace std;

void escriure_tires (vector<int>& sol_parcial, int i, int k, int unsact, int zeros) {
    if (i == int(sol_parcial.size())) {
        for (int it = 0; it < i; ++it) {
            if (it == 0) cout << sol_parcial[it];
            else cout << " " << sol_parcial[it];
        }
        cout << endl;
    }
    else {
        if (zeros < sol_parcial.size()-k) {
        sol_parcial[i] = 0;
        escriure_tires(sol_parcial, i+1, k, unsact, zeros + 1);
        }
        if (unsact < k) {
        sol_parcial[i] = 1;
        escriure_tires(sol_parcial, i+1, k, unsact+1, zeros);
        }
    }
}

void escriure_tires(int n, int k){
    vector<int> solparcial (n);
    escriure_tires(solparcial, 0, k, 0, 0);
}

int main () {
    int n, k;
    cin >> n >> k;
    escriure_tires(n, k);
}