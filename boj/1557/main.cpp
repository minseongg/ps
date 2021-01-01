#include <iostream>
#include <vector>

using namespace std;

using vi = vector<int>;
using ll = long long;

const ll MAXANS = 1e10;
const int SQRT_MAXANS = 1e5;

vi mobius(int n) {
    vi p(n + 1), m(n + 1);

    for (int i = 2; i <= n; i++) { p[i] = 1; }
    for (int i = 1; i <= n; i++) { m[i] = 1; }
    for (int i = 2; i <= n; i++) {
        if (p[i]) {
            for (int j = 1; j <= n / i; j++) {
                if (j >= i) { p[i * j] = 0; }
                m[i * j] *= (-1);
                if (j % i == 0) { m[i * j] = 0; }
            }
        }
    }

    return m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    vi mob = mobius(SQRT_MAXANS);
    ll k, ans = 0;
    cin >> k;
    
    ll l = 1, r = MAXANS;
    while (l <= r) {
        ll m = (l + r) / 2, t = 0;
        for (ll i = 1; i * i <= m; i++) {
            t += mob[i] * (m / i / i);
        }

        if (t < k) {
            l = m + 1;
        } else {
            r = m - 1;
            ans = m;
        }
    }

    cout << ans << "\n";
}