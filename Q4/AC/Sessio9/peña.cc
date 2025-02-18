#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int main(){
    double x = 665857, y = 470832;
    double r = pow(x, 4.) - 4 * pow(y, 4.) - 4 * pow(y, 2.);
    cout << r << endl;

}