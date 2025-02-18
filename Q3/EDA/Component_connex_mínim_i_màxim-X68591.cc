#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int comp_connex(const vector<vector<int>>& graf, vector<bool>& used, int v) {
    used[v] = true;
    int mida = 1; 
    queue <int> Q;
    Q.push(v);
    while (not Q.empty()) {
        int f = Q.front();
        Q.pop();
        for(int i = 0; i < graf[f].size(); ++i) {
            if (not used [graf[f][i]]) {
                used [graf[f][i]] = true;
                ++mida;
                Q.push(graf[f][i]);
            }
        }
    }
    return mida;
}

void comp_connex(const vector<vector<int>>& graf) {
    vector<bool> used (graf.size(), false);
    int min = -1, max = 0;
    for (int i = 0; i < used.size(); ++i) {
        if(not used[i]) {
            int mida = comp_connex(graf, used, i);
            if (min == -1 or mida < min) min = mida;
            if (mida > max) max = mida;
        }
    }
    cout << min << " " << max << endl;
}

int main () {
    int n, m;
    while (cin >> n >> m) {
        vector<vector<int>> graf (n);
        for (int i = 0 ; i < m; ++i) {
            int x, y;
            cin >> x >> y;
            graf[x].push_back(y);
            graf[y].push_back(x);
        }
        comp_connex(graf);
    }
}