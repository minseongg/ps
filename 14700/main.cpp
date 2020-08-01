#include <iostream>
#include <vector>

using namespace std;

using vvvi = vector<vector<vector<int>>>;

const int MOD = 1e9 + 7;

inline int cond(int m, int mask) {
    int x1 = mask & (1 << m), xm = mask & 2, xm1 = mask & 1;

    if (x1 && xm && xm1) { return false; }
    return true;
}

int main() {
    int n, m;
    vvvi d;

    cin >> n >> m;

    if (n < m) { swap(n, m); }

    if (m == 1) {
        int ans = 1;
        
        for (int i = 0; i < n; i++) {
            ans <<= 1;
            ans %= MOD;
        }

        cout << ans << "\n";
        return 0;
    }

    d.resize(n);
    for (int i = 0; i < n; i++) {
        d[i].resize(m);
        for (int j = 0; j < m; j++) {
            d[i][j].resize(1 << (m + 1));
        }
    }

    for (int i = 1; i < n; i++) {
        if (i == 1) {
            for (int mask = 0; mask < (1 << (m + 1)); mask++) {
                d[i][0][mask] = 1;
            }
        } else {
            for (int mask = 0; mask < (1 << (m + 1)); mask++) {
                d[i][0][mask] = (d[i - 1][m - 1][mask >> 1] + d[i - 1][m - 1][(mask >> 1) + (1 << m)]) % MOD;
            }
        }

        for (int j = 1; j < m; j++) {
            for (int mask = 0; mask < (1 << (m + 1)); mask++) {
                if (cond(m, mask)) {
                    d[i][j][mask] = (d[i][j - 1][mask >> 1] + d[i][j - 1][(mask >> 1) + (1 << m)]) % MOD;
                } else {
                    d[i][j][mask] = d[i][j - 1][mask >> 1];
                }
            }
        }
    }

    int ans = 0;
    for (int mask = 0; mask < (1 << (m + 1)); mask++) {
        ans += d[n - 1][m - 1][mask];
        ans %= MOD;
    }

    cout << ans << "\n";
}