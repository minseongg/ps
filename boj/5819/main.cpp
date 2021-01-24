#include <iostream>
#include <vector>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

void dfs(int now, vi &visited, vvi &e, vi &lev, int &is_cycle, int &cycle_p) {
    visited[now] = 1;
    for (int &to : e[now]) {
        if (visited[to] == 1) {
            is_cycle = 1;
            cycle_p = lev[now] + 1;
        } else {
            lev[to] = lev[now] + 1;
            dfs(to, visited, e, lev, is_cycle, cycle_p);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, p;
    vvi adj;
    cin >> n >> m >> p;
    adj.resize(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        if (adj[x].size() < 2) { adj[x].emplace_back(y); }
        if (adj[y].size() < 2) { adj[y].emplace_back(x); }
    }

    vvi e(n << 1);
    vi visited_1(n << 1), lev_1(n << 1), visited_2(n << 1), lev_2(n << 1);
    int is_cycle_1 = 0, cycle_p_1, is_cycle_2 = 0, cycle_p_2;

    for (int i = 0; i < n; i++) {
        if (adj[i].size() == 1) {
            int a = i, b = adj[i][0];
            if (adj[b][0] == a) {
                e[n + b].emplace_back(a);
                e[n + b].emplace_back(n + a);
            } else {
                e[b].emplace_back(a);
                e[b].emplace_back(n + a);
            }
        } else if (adj[i].size() == 2) {
            int a = i, b = adj[i][0], c = adj[i][1];
            if (adj[b][0] == a) {
                e[n + b].emplace_back(a);
            } else {
                e[b].emplace_back(a);
            }
            if (adj[c][0] == a) {
                e[n + c].emplace_back(n + a);
            } else {
                e[c].emplace_back(n + a);
            }
        }
    }

    dfs(p, visited_1, e, lev_1, is_cycle_1, cycle_p_1);
    dfs(n + p, visited_2, e, lev_2, is_cycle_2, cycle_p_2);

    int q;
    cin >> q;
    while (q--) {
        int g, ans = 0;
        cin >> g;
        for (int i = 0; i < n; i++) {
            if (visited_1[i] && (lev_1[i] == g || (is_cycle_1 && g > lev_1[i] && (g - lev_1[i]) % cycle_p_1 == 0))) { ans++; }
            if (visited_2[i] && (lev_2[i] == g || (is_cycle_2 && g > lev_2[i] && (g - lev_2[i]) % cycle_p_2 == 0))) { ans++; }
        }
        cout << ans << "\n";
    }
}