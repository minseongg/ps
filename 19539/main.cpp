#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int n, x, s = 0, c = 0;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x;
        s += x;
        c += x / 2;
    }

    if (s <= 3 * c && s % 3 == 0) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}