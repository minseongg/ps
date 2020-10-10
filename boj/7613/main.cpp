#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

int n;
vector<vector<int>> d, v;
vector<ll> x, y;

inline int ccw(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3) {
    ll o = (x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1);

    if (o > 0) {
        return 1;
    } else {
        return 0;
    }
}

void solve(int i, int j, int k) {
    v[j][k] = 1;

    if (k == i) { return; }

    if (!v[k][i]) { solve(i, k, i); }
    d[j][k] = d[k][i] + 1;

    for (int w = 0; w < n; w++) {
        if (w == i || w == j || w == k) { continue; }
        if (y[w] < y[i]) { continue; }

        if (ccw(x[j], y[j], x[k], y[k], x[w], y[w]) && ccw(x[k], y[k], x[w], y[w], x[i], y[i])) {
            if (!v[k][w]) { solve(i, k, w); }
            d[j][k] = max(d[j][k], d[k][w] + 1);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);

    int ans = 0;

    cin >> n;

    d.resize(n);
    v.resize(n);
    for (int i = 0; i < n; i++) {
        d[i].resize(n);
        v[i].resize(n);
    }

    for (int i = 0; i < n; i++) {
        double tx, ty;

        cin >> tx >> ty;

        x.emplace_back((ll)(tx * 100));
        y.emplace_back((ll)(ty * 100));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                d[j][k] = v[j][k] = 0;
            }
        }

        for (int j = 0; j < n; j++) {
            if (j == i) { continue; }
            if (y[j] < y[i]) { continue; }

            if (!v[i][j]) { solve(i, i, j); }
            ans = max(ans, d[i][j] + 1);
        }
    }

    cout << ans << "\n";
}