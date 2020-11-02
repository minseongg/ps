#include <iostream>

using namespace std;

using db = double;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int a, b, c, need, p = 1, q = 1;

    cin >> a >> b >> c;
    need = (c + 4) / 5;

    if (need > b) { cout << 1 << "\n"; return 0; }
    for (int i = 0; i < need; i++) {
        p *= (b - i);
        q *= (a - i);
    }

    cout.precision(9);
    cout << 1 - (db)p / (db)q << "\n";
}