#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

const ll INF = 1e16;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t, b, c = 1;
    ll ans;
    pair<int, int> ansp = {1e9, 1e9};
    vector<pair<int, int>> v;

    cin >> t;

    while (t--) {
        ans = INF;
        ansp = {1e9, 1e9};
        v.clear();

        cin >> b;

        while (b--) {
            int x1, y1, x2, y2;

            cin >> x1 >> y1 >> x2 >> y2;

            for (int x = x1; x <= x2; x++) {
                for (int y = y1; y <= y2; y++) {
                    v.emplace_back(x, y);
                }
            }
        }

        for (auto &x : v) {
            ll s = 0;

            for (auto &y : v) {
                s += (ll)abs(x.first - y.first) + (ll)abs(x.second - y.second);
            }

            if (ans >= s) {
                if (ans > s) { ansp = x; }
                else if (ansp > x) { ansp = x; }

                ans = s;
            }
        }

        cout << "Case #" << c << ": " << ansp.first << " " << ansp.second << " " << ans << "\n";
        c++;
    }
}
