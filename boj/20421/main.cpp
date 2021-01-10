#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

using state = tuple<int, int, int, int>;

inline int dir(char x) {
    int ans = 0;
    if (x == 'R') { ans = 0; }
    if (x == 'D') { ans = 1; }
    if (x == 'L') { ans = 2; }
    if (x == 'U') { ans = 3; }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int r, c, k;
    cin >> r >> c >> k;
    vector<vector<char>> maze;
    maze.resize(r + 1);
    for (int i = 1; i <= r; i++) {
        maze[i].resize(c + 1);
        for (int j = 1; j <= c; j++) {
            cin >> maze[i][j];
        }
    }

    int dy[4] = { 0, 1, 0, -1 }, dx[4] = { 1, 0, -1, 0 };
    auto cmp = [](state left, state right) { return get<3>(left) > get<3>(right); };
    priority_queue<state, vector<state>, decltype(cmp)> pq(cmp);
    vector<vector<vector<int>>> ans, visited;
    int flag = 0;
    ans.resize(r + 1); visited.resize(r + 1);
    for (int i = 1; i <= r; i++) {
        ans[i].resize(c + 1); visited[i].resize(c + 1);
        for (int j = 1; j <= c; j++) {
            ans[i][j].resize(k + 1); visited[i][j].resize(k + 1);
        }
    }
    pq.push({ 1, 1, 0, 0 });
    while (!pq.empty()) {
        auto [ y, x, left, cost ] = pq.top();
        pq.pop();
        if (cost > k) { break; }
        if (visited[y][x][left]) { continue; }
        visited[y][x][left] = 1;
        ans[y][x][left] = cost;
        if (y == r && x == c) { flag = 1; break; }

        int dir_id = dir(maze[y][x]);
        for (int i = 0; i < 4; i++) {
            int ty = y + dy[(dir_id - i + 4) % 4], tx = x + dx[(dir_id - i + 4) % 4];
            if (ty <= 0 || tx <= 0 || ty > r || tx > c || left + i > k) { continue; }
            if (visited[ty][tx][left + i]) { continue; }
            pq.push({ ty, tx, left + i, cost });
        }
        for (int i = 0; i < 4; i++) {
            int ty = y + dy[(dir_id + i) % 4], tx = x + dx[(dir_id + i) % 4];
            if (ty <= 0 || tx <= 0 || ty > r || tx > c) { continue; }
            if (visited[ty][tx][left]) { continue; }
            pq.push({ ty, tx, left, cost + i });
        }
    }

    if (flag) { cout << "Yes\n"; }
    else { cout << "No\n"; }
}