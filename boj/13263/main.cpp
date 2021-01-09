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

    int n;
    vector<ll> a, b;
    cin >> n;
    a.resize(n + 1); b.resize(n + 1);
    for (int i = 1; i <= n; i++) { cin >> a[n + 1 - i]; }
    for (int i = 1; i <= n; i++) { cin >> b[n + 1 - i]; }

    vector<ll> d(n + 1);
    vector<tuple<db, ll, ll>> lines(n);
    int lc = 0, it = 0;
    d[1] = 0;
    lines[lc++] = { 0, -a[1], 0 };
    for (int i = 2; i <= n; i++) {
        while (it < lc - 1 && b[i] >= get<0>(lines[it + 1])) { it++; }
        auto [ _, slope, bias ] = lines[it];
        d[i] = -(slope * b[i] + bias);

        ll new_slope = -a[i], new_bias = -d[i];
        while (lc > 1) {
            auto [ prev_x, prev_slope, prev_bias ] = lines[lc - 1];
            db new_x = cx(prev_slope, prev_bias, new_slope, new_bias);
            if (new_x <= prev_x) { lc--; }
            else { break; }
        }
        it = min(it, lc - 1);
        auto [ prev_x, prev_slope, prev_bias ] = lines[lc - 1];
        db new_x = cx(prev_slope, prev_bias, new_slope, new_bias);
        lines[lc++] = { new_x, new_slope, new_bias };
    }
    cout << d[n] << "\n";
}