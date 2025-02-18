#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <cmath>
using namespace std;

const int inf = numeric_limits<int>::max();

struct Roca{
    double x;
    double y;
    double radi;
};

double calcula_distancia (const Roca& R1, const Roca& R2) {
    double x = abs(R2.x - R1.x);
    double y = abs(R2.y - R1.y);
    x = pow(x, 2);
    y = pow(y, 2);
    return sqrt(x+y) - R1.radi - R2.radi;
}

int calcula_salts(const vector<Roca>& R, double d) {
    vector<int> Salts (R.size(), inf);
    Salts[0] = 0;
    queue<int> Q;
    Q.push(0);
    
    while (not Q.empty()) {
        int act = Q.front();
        Q.pop();
        for (int i = 0; i < R.size(); ++i) {
            if (Salts[i] == inf and calcula_distancia(R[act], R[i]) < d) {
                Salts[i] = Salts[act] + 1;
                Q.push(i);
                if (Salts[R.size()-1] != inf) return Salts[R.size()-1];
            }
        }
    }
    return -1;
}


int main () {
    int n;
    double m;
    while (cin >> n >> m) {
        vector<Roca> R (n);
        for (int i = 0; i < n; ++i)
            cin >> R[i].x >> R[i].y >> R[i].radi;
        int salts = calcula_salts(R, m);
        if (salts != -1)
            cout << salts << endl;
        else 
            cout << "Xof!" << endl;
    }
}