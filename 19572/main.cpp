#include <iostream>

using namespace std;

int main() {
    int d1, d2, d3, ta, tb, tc;

    cin >> d1 >> d2 >> d3;

    ta = d1 + d2 - d3;
    tb = d1 + d3 - d2;
    tc = d2 + d3 - d1;

    if (ta <= 0 || tb <= 0 || tc <= 0) {
        cout << "-1\n";
    } else {
        cout << "1\n";
        cout << ta / 2 << "." << ta % 2 * 5 << " ";
        cout << tb / 2 << "." << tb % 2 * 5 << " ";
        cout << tc / 2 << "." << tc % 2 * 5 << "\n";
    }
}
