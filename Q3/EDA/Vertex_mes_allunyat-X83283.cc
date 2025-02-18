#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int mes_llunya (const vector<vector<int>>& graf) {
    vector<int> dist (graf.size(), -1);
    queue<int> Q;
    dist[0] = 0;
    Q.push(0);
    while (not Q.empty()) {
        int top = Q.front();
        Q.pop();
        for (int v : graf[top]) {
            if (dist[v] == -1) {
                dist[v] = dist[top] + 1;
                Q.push(v);
            }
        }
    }
    int result = 0;
    for (int v = 1; v < dist.size(); ++v)
        if (dist[v] != -1 and dist[v] > dist[result])
            result = v;
    return result;
}

int main (){
    int n;
    while (cin >> n) {
        int m;
        cin >> m;
        vector<vector<int>> graf (n);
        for (int i = 0; i < m; ++i) {
            int x, y;
            cin >> x >> y;
            graf[x].push_back(y);
            graf[y].push_back(x);
        }
        cout << mes_llunya(graf) << endl;
    }
}