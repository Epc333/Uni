#include <iostream>
#include <vector>
using namespace std;


int pos (double x, const vector<double>& v, int e, int d) {
    if (d < e) return -1;
    else{
        int m = (e+d)/2;
        if (v[m] == x ) return m; 
        else if (v[m] > x) return pos(x, v, e, m-1);
        else return pos(x, v, m+1, d);
    }
}

int first_occurrence(double x, const vector<double>& v) {
    return pos(x, v, 0, v.size()-1);
}


int main() {
    int n;
    while (cin >> n) {
        vector<double> V(n);
        for (int i = 0; i < n; ++i) cin >> V[i];
        int t;
        cin >> t;
        while (t--) {
            double x;
            cin >> x;
            cout << first_occurrence(x, V) << endl;
        }
    }
}
