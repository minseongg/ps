#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;
using vvpii = vector<vector<pii>>;

vi dijkstra(int v, int s, vvpii &e) {
    auto cmp = [](pii left, pii right) { return left.second > right.second; };
    priority_queue<pii, vector<pii>, decltype(cmp)> pq(cmp);
    vi ans(v), visited(v);
    pq.push({ s, 0 });
    while (!pq.empty()) {
        auto [ now, cost ] = pq.top();
        pq.pop();
        if (visited[now]) { continue; }
        visited[now] = 1;
        ans[now] = cost;
        for (auto &[ to, to_cost ] : e[now]) {
            if (visited[to]) { continue; }
            pq.push({ to, cost + to_cost });
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);

    int n, m, x, y;
    cin >> n >> m >> x >> y;

    vvpii e(n);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        e[a].emplace_back(b, c);
        e[b].emplace_back(a, c);
    }

    auto d = dijkstra(n, y, e);

    int t = 0, ans = 0;

    sort(d.begin(), d.end());
    for (int i = 1; i < n; i++) {
        if (d[i] == 0) {
            cout << "-1\n";
            return 0;
        }

        if (t + d[i] * 2 > x) {
            ans++;
            t = 0;
            if (d[i] * 2 > x) {
                cout << "-1\n";
                return 0;
            }
        }

        t += d[i] * 2;
    }

    cout << ans + 1 << "\n";
    return 0;
}
