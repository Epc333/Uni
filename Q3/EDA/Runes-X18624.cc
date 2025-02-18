#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


bool es_vocal (char c) {
    return c == 'a' or c == 'e' or c == 'i' or c == 'o' or c == 'u';
}

void paraules(const vector<char>& lletres, vector<char>& solparcial, int idx) {
    if (idx == solparcial.size()) {
        for (char c : solparcial) cout <<c;
        cout << endl;
    } else {
        for (char c: lletres) {
            if (idx == 0 or not es_vocal(c) or not es_vocal(solparcial[idx - 1])){
                solparcial[idx] = c;
                paraules(lletres, solparcial, idx + 1);
            }
        }
    }
}

void paraules (const vector<char>& lletres, int n) {
    vector<char> solparcial(n);
    paraules (lletres, solparcial, 0);
}

int main () {
    int n;
    while (cin >> n) {
        int m;
        cin >> m;
        vector<char> lletres(m);
        for (int i = 0; i < m; ++i) cin >> lletres[i];
        sort(lletres.begin(), lletres.end());
        paraules (lletres, n);
        cout << "----------" << endl;
    }
}