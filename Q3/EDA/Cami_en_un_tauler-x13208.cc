#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<pair<int, int>> mov = {{1,0}, {-1,0}, {0, -1}, {0, 1}};

int cost (const vector<vector<int>>& taulell) {
    int n = taulell.size();
    vector<vector<bool>> used (n, vector<bool>(n, false));
    vector<vector<int>> dist (n, vector<int>(n, -1));
    pair<int, int> pos = {n/2, n/2};
    priority_queue<pair<int,pair<int, int>>, vector<pair<int,pair<int, int>>>, greater<pair<int, pair<int,int>>>> Q;
    dist[pos.first][pos.second] = taulell[pos.first][pos.second];
    Q.push({dist[pos.first][pos.second], pos});
    while (not Q.empty()) {
        pair<int, int> first = Q.top().second;
        Q.pop();
        if (not used[first.first][first.second]) {
            used[first.first][first.second] = true;
            if (first.first == 0 or first.first == n-1 or first.second == 0 or first.second == n-1) return dist[first.first][first.second];
            for (auto d : mov) {
                pair<int, int> vei = {first.first + d.first, first.second + d.second};
                if (dist[vei.first][vei.second] == -1 or (dist[first.first][first.second] + taulell[vei.first][vei.second] < dist[vei.first][vei.second])){
                    dist [vei.first][vei.second] = dist[first.first][first.second] + taulell[vei.first][vei.second];
                    Q.push({dist[vei.first][vei.second], vei});
                }
            }
        }
    }
    return -1;
}

int main() {
    int n;
    while (cin >> n) {
        vector<vector<int>> taulell(n, vector<int>(n));
        for (int i = 0; i < n; ++i) 
            for (int j = 0; j < n; ++j) 
                cin >> taulell[i][j];
        cout << cost(taulell) << endl;
    }
}
