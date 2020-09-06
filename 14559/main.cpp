#include <iostream>
#include <vector>

using namespace std;

using ll = long long;
using mat = vector<vector<ll>>;

const ll MOD = 1e9 + 9;
const ll sz = 167;

mat mul(mat a, mat b) {
    mat c;

    c.resize(sz);
    for (int i = 0; i < sz; i++) {
        c[i].resize(sz);
    }

    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            for (int k = 0; k < sz; k++) {
                c[i][j] += a[i][k] * b[k][j];
                c[i][j] %= MOD;
            }
        }
    }

    return c;
}

inline mat unit() {
    mat c;

    c.resize(sz);
    for (int i = 0; i < sz; i++) {
        c[i].resize(sz);
    }

    for (int i = 0; i < sz; i++) {
        c[i][i] = 1;
    }

    return c;
}

mat square(mat a, int m) {
    if (m == 0) {
        return unit();
    } else if (m == 1) {
        return a;
    }

    mat b = square(a, m / 2);
    b = mul(b, b);

    if (m % 2) b = mul(b, a);

    return b;
}

int main() {
    ll n, m, a, b, c, d, e, f;
    mat q;

    cin >> n >> m >> a >> b >> c >> d >> e >> f;

    n %= sz;

    q.resize(sz);
    for (int i = 0; i < sz; i++) {
        q[i].resize(sz);
    }

    for (ll i = 0; i < sz; i++) {
        ll next_1 = (a * i * i + b * i + c) % sz;
        ll next_2 = (d * i * i + e * i + f) % sz;

        q[next_1][i]++;
        q[next_2][i]++;
    }

    q = square(q, m);

    ll t = 112345, p = 1, ans = 0;

    for (int i = 0; i < sz; i++) {
        ans = (ans + p * q[i][n]) % MOD;
        p = (p * t) % MOD;
    }

    cout << ans << "\n";
}