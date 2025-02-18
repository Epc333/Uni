#include <iostream>
#include <vector>
using namespace std;

bool position(double x, const vector<double>& v, int left, int right) {
    if (left > right) return false;
    else {
        int m = (left + right) / 2;
        if (v[m] > x) return (m != v.size()-1 and v[m+1] == x) or position(x, v, left, m-1);
        else if (v[m] < x) return (m!= 0 and v[m-1] == x) or position(x, v, m+1, right);
        return true;
    }
}

bool resistant_search(double x, const vector<double>& v) {
    return position(x, v, 0, v.size()-1);
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
            cout << resistant_search(x, V) << endl;
        }
    }
}