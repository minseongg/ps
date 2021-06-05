#include <iostream>

using namespace std;

inline void f(int k, int &c1, int &c2) {
    if (k < 0) { c1++; }
    else if (k > 0) { c2++; }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int a, b, c, x1, x2, y1, y2, f1 = 0, f2 = 0;
    cin >> a >> b >> c >> x1 >> x2 >> y1 >> y2;

    f(a * x1 + b * y1 + c, f1, f2);
    f(a * x1 + b * y2 + c, f1, f2);
    f(a * x2 + b * y1 + c, f1, f2);
    f(a * x2 + b * y2 + c, f1, f2);

    if (f1 && f2) { cout << "Poor\n"; }
    else { cout << "Lucky\n"; }
}
