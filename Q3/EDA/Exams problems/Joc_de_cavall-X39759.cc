#include <iostream>
#include <vector>
#include <limits>
#include <queue>
using namespace std;

const int MAX = numeric_limits<int>::max();

vector <pair<int,int>> mov_cavall = {{2, 1}, {1, 2}, {-2, 1}, {-1, 2}, {2, -1}, {1, - 2}, {-2, -1}, {-1, -2}};

bool pos_ok (const vector<vector<int>>& camp, pair<int, int>& aux) {
    return 0 <= aux.first and aux.first < camp.size() and 0 <= aux.second and aux.second < camp[0].size(); 
}
 /*
void calc_cost(int n, int m, int W, int L,  vector<pair<int,int>>& pos_final) {
    vector<vector<int>> punts (n, vector<int>(m, MAX));
    pair<int, int> pos_c = {0, 0};
    punts[0][0] = 0;
    int idx = 0;
    while ( pos_c == pos_final[idx]) {
        ++idx;
        punts[0][0] += W;
    }
    int punts_final = punts[0][0];
    int max = punts_final;
    queue <pair<int, int>> Q;
    Q.push({0,0});
    while (not Q.empty() and idx < pos_final.size()) {
        pair<int, int> front = Q.front();
        Q.pop();
        bool acabar = false;
        for (int i = 0; i < mov_cavall.size() and not acabar; ++i) {
            pair<int, int> d = mov_cavall[i];
            pair<int, int> aux = {front.first + d.first, front.second + d.second};
            if (pos_ok(punts, aux) and punts[aux.first][aux.second] == MAX) {
                punts[aux.first][aux.second] = punts[front.first][front.second] - L;
                Q.push(aux);
                if (aux == pos_final[idx]) {
                    while (aux == pos_final[idx]) {
                        punts[aux.first][aux.second] +=  W;
                        ++idx;
                    }
                    punts_final = punts[aux.first][aux.second];
                    punts = vector<vector<int>> (n, vector<int>(m, MAX));
                    punts[aux.first][aux.second] = punts_final;
                    while (not Q.empty()) Q.pop();
                    Q.push(aux);
                    acabar = true;
                }
                if (max < punts[aux.first][aux.second]) max = punts[aux.first][aux.second];
            }
        }
    }
    cout << max << endl;
}*/

int bfs (int n, int m, const pair <int, int>& ini, const pair<int,int>& fi) {
    vector<vector<int>> dist(n, vector<int>(m, MAX));
    dist[ini.first][ini.second] = 0;
    queue<pair<int,int>> Q;
    Q.push(ini);
    while (not Q.empty()) {
        pair<int, int> front = Q.front();
        Q.pop();
        if (front == fi) return dist[front.first][front.second];
        for (auto d: mov_cavall) {
            pair<int, int> aux = {front.first+d.first, front.second + d.second};
            if (pos_ok(dist, aux) and dist[aux.first][aux.second] == MAX) {
                dist[aux.first][aux.second] = dist[front.first][front.second] + 1;
                Q.push(aux);
            }
        }
    }
    return -1;
}

int main () {
    int n, m;
    while (cin >> n >> m) {
        int W, L, pos;
        cin >> W >> L >> pos;
        vector<pair<int,int>> pos_final (pos+1);
        pos_final[0] = {0,0};
        for (int i = 1; i <= pos; ++i) {
            pair<int,int> aux;
            cin >> aux.first >> aux.second;
            pos_final[i] = aux;
        }

        int punts = 0, top_punts = 0;
        bool acabar = false;

        for (int i = 0; i < pos_final.size()-1 and not acabar; ++i) {
            int dist = bfs(n, m, pos_final[i], pos_final[i+1]);
            if (dist == -1) acabar = true;
            else {
                punts += W;
                punts -= L*dist;
                if (punts > top_punts) top_punts = punts;
            }
        }
        cout << top_punts << endl;
    }
}