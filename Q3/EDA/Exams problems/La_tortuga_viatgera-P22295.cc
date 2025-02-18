#include <iostream>
#include <vector>
using namespace std;


void cami(vector<vector<char>>& taulell, vector<vector<bool>>& visited)

void cami(vector<vector<char>>& taulell, pair <int, int>& ini, pair <int, int>& fin){
    vector<vector<bool>> visited (taulell.size(), vector<bool>(taulell[0].size(), false));
    vector<vector<pair<int,int>>> parents
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<char>> taulell (n, vector<char>(m));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j< m; ++j)
            cin >> taulell[i][j];
    pair <int, int> ini, fin;
    cin >> ini.first >> ini.second >> fin.first >> fin.second;
    cami(taulell, ini, fin);
    
}