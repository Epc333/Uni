#include <iostream>
#include <vector>
#include <limits>
#include <queue>
using namespace std;

const int inf = numeric_limits<int>::max();
const vector<pair<int,int>> dir = {{1,0}, {-1,0}, {0, -1}, {0,1}};

bool ok_vei (const vector<vector<char>>& M, int i, int j) {
  return (i >= 0 and i < int(M.size()) and j >= 0 and j < int(M[0].size()) and M[i][j] != 'X');
}


int distanciaMax (vector<vector<char>>& M, int i, int j) {
    int distancia = -1;
    int seg_dist = -1;
    vector<vector<int>> dist (M.size(), vector<int>(M[0].size(),inf));
    dist[i][j] = 0;
    queue <pair<int, int>> Q;
    Q.push({i,j});
    while (not Q.empty()) {
        pair<int,int> top = Q.front();
        Q.pop();
        for (auto d : dir) {
            int v_i = top.first + d.first;
            int v_j = top.second + d.second;
            if (ok_vei(M, v_i, v_j)){
                if (dist[v_i][v_j] == inf) {
                    Q.push({v_i, v_j});
                    dist[v_i][v_j] = dist[top.first][top.second] + 1;
                    if (M[v_i][v_j] == 't') {
                        seg_dist = distancia;
                        distancia = dist[v_i][v_j];
                    }
                }
            }
        }
    }
    return seg_dist;
}

int main () {
    int n, m;
    cin >> n >> m;
    vector<vector<char>> M (n, vector<char> (m));
    for (int i = 0; i < n; ++i) 
        for (int j = 0; j < m; ++j)
            cin >> M[i][j];
    int x, y;
    cin >> x >> y;
    int distancia = distanciaMax(M, x-1, y-1);
    if (distancia == -1) cout << "no es pot arribar a dos o mes tresors" << endl;
    else cout << "segona distancia maxima: " << distancia << endl;
}

