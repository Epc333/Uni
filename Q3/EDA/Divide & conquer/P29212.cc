#include <iostream>
using namespace std;

int nkmod(long long n, long long k, int m) {
    long long result = 1;
    n = n % m;
    while (k > 0) {
        if (k % 2 == 1)  result = (result * n) % m;
        n = (n * n) % m;
        k /= 2;
    }
    return result;
}

int main() {
    long long n, k;
    int m;
    while (cin >> n >> k >> m) {
        int result = nkmod(n, k, m);
        cout << result << endl;
    }
    return 0;
}