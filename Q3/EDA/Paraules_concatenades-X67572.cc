#include <iostream>
#include <vector>
#include <string>
using namespace std;

void concatenar (const vector<string>& paraules, vector<bool>& used, vector<int>& solparcial, int idx) {
    if (idx == solparcial.size()) {
        for (int i :solparcial) cout <<paraules[i];
        cout <<endl;
    } else {
        for (int i = 0 ; i < paraules.size(); ++i) {
            if (not used[i]) {
                if (idx == 0 or paraules[solparcial[idx-1]][paraules[solparcial[idx-1]].length() - 1] != paraules[i][0]) {
                    used[i] = true;
                    solparcial[idx] = i;
                    concatenar(paraules, used, solparcial, idx+1);
                    used[i] = false;
                }
            }
        }
    }
}

void concatenar(const vector<string>& paraules) {
    vector<bool> used (paraules.size());
    vector<int> solparcial(used.size());
    concatenar(paraules, used, solparcial, 0);

}

int main() {
    int n;
    cin >> n;
    vector<string> paraules(n);
    for (int i = 0; i < n; ++i) {
        cin >> paraules[i];
    }
    concatenar(paraules);
}