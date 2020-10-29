#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, s, t;
    string x, y, t1, t2;
    vector<vector<int>> d;

    cin >> n >> x >> y >> s >> t;
    d.resize(n);
    for (int i = 0; i < n; i++) { d[i].resize(3); }

    for (int i = 0; i < n; i++) {
        if (i == s || i == t) { t2 += x[i]; }
        else { t1 += x[i]; }
    }

    d[0][0] = 1;
    d[0][1] = (t2[0] == y[0]);
    d[0][2] = (t2[0] == y[0] && t2[1] == y[1]);
    for (int i = 1; i <= n - 2; i++) {
        if (t1[i - 1] == y[i - 1] && d[i - 1][0]) { d[i][0] = 1; }

        if (t1[i - 1] == y[i] && d[i - 1][1]) { d[i][1] = 1; }
        if (t2[0] == y[i] && d[i][0]) { d[i][1] = 1; }

        if (t1[i - 1] == y[i + 1] && d[i - 1][2]) { d[i][2] = 1; }
        if (t2[1] == y[i + 1] && d[i][1]) { d[i][2] = 1; }
    }

    if (d[n - 2][2] == 1) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}