#include <iostream>
#include <vector>

using namespace std;

const int MAXM = 50;

void dfs(vector<vector<int>> &v, vector<vector<int>> &visited, int y, int x) {
    int dy[4] = { 0, -1, 0, 1 }, dx[4] = { -1, 0, 1, 0 };
    visited[y][x] = 1;
    for (int i = 0; i < 4; i++) {
        int ty = y + dy[i], tx = x + dx[i];
        if (v[ty][tx] && !visited[ty][tx]) {
            dfs(v, visited, ty, tx);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int m, n, k, ans = 0;
        vector<vector<int>> v, visited;
        cin >> m >> n >> k;
        v.resize(n + 2); visited.resize(n + 2);
        for (int i = 0; i <= n + 1; i++) { v[i].resize(m + 2); visited[i].resize(m + 2); }
        for (int i = 0; i < k; i++) {
            int x, y;
            cin >> x >> y;
            v[y + 1][x + 1] = 1;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (v[i][j] && !visited[i][j]) {
                    dfs(v, visited, i, j);
                    ans++;
                }
            }
        }
        cout << ans << "\n";
    }
}