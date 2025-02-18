#include <iostream>
#include <vector>
using namespace std;


int primera_aparicio (double x, const vector<double>& v, int l, int r) {
    if (l > r) return -1;
    else {
        int m = (l+r)/2;
        if (v[m] == x) {
            int p_left = primera_aparicio(x, v, l, m - 1);
            if (p_left == -1) return m;
            else return p_left;
        } else if (v[m] > x) {
            int p_left = primera_aparicio(x, v, l, m-1);
            if (p_left == - 1) {
                if (m + 1 <= r and v[m+1] == x) return m+1;
                else return -1;
            } else return p_left;
        } else {
            if (m - 1 >= l and v[m-1] == x) return m-1;
            return primera_aparicio(x, v, m+1, r);
        }
    }
}

int first_occurrence(double x, const vector<double>& v) {
    return primera_aparicio(x, v, 0, v.size()-1);
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