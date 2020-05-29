#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 9;

int main() {
    int n, m;
    vector<vector<int>> d, s;

    cin >> n >> m;

    d.resize(n + 1);
    s.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        d[i].resize(m + 1);
        s[i].resize(m + 1);
    }

    for (int j = 0; j <= m; j++) {
        d[2][j] = 1;
        s[2][j] = j + 1;
    }
    for (int i = 3; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            int t = min(i - 1, j);

            d[i][j] = (s[i - 1][j] - ((j - t) ? s[i - 1][j - t - 1] : 0) + MOD) % MOD;
            s[i][j] = j ? (s[i][j - 1] + d[i][j]) % MOD : d[i][j];
        }
    }

    cout << d[n][m] << "\n";
}
