#include <iostream>

using namespace std;

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

int solve(int now, vvi &e, vi &d, vi &visited, vi &c, vi &dests) {
    if (visited[now]) { return d[now]; }
    visited[now] = 1;
    int ans = dests[now] ? c[now] : -1;
    for (int &to : e[now]) {
        int t = solve(to, e, d, visited, c, dests);
        if (t == -1) { continue; }
        ans = max(ans, t + c[now]);
    }
    return d[now] = ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, s, p;
    vvi e, comp_e;
    vi c, comp_map, comp_c, dests, comp_dests;
    cin >> n >> m;
    e.resize(n);
    c.resize(n);
    comp_map.resize(n);
    dests.resize(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        e[x - 1].emplace_back(y - 1);
    }
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    cin >> s >> p;
    for (int i = 0; i < p; i++) {
        int x;
        cin >> x;
        dests[x - 1] = 1;
    }
    auto comps = scc(n, e);
    for (int i = 0; i < (int)comps.size(); i++) {
        for (int &x : comps[i]) {
            comp_map[x] = i;
        }
    }
    comp_c.resize((int)comps.size());
    comp_dests.resize((int)comps.size());
    for (int i = 0; i < n; i++) {
        comp_c[comp_map[i]] += c[i];
        comp_dests[comp_map[i]] = max(comp_dests[comp_map[i]], dests[i]);
    }
    comp_e.resize((int)comps.size());
    for (int x = 0; x < n; x++) {
        for (int &y : e[x]) {
            if (comp_map[x] == comp_map[y]) { continue; }
            comp_e[comp_map[x]].emplace_back(comp_map[y]);
        }
    }
    vi d((int)comps.size()), visited((int)comps.size());
    cout << solve(comp_map[s - 1], comp_e, d, visited, comp_c, comp_dests) << "\n";
}