#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

const ll MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    ll x, s = 1, ans = 0;
    vector<pair<ll, ll>> v;

    cin >> n >> x;

    for (int i = 0; i < n + 1; i++) {
        ll a, c;

        cin >> a >> c;
        v.emplace_back(a, c);
    }

    for (int i = n; i >= 0; i--) {
        ans = (ans + v[i].first * s) % MOD;

        s *= x;
        s %= MOD;
    }

    cout << ans << "\n";
}
