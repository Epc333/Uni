#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

pair<int, int> resol(vector<vector<pair<int,int>>>& G, int x, int y){
    vector<int> d = vector<int>(G.size(), -1);
    vector<bool> visitats (G.size(), false);
    vector<int> parents (G.size(), -1);
    vector<int> steps (G.size(), 0);
    steps[x] = 0;
    d[x] = 0;
    priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int, int>>> Q;
    Q.push({0, x});
    while(not Q.empty()) {
        int u = Q.top().second;
        Q.pop();
        if (not visitats[u]) {
            visitats[u] = true;
            for (auto n : G[u]) {
                int v = n.first;
                int c = n.second;
                if ( d[v] == -1 or d[u] + c < d[v] or (d[v] == d[u]+c and steps[v] > steps[u]+1)){
                    d[v] = d[u] + c;
                    parents[v] = u;
                    steps[v] = steps[u] + 1;
                    Q.push({d[v], v});
                }
            }

        }
    }
    return {d[y],steps[y]};
}

int main () {
    int n, m;
    while (cin >> n >> m) {
        vector<vector<pair<int, int>>> G (n);
        for (int i = 0; i < m; ++i) {
            int u, v, c;
            cin >> u >> v >> c;
            G[u].push_back({v, c});
        }
        int x, y;
        cin >> x >> y;
        pair<int, int> sol = resol(G, x, y);
        if (sol.first == -1) cout << "no path from " << x << " to " << y << endl;
        else cout << "cost " << sol.first << ", " << sol.second << " step(s)" << endl;
    }
}