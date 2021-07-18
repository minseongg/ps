#include <iostream>
#include <vector>
#include <queue>

using namespace std;

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using edge = pair<int, pair<ll, ll>>;
using state = pair<pair<int, int>, ll>;
using edge_mat = vector<vector<edge>>;

const ll INF = 1e9;

vl dijkstra(int v, int s, edge_mat &e) {
    auto cmp = [](state left, state right) { return left.second > right.second; };
    priority_queue<state, vector<state>, decltype(cmp)> pq(cmp);
    vl ans(v << 1);
    vi visited(v << 1);
    pq.push({ { s, 0 }, 0 });
    while (!pq.empty()) {
        auto [ now_state, cost ] = pq.top();
        int now = now_state.first, eaten = now_state.second;
        pq.pop();
        if (visited[now * 2 + eaten]) { continue; }
        visited[now * 2 + eaten] = 1;
        ans[now * 2 + eaten] = cost;

        for (auto &[ to, to_state ] : e[now]) {
            ll to_cost = to_state.first, to_flavor = to_state.second;
            if (eaten) {
                if (!visited[to * 2 + 1]) {
                    pq.push({ { to, 1 }, cost + to_cost });
                }
            } else {
                if (!visited[to * 2]) {
                    pq.push({ { to, 0 }, cost + to_cost });
                }
                if (!visited[to * 2 + 1]) {
                    pq.push({ { to, 1 }, cost + to_cost + INF - to_flavor });
                }
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);

    int v, e;
    edge_mat edges;
    
    cin >> v >> e;
    edges.resize(v);
    for (int i = 0; i < e; i++) {
        int x, y, t, k;
        cin >> x >> y >> t >> k;
        x--; y--;
        edges[x].push_back({ y, { t, k } });
        edges[y].push_back({ x, { t, k } });
    }

    auto ans = dijkstra(v, 0, edges);
    
    for (int i = 1; i < v; i++) {
        cout << min(ans[i * 2], ans[i * 2 + 1] - INF) << "\n";
    }
}
