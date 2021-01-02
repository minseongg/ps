#include <iostream>
#include <vector>
#include <queue>

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
    cin.tie(0);
    int n, m;
    vvpii e;
    cin >> n >> m;
    e.resize(n);
    for (int i = 0; i < m; i++) {
        int x, y, c;
        cin >> x >> y >> c;
        e[x - 1].emplace_back(y - 1, c);
    }
    int s, d;
    cin >> s >> d;
    auto ans = dijkstra(n, s - 1, e);
    cout << ans[d - 1] << "\n";
}