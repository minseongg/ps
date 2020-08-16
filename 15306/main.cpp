#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

const ll MOD = 1e9 + 7;
const int MAXP = 40;

inline ll add(ll a, ll b) {
    return (a + b) % MOD;
}

inline ll mul(ll a, ll b) {
    return (a * b) % MOD;
}

inline ll div2(ll a) {
    return (a * (ll)(5e8 + 4)) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll n, l, r, ans = 0;
    vector<vector<ll>> d, g;

    cin >> n >> l >> r;

    d.resize(n + 1);
    g.resize(n + 1);

    for (int i = 0; i <= n; i++) {
        d[i].resize(MAXP);
        g[i].resize(MAXP);
    }

    d[0][0] = 1;
    d[1][0] = 1;

    for (int i = 2; i <= n; i++) {
        d[i][0] = add(d[i - 1][0], mul(i - 1, d[i - 2][0]));
        g[i][0] = add(mul(i, g[i - 1][0]), mul(i, mul(i - 1, d[i - 2][0])));

        for (int j = 1; j < MAXP; j++) {
            d[i][j] = add(d[i - 1][j], add(mul(i - 1, d[i - 2][j]), div2(g[i - 1][j - 1])));
            g[i][j] = add(mul(i, g[i - 1][j]), mul(i, mul(i - 1, d[i - 2][j])));
        }
    }

    for (int i = 0; i < MAXP; i++) {
        if ((ll)(1 << i) >= l && (ll)(1 << i) <= r) {
            ans = add(ans, d[n][i]);
        }
    }

    cout << ans << "\n";
}
