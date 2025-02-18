#include <iostream>
#include <vector>
#include <list>
using namespace std;

bool dfs(const vector<pair<int,int>>& arestes, vector<int>& pintats, list<int>& L, int u, bool color){
    if (pintats[u] != -1) 
        return pintats[u] == color;
    
    pintats[u] = color;
    L.push_back(u);

    for (pair<int,int> v : arestes[u]) {
            if (not dfs(arestes, pintats, L, v.second, not color))
                return false;
    }
    return true;
}

bool colorejable (const vector<pair<int,int>>& arestes, int n) {
    vector <int> pintats (n, -1);
    list<int> L;

    for (int i = 0; i < n; ++i) {
        if (pintats[i] == -1 and not dfs(arestes, pintats, L, i, true)) 
            return false;
    }
    
    return true;

}

int main () {
    int n, m;
    while (cin >> n >> m) {
    vector<pair<int, int>> arestes(m);
    for (int i = 0; i < m; ++i) {
        cin >> arestes[i].first >> arestes[i].second;
    }
    if (colorejable(arestes, n))
        cout << "yes" << endl;
    else 
        cout << "no" << endl;
    }
}