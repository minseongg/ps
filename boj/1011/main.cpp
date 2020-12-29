#include <iostream>

using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        ll x, y, d, s = 1, c = 1;
        cin >> x >> y;
        d = y - x;
        while (s < d) {
            s += (c + 2) / 2;
            c++;
        }
        cout << c << "\n";
    }
}