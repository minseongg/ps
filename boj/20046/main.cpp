#include <iostream>
#include <queue>
#include <vector>

using namespace std;

using pii = pair<int, int>;
using state = pair<pii, int>;

inline bool valid(int y, int x, int m, int n, vector<vector<int>> &v, vector<vector<int>> &visited) {
    if (y < 0 || y >= m) { return false; }
    if (x < 0 || x >= n) { return false; }
    if (v[y][x] == -1 || visited[y][x]) { return false; }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int m, n;
    vector<vector<int>> v, visited;

    cin >> m >> n;
    v.resize(m); visited.resize(m);
    for (int i = 0; i < m; i++) {
        v[i].resize(n); visited[i].resize(n);
        for (int j = 0; j < n; j++) {
            cin >> v[i][j];
        }
    }

    if (v[0][0] == -1) {
        cout << "-1\n";
        return 0;
    }

    auto cmp = [](state x, state y) { return x.second > y.second; };
    priority_queue<state, vector<state>, decltype(cmp)> pq(cmp);

    pq.push({ { 0, 0 }, v[0][0] });
    while (!pq.empty()) {
        state top = pq.top();
        int ty = top.first.first, tx = top.first.second, tc = top.second;
        visited[ty][tx] = 1;
        pq.pop();

        if (ty == m - 1 && tx == n - 1) {
            cout << tc << "\n";
            return 0;
        }

        if (valid(ty - 1, tx, m, n, v, visited)) { pq.push({ { ty - 1, tx }, tc + v[ty - 1][tx] }); }
        if (valid(ty, tx - 1, m, n, v, visited)) { pq.push({ { ty, tx - 1 }, tc + v[ty][tx - 1] }); }
        if (valid(ty + 1, tx, m, n, v, visited)) { pq.push({ { ty + 1, tx }, tc + v[ty + 1][tx] }); }
        if (valid(ty, tx + 1, m, n, v, visited)) { pq.push({ { ty, tx + 1 }, tc + v[ty][tx + 1] }); }
    }

    cout << "-1\n";
}