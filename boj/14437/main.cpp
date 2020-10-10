#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MOD = 1e9 + 7;

inline int add(int a, int b) {
    return (a + b) % MOD;
}

inline int sub(int a, int b) {
    return (a - b + MOD) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    vector<vector<int>> d;

    int n, m;
    string s;

    cin >> n;
    cin >> s;

    m = (int)s.size();

    d.resize(m);
    for (int i = 0; i < m; i++) {
        d[i].resize(n + 1);
    }

    for (int j = 0; j < min(26, n + 1); j++) {
        d[0][j] = 1;
    }

    for (int i = 1; i < m; i++) {
        d[i][0] = d[i - 1][0];

        for (int j = 1; j < min(26, n + 1); j++) {
            d[i][j] = add(d[i][j - 1], d[i - 1][j]);
        }

        for (int j = 26; j < n + 1; j++) {
            d[i][j] = add(sub(d[i][j - 1], d[i - 1][j - 26]), d[i - 1][j]);
        }
    }

    cout << d[m - 1][n] << "\n";
}