#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;


int main() {
    string s;
    map<string, int> bossa;
    while (cin >> s) {
        if (s == "minimum?") {
            if (not bossa.empty()) {
                map<string,int>::iterator it = bossa.begin();
                cout << "minimum: " << it -> first << ", " << it -> second << " time(s)" << endl;

            } else 
                cout << "indefinite minimum" << endl;

        } else if (s == "store") {
            string w;
            cin >> w;
            if (bossa.find(w) != bossa.end())
                ++bossa[w];
            else
                bossa[w] = 1;

        } else if (s == "delete") {
            string w;
            cin >> w;
            if (bossa.find(w) != bossa.end()){
                if (bossa[w] > 1)
                    --bossa[w];
                else 
                    bossa.erase(w);
            }
        } else if (s == "maximum?") {
            if (not bossa.empty()) {
                map<string,int>::iterator it = bossa.end();
                --it;
                cout << "maximum: " << it -> first << ", " << it -> second << " time(s)" << endl;
            } else
                cout << "indefinite maximum" << endl;
        }
    }
}
