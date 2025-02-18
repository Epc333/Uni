#include <iostream>
#include <vector>
#include <string>
using namespace std;

void escriure_sequencia(const vector<string>& paraules, vector<string> & solparcial, vector<bool>& usat, int idx) {
    if (idx == paraules.size()) {
        cout << "(" << solparcial[0];
        for (int i = 1; i < solparcial.size(); ++i) cout << "," << solparcial[i];
        cout << ")" << endl;
    } else {
        for (int i = 0; i < paraules.size(); ++i) {
            if (not usat[i]) {
                solparcial[idx] = paraules[i];
                usat[i] = true;
                escriure_sequencia(paraules, solparcial, usat, idx + 1);
                usat[i] = false;
            }
        }
    }
}

void escriure_sequencia(const vector <string>& paraules) {
    vector <bool> usat (paraules.size());
    vector <string> solparcial(paraules.size());
    escriure_sequencia(paraules, solparcial, usat, 0);
}

int main () {
    int n; 
    cin >> n;
    vector<string> paraules (n);
    for (int i = 0; i < n; ++i) cin >> paraules[i];
    escriure_sequencia(paraules);
}