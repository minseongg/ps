#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

using ll = long long;
using vi = vector<int>;
using vvll = vector<vector<ll>>;

const ll INF = 1e18;

ll solve(vi &a) {
    int sz = (int)a.size();
    vi s;
    vvll d, e;

    d.resize(sz);
    e.resize(sz);
    for (int i = 0; i < sz; i++) {
        d[i].resize(sz);
        e[i].resize(sz);
    }

    s = a;
    sort(s.begin(), s.end());

    for (int i = 0; i < sz; i++) {
        d[0][i] = abs(a[0] - s[i]);
        e[0][i] = (i ? min(e[0][i - 1], d[0][i]) : d[0][0]);
    }

    for (int i = 1; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            d[i][j] = abs(a[i] - s[j]) + e[i - 1][j];
            e[i][j] = (j ? min(e[i][j - 1], d[i][j]) : d[i][j]);
        }
    }

    return e[sz - 1][sz - 1];
}

int main() {
    ios::sync_with_stdio(false);

    int n;
    vi a;
    ll ans = INF;

    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    ans = min(ans, solve(a));
    for (int i = 0; i < n; i++) a[i] = -a[i];
    ans = min(ans, solve(a));

    cout << ans << "\n";
}