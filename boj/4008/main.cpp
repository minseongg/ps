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
    ll a, b, c;
    vector<ll> x, s;
    cin >> n >> a >> b >> c;
    x.resize(n + 1); s.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
        s[i] = s[i - 1] + x[i];
    }

    vector<tuple<db, ll, ll>> lines(n + 1);
    vector<ll> d(n + 1);
    int lc = 0, it = 0;
    lines[lc++] = { 0, 0, 0 };
    for (int i = 1; i <= n; i++) {
        while (it < lc - 1 && s[i] >= get<0>(lines[it + 1])) { it++; }
        auto [ _, slope, bias ] = lines[it];
        d[i] = slope * s[i] + bias + a * s[i] * s[i] + c;
        
        ll new_slope = (-2) * a * s[i], new_bias = d[i] + a * s[i] * s[i];
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

    cout << d[n] + b * s[n] << "\n";
}