#include <iostream>
#include <vector>

using namespace std;

const int INF = 0x7fffffff;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, ans = -INF;
    vector<vector<int>> v, s;
    cin >> n;
    v.resize(n); s.resize(n);
    for (int i = 0; i < n; i++) {
        v[i].resize(n); s[i].resize(n);
        for (int j = 0; j < n; j++) {
            cin >> v[i][j];
            s[i][j] = (i ? s[i - 1][j] : 0) + (j ? s[i][j - 1] : 0) - (i && j ? s[i - 1][j - 1] : 0) + v[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k <= min(i, j); k++) {
                int uy = i - k, dy = i, lx = j - k, rx = j;

                ans = max(ans, s[dy][rx] - (uy ? s[uy - 1][rx] : 0) - (lx ? s[dy][lx - 1] : 0) + (uy && lx ? s[uy - 1][lx - 1] : 0));
            }
        }
    }

    cout << ans << "\n";
}
