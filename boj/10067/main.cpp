#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

using db = double;
using ll = long long;

inline db cx(ll a, ll b, ll c, ll d) {
    return (db)(d - b) / (db)(a - c);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    vector<ll> a, s;
    cin >> n >> k;
    a.resize(n + 1); s.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        s[i] = s[i - 1] + a[i];
    }

    vector<vector<ll>> d(n + 1);
    vector<vector<int>> trace(n + 1);
    vector<tuple<db, ll, ll, int>> lines(n + 1);
    int parity = 0;
    for (int i = 1; i <= n; i++) { d[i].resize(2); trace[i].resize(k + 1); }
    for (int j = 1; j <= k; j++) {
        int lc = 0, it = 0;
        lines[lc++] = { 0, s[j], d[j][parity] - s[j] * s[j], j };
        for (int i = j + 1; i <= n; i++) {
            while (it < lc - 1 && s[i] >= get<0>(lines[it + 1])) { it++; }
            auto [ _, slope, bias, idx ] = lines[it];
            d[i][parity ^ 1] = slope * s[i] + bias;
            trace[i][j] = idx;

            ll new_slope = s[i], new_bias = d[i][parity] - s[i] * s[i];
            while (lc > 1) {
                auto [ prev_x, prev_slope, prev_bias, t ] = lines[lc - 1];
                if (prev_slope == new_slope) { break; }
                db new_x = cx(prev_slope, prev_bias, new_slope, new_bias);
                if (prev_x >= new_x) { lc--; }
                else { break; }
            }
            it = min(it, lc - 1);
            auto [ prev_x, prev_slope, prev_bias, tt ] = lines[lc - 1];
            if (prev_slope == new_slope) { continue; }
            db new_x = cx(prev_slope, prev_bias, new_slope, new_bias);
            lines[lc++] = { new_x, new_slope, new_bias, i };
        }
        parity ^= 1;
    }

    cout << d[n][parity] << "\n";
    vector<int> ans;
    int it = n;
    for (int i = k; i >= 1; i--) {
        ans.emplace_back(trace[it][i]);
        it = trace[it][i];
    }
    for (int x : ans) {
        cout << x << " ";
    }
    cout << "\n";
}