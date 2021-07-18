#include <iostream>

using namespace std;

int main() {
    int n, ans = 0;
    cin >> n;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n - i; j++) {
            int k = n - i - j;
            ans = max(ans, (i + 1) * (j + 1) * (k + 1) - i * j * k);
        }
    }
    cout << ans << "\n";
}
