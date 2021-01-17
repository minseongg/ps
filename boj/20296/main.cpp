#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

const ll MOD = 1e9 + 7;
const int MAX = 1100000;

inline ll pow(ll a, ll n) {
    if (n == 0) { return 1; }
    if (n == 1) { return a; }
    ll t = pow(a, n / 2);
    t = (t * t) % MOD;
    return (n % 2) ? (t * a) % MOD : t;
}

inline ll get_inv(ll a) {
    return pow(a, MOD - 2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    vector<ll> fac(MAX + 1), fac_inv(MAX + 1);
    fac[0] = 1; fac_inv[0] = 1;
    for (int i = 1; i <= MAX; i++) {
        fac[i] = (fac[i - 1] * i) % MOD;
        fac_inv[i] = get_inv(fac[i]);
    }

    ll n, l, r, k, ans = 0;
    cin >> n >> l >> r >> k;
    for (int i = 0; i <= n; i++) {
        ll tk = k - i * (r + 1) - (n - i) * l;
        if (tk < 0) { break; }
        ll t = fac[n];
        t = (t * fac_inv[i]) % MOD;
        t = (t * fac_inv[n - i]) % MOD;
        t = (t * fac[tk + n - 1]) % MOD;
        t = (t * fac_inv[n - 1]) % MOD;
        t = (t * fac_inv[tk]) % MOD;
        if (i % 2 == 0) {
            ans = (ans + t) % MOD;
        } else {
            ans = (ans - t + MOD) % MOD;
        }
    }

    cout << ans << "\n";
}