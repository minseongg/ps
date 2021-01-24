#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

const int MAXN = 2e3;
const int LG = 42;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, a, b;
    vector<ll> y;
    cin >> n >> a >> b;
    y.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> y[i];
    }

    ll lo = 0, hi = (1ll << LG) - 1, ans;
    if (n <= 100) {
        while (lo < hi) {
            ll m = (lo + hi) >> 1;
            vector<vector<int>> avail;
            avail.resize(n + 1);
            for (int i = 0; i <= n; i++) { avail[i].resize(n + 1); }

            avail[0][0] = 1;
            for (int i = 1; i <= n; i++) {
                ll s = 0;
                for (int j = i; j >= 1; j--) {
                    s += y[j];
                    if ((s | m) == m) {
                        for (int k = 0; k < b; k++) {
                            if (avail[j - 1][k]) {
                                avail[i][k + 1] = 1;
                            }
                        }
                    }
                }
            }

            int flag = 0;
            for (int i = a; i <= b; i++) {
                if (avail[n][i]) {
                    flag = 1;
                    break;
                }
            }

            if (flag) {
                hi = m;
                ans = m;
            } else {
                lo = m + 1;
            }
        }
    } else {
        while (lo < hi) {
            ll m = (lo + hi) >> 1;
            vector<ll> d(n + 1), avail(n + 1);
            avail[0] = 1;
            for (int i = 1; i <= n; i++) {
                ll s = 0, flag = 0, t = MAXN;
                for (int j = i; j >= 1; j--) {
                    s += y[j];
                    if ((s | m) == m && avail[j - 1]) {
                        flag = 1;
                        t = min(t, d[j - 1] + 1);
                    }
                }
                if (flag) {
                    avail[i] = 1;
                    d[i] = t;
                }
            }

            if (avail[n] && d[n] <= b) {
                hi = m;
                ans = m;
            } else {
                lo = m + 1;
            }
        }
    }

    cout << ans << "\n";
}