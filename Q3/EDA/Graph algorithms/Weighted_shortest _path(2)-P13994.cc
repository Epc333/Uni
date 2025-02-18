#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii; // pair of (cost, vertex)

vector<int> resol(vector<vector<pair<int,int>>>& G, int x, int y){
    vector<int> d = vector<int>(G.size(), INT_MAX);
    vector<bool> visitats (G.size(), false);
    vector<int> parents (G.size(), -1);
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
                if (d[u] + c < d[v]) {
                    d[v] = d[u] + c;
                    parents[v] = u;
                    Q.push({d[v], v});
                }
            }

        }
    }
    int act = y;
    vector <int> cami;
    while (act != x) {
        if (act == -1) return vector<int>();
        cami.push_back(act);
        act = parents[act];
    }
    cami.push_back(x);
    reverse(cami.begin(), cami.end());
    return cami;
}

int main () {
    int n, m;
    while (cin >> n >> m) {
        vector<vector<pair<int,int>>> G (n);
        for (int i = 0; i < m; ++i) {
            int u, v, c;
            cin >> u >> v >> c;
            G[u].push_back({v, c});
        }
        int x, y;
        cin >> x >> y;
        vector<int> sol = resol(G, x, y);
        if (sol.empty()) cout << "no path from " << x << " to " << y << endl;
        else {
            for (int i = 0; i < sol.size(); ++i) {
                if (i > 0) cout << " ";
                cout << sol[i];
            }
            cout << endl;
        }
    }
}