#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

const int MAXM = 35;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    vector<vector<ll>> v;
    v.resize(MAXM);
    for (int i = 1; i < MAXM; i++) { v[i].resize(MAXM); }
    v[1][0] = 1;
    v[1][1] = 1;
    for (int i = 2; i < MAXM; i++) {
        v[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            v[i][j] = v[i - 1][j - 1] + v[i - 1][j];
        }
    }

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        cout << v[m][n] << "\n";
    }
}