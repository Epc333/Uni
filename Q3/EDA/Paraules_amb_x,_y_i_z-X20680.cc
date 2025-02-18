#include <iostream>
#include <vector>
using namespace std;

vector<char> lletres = {'x', 'y', 'z'};

void escriure_lletres(vector<char>& solparcial, pair<char, int>& anterior, int c, int idx) {
    if (idx == solparcial.size()) {
        for (char c : solparcial){
            cout << c;
        }
        cout << endl;
    } else{
        for (int i = 0; i < 3; ++i) {
            if (lletres[i] == anterior.first and anterior.second < c) {
                ++anterior.second;
                solparcial[idx] = lletres[i];
                escriure_lletres (solparcial, anterior, c, idx + 1);
                --anterior.second;
            } else if (lletres[i] != anterior.first){
                pair<char, int> aux = anterior;
                anterior = {lletres[i], 1};
                solparcial[idx] = lletres[i];
                escriure_lletres (solparcial, anterior, c, idx + 1);
                anterior = aux;
            }
        }
    }
}

void escriure_lletres (int n, int c) {
    vector<char> solparcial (n);
    vector<int> used(3, c);
    pair <char, int> vegades = {'t', 0}; 
    escriure_lletres(solparcial, vegades, c, 0);

}

int main () {
    int n;
    while (cin >> n){
        int c;
        cin >> c;
        escriure_lletres(n, c);
        cout << "--------------------" << endl;
    }
}