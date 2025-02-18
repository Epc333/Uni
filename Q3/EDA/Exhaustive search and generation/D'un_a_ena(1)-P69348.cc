#include <iostream>
#include <vector>
using namespace std;

void escriure_sequencia(vector<int>& solparcial, vector<bool>& used, int it) {
    if (it == solparcial.size()) {
        cout << "(" << solparcial[0];
        for (int i = 1; i < solparcial.size(); ++i) cout << "," << solparcial[i];
        cout << ")" << endl;
    }
    for (int k = 1; k <= solparcial.size(); ++k) {
        if (not used[k-1]) {
            solparcial[it] = k;
            used[k-1] = true;
            escriure_sequencia(solparcial, used, it+1);
            used[k-1] = false;
        }
    }
}

void escriure_sequencia(int n) {
    vector <int> solparcial (n);
    vector <bool> used(n, false);
    escriure_sequencia(solparcial, used, 0);
}

int main () {
    int n;
    cin >> n;
    escriure_sequencia(n);
}