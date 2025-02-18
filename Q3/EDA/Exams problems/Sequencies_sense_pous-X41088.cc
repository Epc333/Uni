#include <iostream>
#include <vector>
using namespace std;
bool compatible(int left, int mid, int right, int n)
{
    return left + right <= 2 * mid;
}
void write_no_well_permutations(int n, vector<int> &partial_sol, vector<bool> &used)
{
    if (int(partial_sol.size()) == n)
    {
        cout << "(";
        for (int i = 0; i < n; ++i)
            cout << (i == 0 ? "" : ",") << partial_sol[i];
        cout << ")" << endl;
    }
    else
    {
        for (int k = 1; k <= n; ++k)
        {
            if (not used[k])
            {
                if (partial_sol.size() <= 1 or compatible(partial_sol[partial_sol.size() - 2], partial_sol.back(), k, n))
                {
                    partial_sol.push_back(k);
                    used[k] = true;
                    write_no_well_permutations(n, partial_sol, used);
                    used[k] = false;
                    partial_sol.pop_back();
                }
            }
        }
    }
}
void write_no_well_permutations(int n)
{
    vector<bool> used(n + 1, false);
    vector<int> partial_sol;
    write_no_well_permutations(n, partial_sol, used);
}
int main()
{
    int n;
    cin >> n;
    write_no_well_permutations(n);
}