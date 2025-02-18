#include <iostream>
#include <vector>
using namespace std;

void dfs(int act, vector<bool>& visitats, const vector<vector<int>>& adjecencia) {
    visitats[act] = true;
    for (auto i : adjecencia[act]) {
        if (not visitats[i]) 
            dfs(i, visitats, adjecencia);
    }
}

bool es_bosc(const vector<pair<int,int>>& arestes, int n, int m) {
    vector<bool> visitats (n, false);
    vector<vector<int>> adjecencia(n);
    int arbres = 0;
    for (int i = 0; i < arestes.size(); ++i) {
        int x = arestes[i].first;
        int y = arestes[i].second;
        adjecencia[x].push_back(y);
        adjecencia[y].push_back(x);
    }
    for (int act = 0; act < n; ++act) {
        if (not visitats[act]) {
            dfs(act, visitats, adjecencia);
            arbres++;
        }
    }
    return arbres == n - m;
}

int main (){
    int n, m;
    while (cin >> n >> m) {
        vector<pair<int,int>> arestes (m);
        for (int i = 0; i < m; ++i) cin >> arestes[i].first >> arestes[i].second;
        if (es_bosc(arestes, n, m)) cout << n - m << endl;
        else cout << "no" << endl;
    }
}
