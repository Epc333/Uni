#include <iostream>
#include <vector>
using namespace std;

const vector<pair<int,int>> dir = {{1,0}, {-1,0}, {0, -1}, {0,1}};

bool correcte (vector<vector<char>>&M, int i, int j){
    return i > 0 and i < M.size()-1 and j > 0 and j < M[0].size()-1 and M[i][j] == '.'; 
}

void pintar (vector<vector<char>>&M, int i, int j, const char a) {
    if (M[i][j] != '#'){
        M[i][j] = a;
        for (auto d : dir) {
            int v_i = i + d.first;
            int v_j = j + d.second;
            if (correcte(M, v_i, v_j))
                pintar(M, v_i, v_j, a);
        }
    }
    
}

void pintar (vector<vector<char>>& M) {
    int n = M.size();
    int m = M[0].size();
    for (int i = 1; i < n-1; ++i) {
        for (int j = 1; j < m-1; ++j) {
            if (M[i][j] != '#' and M[i][j] != '.') 
                pintar(M, i, j, M[i][j]);
        }
    }
}

int main () {
    int n, m;
    while (cin >> n >> m) {
        vector<vector<char>> M (n, vector<char>(m));
        for (int i = 0; i <n; ++i) 
            for (int j = 0; j < m; ++j)
                cin >> M[i][j];
        pintar (M);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) 
                cout << M[i][j];
            cout << endl;
        }
        cout << endl;
    }
}