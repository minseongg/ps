#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long;
using vll = vector<ll>;

ll subsum(ll l, ll r, vll &s) {
    if (l > r) { return 0; }
    return s[r] - s[l - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int r;
    ll l, b;
    vll x, s;
    cin >> r >> l >> b;
    x.resize(r + 1);
    s.resize(r + 1);
    for (int i = 1; i <= r; i++) {
        cin >> x[i];
        s[i] = s[i - 1] + x[i];
    }

    ll ans = 0;
    for (int i = 1; i <= r; i++) {
        ll lo = 1, hi = l;
        ans = max(ans, (ll)(upper_bound(x.begin() + 1, x.end(), x[i]) - lower_bound(x.begin() + 1, x.end(), x[i])));
        while (lo <= hi) {
            ll mi = (lo + hi) >> 1;
            ll f1 = lower_bound(x.begin() + 1, x.end(), x[i] - mi) - x.begin();
            ll f2 = upper_bound(x.begin() + 1, x.end(), x[i] - mi) - x.begin();
            ll f3 = lower_bound(x.begin() + 1, x.end(), x[i] + mi) - x.begin();
            ll f4 = upper_bound(x.begin() + 1, x.end(), x[i] + mi) - x.begin();

            ll same = (f2 - f1) + (f4 - f3);
            ll s1 = max(i - f2, 0LL) * x[i] - subsum(f2, i - 1, s);
            ll s2 = subsum(i, f3 - 1, s) - max(f3 - i, 0LL) * x[i];
            if (s1 + s2 > b) {
                hi = mi - 1;
            } else if (s1 + s2 + same * mi <= b) {
                ans = max(ans, f3 - f2 + same);
                lo = mi + 1;
            } else {
                ans = max(ans, f3 - f2 + (b - s1 - s2) / mi);
                break;
            }
        }
    }
    cout << ans << "\n";
}