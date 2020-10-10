#include <iostream>

using namespace std;

int main() {
    int a, b, c, d, e;

    cin >> a >> b >> c >> d >> e;

    if (a > 0) {
        cout << e * (b - a) << "\n";
    } else {
        cout << c * (-a) + d + e * b << "\n";
    }
}