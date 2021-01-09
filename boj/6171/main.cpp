#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using db = double;
using ll = long long;

inline db cx(ll a, ll b, ll c, ll d) {
    return (db)(d - b) / (db)(a - c);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    vector<pair<ll, ll>> g, g_red;
    cin >> n;
    g.resize(n);
    for (int i = 0; i < n; i++) { cin >> g[i].first >> g[i].second; }
    sort(g.begin(), g.end());

    int sz = 0;
    g_red.resize(n);
    for (int i = 0; i < n; i++) {
        while (sz && g_red[sz - 1].first <= g[i].first && g_red[sz - 1].second <= g[i].second) { sz--; }
        g_red[sz++] = g[i];
    }

    vector<tuple<db, ll, ll>> lines(sz + 1);
    vector<ll> d(sz + 1);
    int lc = 0, it = 0;
    lines[lc++] = { 0, -g_red[0].second, 0 };
    for (int i = 1; i <= sz; i++) {
        while (it < lc - 1 && g_red[i - 1].first >= get<0>(lines[it + 1])) { it++; }
        auto [ _, slope, bias ] = lines[it];
        d[i] = -(slope * g_red[i - 1].first + bias);

        if (i == sz) { break; }

        ll new_slope = -g_red[i].second, new_bias = -d[i];
        while (lc > 1) {
            auto [ prev_x, prev_slope, prev_bias ] = lines[lc - 1];
            db new_x = cx(prev_slope, prev_bias, new_slope, new_bias);
            if (prev_x >= new_x) { lc--; }
            else { break; }
        }
        it = min(it, lc - 1);
        auto [ prev_x, prev_slope, prev_bias ] = lines[lc - 1];
        db new_x = cx(prev_slope, prev_bias, new_slope, new_bias);
        lines[lc++] = { new_x, new_slope, new_bias };
    }

    cout << d[sz] << "\n";
}