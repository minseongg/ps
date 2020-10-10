#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m, ans = 0;
    vector<vector<int>> v;

    cin >> n >> m;
    v.resize(n);

    for (int i = 0; i < n; i++) {
        v[i].resize(m);

        for (int j = 0; j < m; j++) {
            cin >> v[i][j];
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
            for (int k = j + 1; k < m; k++) {
                int t = 0;

                for (int l = 0; l < n; l++) {
                    t += max(max(v[l][i], v[l][j]), v[l][k]);
                }

                ans = max(ans, t);
            }
        }
    }

    cout << ans << "\n";

    return 0;
}