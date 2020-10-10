#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

const int MAXR = 100;

void fill_d(vector<vector<ll>> &d, vector<ll> &l, vector<ll> &c, int m) {
    for (ll r1 = 0; r1 <= MAXR; r1++) {
        for (ll r2 = 0; r2 <= MAXR; r2++) {
            ll cul1 = l[0] + l[1], cul2 = l[0], maxc = r1 * l[0] + c[0];

            for (int i = 1; i < m; i++) {
                if (maxc < r1 * cul1 - r2 * cul2 + c[i]) {
                    maxc = r1 * cul1 - r2 * cul2 + c[i];
                }

                cul1 += l[i + 1];
                cul2 += l[i];
            }

            d[(int)r1][(int)r2] = maxc;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    vector<ll> l, c, r;
    ll lsum = 0, t = 0;
    vector<vector<ll>> d;

    cin >> n >> m;
    l.resize(m);
    c.resize(m);
    r.resize(n);
    for (int i = 0; i < m; i++) {
        cin >> l[i];
        lsum += l[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> c[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> r[i];
    }

    d.resize(MAXR + 1);
    for (int i = 0; i <= MAXR; i++) d[i].resize(MAXR + 1);

    fill_d(d, l, c, m);

    for (int i = 0; i < n; i++) {
        if (i) {
            int r1 = r[i - 1], r2 = r[i];
            
            t += d[r1][r2];
        }
        cout << t + r[i] * lsum << " ";
    }
    cout << "\n";
}