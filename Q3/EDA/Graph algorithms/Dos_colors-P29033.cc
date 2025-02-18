#include <iostream>
#include <vector>
#include <stack>
#include <list>
using namespace std;



void DFS_rec ();

bool colorejable (vector<vector<int>>& arestes, int n) {
    vector <int> color (n, -1);
    stack <int> S;
    int color_act = 0;
    for (int u = 0; u < n; ++u) {
        S.push(u);
        while (not S.empty()) {
            int v = S.top();
            S.pop();
            if (color[v] == -1) {
                color[v] = color_act;
                if (color_act == 0) color_act = 1;
                else color_act = 0;
                for (auto w : arestes[v]) {
                    if (color[w] == -1) S.push(w);
                    else if (color[w] == color[v]) return false;
                }
            }
        }
    }
    return true;
}

int main () {
    int n, m;
    while (cin >> n >> m) {
        vector<vector<int>> arestes (n);
        for (int i = 0; i < m; ++i) {
            int x, y;
            cin >> x >> y;
            arestes[x].push_back(y);
            arestes[y].push_back(x);
        }
        if (colorejable(arestes, n)) cout << "yes" << endl;
        else cout << "no" << endl;
    }
}