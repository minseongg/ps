#include <iostream>
#include <vector>
#include <queue>

using ll = long long;

using namespace std;

int get_parent(int now, vector<vector<int>> &e, vector<int> &visited) {
    for (int x : e[now]) {
        if (!visited[x]) { return x; }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    ll ans = 0;
    vector<int> w, d, visited;
    vector<vector<int>> e;
    priority_queue<pair<int, int>> pq;

    cin >> n >> m;

    w.resize(n);
    d.resize(n);
    visited.resize(n);
    e.resize(n);

    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }
    
    for (int i = 0; i < m; i++) {
        int x, y;

        cin >> x >> y;

        e[x - 1].emplace_back(y - 1);
        e[y - 1].emplace_back(x - 1);

        d[x - 1]++;
        d[y - 1]++;
    }

    for (int i = 0; i < n; i++) {
        if (d[i] == 1) {
            pq.push({i, w[i]});
        }
    }

    while (!pq.empty()) {
        auto top = pq.top();
        int now = top.first;

        pq.pop();

        int par = get_parent(now, e, visited);

        d[now]--;
        d[par]--;

        if (w[now]) {
            ans += (ll)w[now];

            w[par] = max(0, w[par] - w[now]);

            for (int x : e[par]) {
                w[x] = max(0, w[x] - w[now]);
            }
        }

        if (d[par] == 1) {
            pq.push({par, w[par]});
        }
    }

    cout << ans << "\n";
}