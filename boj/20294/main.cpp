#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    vector<tuple<int, int, int>> room;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        room.push_back({ x, y, z });
    }

    int ans = 0;
    vector<int> d(n);
    vector<vector<int>> flow((n << 1) + 2), e((n << 1) + 2);
    for (int i = 0; i < (n << 1) + 2; i++) { flow[i].resize((n << 1) + 2); }
    for (int i = 0; i < n; i++) {
        auto &[ x, y, z ] = room[i];
        if ((abs(x) + abs(y) + abs(z)) % 2 == 0) {
            flow[0][i + 1]++;
            e[0].emplace_back(i + 1);
            e[i + 1].emplace_back(0);
            for (int j = 0; j < n; j++) {
                auto &[ tx, ty, tz ] = room[j];
                if (abs(x - tx) + abs(y - ty) + abs(z - tz) == 1) {
                    flow[i + 1][n + j + 1]++;
                    d[i]++;
                    d[j]++;
                    e[i + 1].emplace_back(n + j + 1);
                    e[n + j + 1].emplace_back(i + 1);
                }
            }
        } else {
            flow[n + i + 1][(n << 1) + 1]++;
            e[n + i + 1].emplace_back((n << 1) + 1);
            e[(n << 1) + 1].emplace_back(n + i + 1);
        }
    }

    for (int i = 0; i < n; i++) {
        if (d[i] == 0) {
            ans++;
        }
    }

    while (true) {
        vector<int> visited((n << 1) + 2), parent((n << 1) + 2);
        int flag = 0;
        queue<int> q;
        q.push(0);
        visited[0] = 1;
        while (!q.empty()) {
            int f = q.front();
            q.pop();
            if (f == (n << 1) + 1) { flag = 1; ans++; break; }
            for (int x : e[f]) {
                if (flow[f][x] && !visited[x]) {
                    q.push(x);
                    parent[x] = f;
                    visited[x] = 1;
                }
            }
        }

        if (flag == 0) { break; }
        int now = (n << 1) + 1;
        while (now) {
            flow[parent[now]][now]--;
            flow[now][parent[now]]++;
            now = parent[now];
        }
    }

    cout << ans << "\n";
}
