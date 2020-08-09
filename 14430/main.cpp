#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    vector<vector<int>> v, d;

    cin >> n >> m;

    v.resize(n);
    d.resize(n);

    for (int i = 0; i < n; i++) {
        v[i].resize(m);
        d[i].resize(m);

        for (int j = 0; j < m; j++) {
            cin >> v[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        if (i) { d[i][0] = d[i - 1][0] + v[i][0]; } else { d[0][0] = v[0][0]; }

        for (int j = 1; j < m; j++) {
            if (i) { d[i][j] = max(d[i - 1][j], d[i][j - 1]) + v[i][j]; } else { d[0][j] = d[0][j - 1] + v[0][j]; }
        }
    }

    cout << d[n - 1][m - 1] << "\n";
}