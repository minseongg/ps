#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    vector<int> k, s;
    ll ans = 0;
    cin >> n;
    k.resize(n + 1);
    s.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> k[i];
        s[i] = s[i - 1] + k[i];
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i <= j) {
                if (s[i - 1] - s[j] > 0) {
                    ans += (ll)(s[i - 1] - s[j] - 1) / s[n] + 1;
                }
            } else {
                if (s[i - 1] - s[j] - s[n] > 0) {
                    ans += (ll)(s[i - 1] - s[j] - s[n] - 1) / s[n] + 1;
                }
            }
        }
    }

    cout << ans << "\n";
}