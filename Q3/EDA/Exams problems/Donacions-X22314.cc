#include <iostream>
#include <map>
using namespace std;


int main() {
  map<string, int> M;
  char c;
  while (cin >> c) {
    if (c == 'N') {
      cout <<  "number: " << M.size() << endl;
    }
    else if (c == 'D') {
      string nif;
      int money;
      cin >> nif >> money;
      if (M.find(nif) == M.end()) M[nif] = money;
      else M[nif] += money;
    }
    else if (c == 'Q') {
      string nif;
      cin >> nif;
      if (M.find(nif) == M.end()) cout << -1 << endl;
      else cout << M[nif] << endl;
    }
    else if (c == 'P') {
        bool first = true;
        for (map<string, int>::iterator it = M.begin(); it != M.end(); ++it) {
            if (it->first[7] % 2 == 0) {
                if (not first) cout << " ";
                first = false;
                cout << it->first;
            }
        }
        cout << endl;
    }
    else { // c == 'L'
      if (M.end() == M.begin()) cout << "NO LAST NIF" << endl;
      else {
        map<string, int>::iterator it = M.end();
        --it;
        cout << it->first << " " << it->second << endl;
      }
    }
  }
}
