#include <iostream>
#include <vector>

using namespace std;

const int INF = 1e7;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int r, c, n;
    vector<vector<int>> map, ans;
    cin >> r >> c >> n;
    map.resize(r); ans.resize(r);
    for (int i = 0; i < r; i++) { map[i].resize(c); ans[i].resize(c); }
    for (int i = 0; i < n; i++) {
        int y, x, f;
        cin >> y >> x >> f;
        map[y - 1][x - 1] = f;
    }

    for (int i = r - 1; i >= 0; i--) {
        for (int j = c - 1; j >= 0; j--) {
            if (i == r - 1 && j == c - 1) { continue; }
            ans[i][j] = INF;
            if (i < r - 1) { ans[i][j] = min(ans[i][j], ans[i + 1][j] + 1); }
            if (j < c - 1) { ans[i][j] = min(ans[i][j], ans[i][j + 1] + 1); }
            ans[i][j] = max(0, ans[i][j] - map[i][j]);
        }
    }

    cout << ans[0][0] << "\n";
}