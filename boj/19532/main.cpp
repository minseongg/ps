#include <iostream>

using namespace std;

int main() {
    int a, b, c, d, e, f;

    cin >> a >> b >> c >> d >> e >> f;
    cout << (c * e - b * f) / (a * e - b * d) << " " << (a * f - c * d) / (a * e - b * d) << "\n";
}