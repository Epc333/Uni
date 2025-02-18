#include <iostream>
#include <queue>
#include <vector>
#include <limits.h>
using namespace std;
using P = pair<int, int>;

const int inf = INT_MAX;

int dijsktra(const vector<vector<pair<int,int>>>& G, int x, int y){
    vector<int> dist (G.size(),inf);
    dist[x] = 0;
    priority_queue<P, vector<P>, greater<P>> Q;
    Q.push({0, x});
    while (not Q.empty()) {
        P f = Q.top();
        Q.pop();
        int u = f.second;
        int d = f.first;
        if (u == y) return dist[y];
        if (d == dist[u]) {
            for (auto p : G[u]) {
                int d2 = max(dist[u], p.second);
                if (d2 < dist[p.first]) {
                    dist[p.first] = d2;
                    Q.push({d2,p.first});
                }
            }
        }
    }
    return -1;
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        vector<vector<pair<int,int>>> G (n);
        while (m--) {
            int x, y, c;
            cin >> x >> y >> c;
            G[x].push_back({y, c});
        }
        cout << dijsktra(G, 0, 1) << endl;
    }
}