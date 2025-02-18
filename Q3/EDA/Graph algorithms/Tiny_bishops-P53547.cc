#include <iostream>
#include <vector>
using namespace std;

int main (){
    int it;
    cin >> it;
    for (int i = 1; i <= it; ++i) {
        int n, m;
        cin >> n >> m;
        vector<vector<char>> caselles  (n, vector<char> (m));
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
                cin >> caselles[j][k];

        


        cout << "Case " << i << ": ";
        if (true) cout << "yes" << endl;
        else cout << "no" << endl;
    }
}