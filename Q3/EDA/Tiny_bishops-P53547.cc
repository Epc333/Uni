#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

const vector<pair<int,int>> dir = {{-1, 1}, {1, 1}, {-1, -1}, {1, -1}};

bool vei_correcte(const vector<vector<string>>& caselles, int x, int y) {
    return (x >= 0 and x < caselles.size() and y >= 0 and y < caselles[0].size() and caselles[x][y] != "X");
}

int transformar (const string& c) {
    int num = 0;
    for (int i = 0; i < c.length(); ++i) {
        num +=  c[i] - '0';
        num *= 10;
    }
    return num/10;
}

void dfs(vector<vector<string>>& caselles, int x, int y, int& suma, int& total) {
    if (caselles[x][y] != "X"){
        suma += transformar(caselles[x][y]);
        ++total;
        caselles[x][y] = "X";
        for (auto d : dir) {
            int v_x = x + d.first;
            int v_y = y + d.second;
            if (vei_correcte(caselles, v_x, v_y)){
                dfs(caselles, v_x, v_y, suma, total);
            }
        }
    }

}

bool moviment(vector<vector<string>>& caselles) {
    int prev = -1;
    for (int i = 0; i < caselles.size(); ++i) {
        for (int j = 0; j < caselles[0].size(); ++j) {
            if (caselles[i][j] != "X") {
                int sum = 0, total = 0;
                dfs(caselles, i, j, sum, total);
                if (total > 0 and sum%total != 0) return false;
                if (prev == -1) prev = sum/total;
                else if (prev != sum/total) return false;
            }
        }
    }
    return true;

}

int main () {
    int it;
    cin >> it;
    for (int i = 1; i <= it; ++i) {
        int n, m;
        cin >> n >> m;
        vector<vector<string>> caselles (n, vector<string>(m));
        for (int x = 0; x < n; ++x)
            for (int y = 0; y < m; ++y)
                cin >> caselles[x][y];
        if (moviment(caselles)) cout << "Case " << i << ": yes" <<endl;
        else cout << "Case " << i << ": no" << endl;
    }
}