#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector <pair<int,int>> mov_cavall = {{2, 1}, {1, 2}, {-2, 1}, {-1, 2}, {2, -1}, {1, - 2}, {-2, -1}, {-1, -2}};


bool pos_ok (const vector<vector<char>>& camp, pair<int, int>& aux) {
    return 0 <= aux.first and aux.first < camp.size() and 0 <= aux.second and aux.second < camp[0].size(); 
}

int pasta (vector<vector<char>>& camp, pair<int, int>& ini) {
    vector<vector<int>> dist (camp.size(), vector<int>(camp[0].size(), -1));
    dist[ini.first][ini.second] = 0;
    queue<pair<int,int>> Q;
    Q.push(ini);
    camp[ini.first][ini.second] = 'X';
    while(not Q.empty()) {
        pair<int, int> Top = Q.front();
        Q.pop();
        for (auto d : mov_cavall) {
            pair<int, int> aux = {Top.first+d.first, Top.second+d.second};
            if (pos_ok(camp, aux) and camp[aux.first][aux.second] != 'X') {
                dist[aux.first][aux.second] = dist[Top.first][Top.second] + 1;
                if (camp[aux.first][aux.second] == 'p') return dist[aux.first][aux.second];
                camp[aux.first][aux.second] = 'X';
                Q.push(aux);
            }
        }
    }
    return -1;
}

int main () {
    int f, c;
    while (cin >> f >> c) {
        vector<vector<char>> camp (f, vector<char>(c));
        for (int i = 0; i < f; ++i) {
            for (int j = 0; j < c; ++j) {
                cin >> camp[i][j];
            }
        }
        pair<int,int> p_c;
        cin >> p_c.first >> p_c.second;
        p_c = {p_c.first-1, p_c.second-1};
        int pastanagues = pasta(camp, p_c);
        if (pastanagues == -1) cout << "no" << endl;
        else cout << pastanagues << endl;
    }
}