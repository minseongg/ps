#include <iostream>
#include <vector>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

vvi scc_get_rev_e(int v, vvi &e) {
    vvi rev_e(v);
    for (int x = 0; x < v; x++) {
        for (int &y : e[x]) {
            rev_e[y].emplace_back(x);
        }
    }
    return rev_e;
}

void scc_dfs(int now, vvi &e, vi &visited, vi &order) {
    visited[now] = 1;
    for (int x : e[now]) {
        if (visited[x]) { continue; }
        scc_dfs(x, e, visited, order);
    }
    order.emplace_back(now);
}

void scc_dfs_rev(int now, vvi &e, vi &visited, vi &ans) {
    visited[now] = 1;
    ans.emplace_back(now);
    for (int x : e[now]) {
        if (visited[x]) { continue; }
        scc_dfs_rev(x, e, visited, ans);
    }
}

vvi scc(int v, vvi &e) {
    vi visited(v), rev_visited(v), order;
    vvi rev_e = scc_get_rev_e(v, e);
    vvi ans;
    
    for (int i = 0; i < v; i++) {
        if (visited[i]) { continue; }
        scc_dfs(i, e, visited, order);
    }

    for (int i = v - 1; i >= 0; i--) {
        if (rev_visited[order[i]]) { continue; }
        ans.push_back({});
        scc_dfs_rev(order[i], rev_e, rev_visited, ans[ans.size() - 1]);
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        vvi e;
        cin >> n >> m;
        e.resize(n);
        for (int i = 0; i < m; i++) {
            int x, y;
            cin >> x >> y;
            e[x - 1].emplace_back(y - 1);
        }
        auto comps = scc(n, e);
        vi comp_map(n), in(n);
        int ans = 0;
        for (int i = 0; i < (int)comps.size(); i++) {
            for (int &x : comps[i]) {
                comp_map[x] = i;
            }
        }
        for (int x = 0; x < n; x++) {
            for (int &y : e[x]) {
                if (comp_map[x] == comp_map[y]) { continue; }
                in[comp_map[y]]++;
            }
        }
        for (int i = 0; i < (int)comps.size(); i++) {
            if (in[i] == 0) {
                ans++;
            }
        }
        cout << ans << "\n";
    }
}