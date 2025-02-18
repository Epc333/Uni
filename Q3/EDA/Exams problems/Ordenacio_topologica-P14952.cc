#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;

void compute(const VVI& g, VI& indeg, VI& ord) {
    int n = g.size();
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int u = 0; u < n;++u) {
        if (indeg[u] == 0) pq.push(u);
    }
    ord = VI(n);
    int cnt = 0;
    while (not pq.empty()){
        int u = pq.top();
        pq.pop();
        ord[cnt] = u;
        ++cnt;
        for (int k = 0; k < g[u].size(); ++k) {
            int v = g[u][k];
            --indeg[v];
            if (indeg[v] == 0) pq.push(v);
        }
    }
}

void write (const VI& v) {
    cout << v[0];
    for (int k = 1; k < v.size(); ++k) {
        cout << " " << v[k];
    }
    cout << endl;
}

int main () {
    int n, m;
    while (cin >> n >> m) {
        VVI g(n);
        VI indg (n, 0);
        for (int k = 0; k < m; ++k) {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            ++indg[v];
        }
        VI ord;
        compute(g, indg, ord);
        write(ord);
    }
}