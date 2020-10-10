#include <iostream>

using namespace std;

int main() {
    int n, m, ans = 1;

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        int x;

        cin >> x;

        ans *= (x == 0 ? 1 : x);
        ans %= m;
    }

    cout << ans % m << "\n";
}
