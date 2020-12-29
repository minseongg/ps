#include <iostream>
#include <vector>

using namespace std;

const int INF = 1e7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int c, n;
    vector<int> a, b;
    vector<vector<int>> d;

    cin >> c >> n;
    a.resize(n);
    b.resize(n);
    d.resize(n);
    for (int i = 0; i < n; i++) {
        d[i].resize(c + 1);
        cin >> a[i] >> b[i];
    }

    for (int i = 0; i < n; i++) {
        d[i][0] = 0;
        for (int j = 1; j <= c; j++) {
            d[i][j] = (i ? d[i - 1][j] : INF);
            d[i][j] = min(d[i][j], d[i][max(j - b[i], 0)] + a[i]);
        }
    }

    cout << d[n - 1][c] << "\n";
}