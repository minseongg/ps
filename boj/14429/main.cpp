#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, j, m, ans = 1e5, ansi;

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> j >> m;

        if (ans > (j - 1) / (m + 1)) {
            ans = (j - 1) / (m + 1);
            ansi = i + 1;
        }
    }

    cout << ansi << " " << ans * 2 + 2 << "\n";
}