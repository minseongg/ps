#include <iostream>

using namespace std;

int main() {
    double pi = 3.141592;
    double d1, d2;

    cout << fixed;
    cout.precision(6);

    cin >> d1 >> d2;
    cout << d1 * 2.0 + d2 * 2.0 * pi << "\n";
}
