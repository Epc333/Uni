#include <iostream>
#include <vector>
using namespace std;


int first_occurrence(double x, const vector<double>& v) {
    int left = 0, right = v.size() - 1, pos = -1;

    while (left <= right) {
        int m = (left + right) / 2;
        if (v[m] == x) {
            pos = m;
            right = m - 1;
        } 
        else if (v[m] < x) left = m + 1;
        else right = m - 1;
    }
    return pos;
}

/*
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
*/

