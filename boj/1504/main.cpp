#include <iostream>
#include <vector>
#include <queue>

using namespace std;

using pii = pair<int, int>;
using vpii = vector<pii>;
using vvpii = vector<vpii>;
using vi = vector<int>;

const int MAXN = 800;
const int INF = 1e9;

void dijkstra(vvpii &edge, int s, vi &v) {
    auto cmp = [](pii a, pii b) { return a.second > b.second; };

    priority_queue<pii, vector<pii>, decltype(cmp)> pq(cmp);
    vi visit;
    int sz = (int)v.size();

    visit.resize(sz);
    for (int i = 0; i < sz; i++) v[i] = INF;
    v[s] = 0;
    pq.push({s, 0});

    while (!pq.empty()) {
        pii top = pq.top();
        int n = top.first, c = top.second;

        pq.pop();

        if (visit[n]) continue;
        visit[n] = 1;

        for (pii t: edge[n]) {
            int tn = t.first, tc = t.second;

            if (visit[tn]) continue;
            if (c + tc < v[tn]) {
                v[tn] = c + tc;
                pq.push({tn, v[tn]});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);

    int n, e, ans = INF, v, w;
    vvpii edge;
    vi dv, dw;

    cin >> n >> e;
    edge.resize(n);
    for (int i = 0; i < e; i++) {
        int a, b, c;

        cin >> a >> b >> c;
        edge[a - 1].push_back({b - 1, c});
        edge[b - 1].push_back({a - 1, c});
    }

    cin >> v >> w;
    v--; w--;
    dv.resize(n);
    dw.resize(n);

    dijkstra(edge, v, dv);
    dijkstra(edge, w, dw);

    if (dv[0] != INF && dv[w] != INF && dw[n - 1] != INF) ans = min(ans, dv[0] + dv[w] + dw[n - 1]);
    if (dw[0] != INF && dw[v] != INF && dv[n - 1] != INF) ans = min(ans, dw[0] + dw[v] + dv[n - 1]);

    ans = (ans == INF) ? -1 : ans;

    cout << ans << "\n";
}