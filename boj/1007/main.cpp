#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

using ll = long long;
using pll = pair<ll, ll>;

const ll INF = 1e18;

ll solve(vector<pll> &v, int it, int now, ll sx, ll sy, ll tx, ll ty) {
    int n = (int)v.size();

    if (now == n / 2) { return (tx - 2 * sx) * (tx - 2 * sx) + (ty - 2 * sy) * (ty - 2 * sy); }
    if (it == n) { return INF; }

    ll ans = INF;
    ans = min(ans, solve(v, it + 1, now + 1, sx + v[it].first, sy + v[it].second, tx, ty));
    ans = min(ans, solve(v, it + 1, now, sx, sy, tx, ty));
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed;
    cout.precision(9);

    int t;
    cin >> t;
    while (t--) {
        int n;
        vector<pll> v;
        ll tx = 0, ty = 0;
        cin >> n;
        v.resize(n);
        for (int i = 0; i < n; i++) {
            ll x, y;
            cin >> x >> y;
            v[i] = {x, y};
            tx += x;
            ty += y;
        }
        cout << (double)sqrt(solve(v, 0, 0, 0, 0, tx, ty)) << "\n";
    }
}