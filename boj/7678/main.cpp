#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, c;
    vector<vector<double>> d, p;
    vector<pair<int, int>> r;

    while(true) {
        cin >> n;

        if (n == -1) { break; }

        c = 1 << n;

        p.clear();
        p.resize(c);
        for (int i = 0; i < c; i++) {
            p[i].resize(c);

            for (int j = 0; j < c; j++) {
                cin >> p[i][j];
            }
        }

        d.clear();
        d.resize(c * 2);
        for (int i = 0; i < c * 2; i++) {
            d[i].resize(c);
        }

        r.resize(c * 2);
        r[1] = { 0, c - 1 };
        for (int i = 1; i < c; i++) {
            int left = r[i].first, right = r[i].second;

            r[i << 1] = { left, (left + right) >> 1 };
            r[(i << 1) + 1] = { ((left + right) >> 1) + 1, right };
        }

        for (int i = c; i < c * 2; i++) {
            d[i][i - c] = 1.0;
        }

        for (int i = c - 1; i >= 1; i--) {
            for (int j = r[i * 2].first; j <= r[i * 2].second; j++) {
                for (int k = r[i * 2 + 1].first; k <= r[i * 2 + 1].second; k++) {
                    d[i][j] += d[i * 2][j] * d[i * 2 + 1][k] * p[j][k];
                }
            }
            for (int j = r[i * 2 + 1].first; j <= r[i * 2 + 1].second; j++) {
                for (int k = r[i * 2].first; k <= r[i * 2].second; k++) {
                    d[i][j] += d[i * 2 + 1][j] * d[i * 2][k] * p[j][k];
                }
            }
        }

        double ansp = 0;
        int ans = 0;

        for (int i = 0; i < c; i++) {
            if (ansp < d[1][i]) {
                ans = i + 1;
                ansp = d[1][i];
            }
        }

        cout << ans << "\n";
    }
}
