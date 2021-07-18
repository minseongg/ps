#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

inline int uf_par(int now, vector<int> &par) {
    return par[now] == now ? now : par[now] = uf_par(par[now], par);
}

inline void uf_merge(int x, int y, vector<int> &par, vector<int> &lev) {
    if (lev[x] < lev[y]) {
        par[x] = y;
    } else {
        if (lev[y] > lev[x]) {
            par[y] = x;
        } else {
            par[y] = x;
            lev[x]++;
        }
    }
}

// first: local, second: longest
pair<int, int> dfs(int par, int now, vector<vector<pair<int, int>>> &e) {
    vector<int> paths;
    int local = 0, longest = 0;
    
    for (auto [to, cost]: e[now]) {
        if (to == par) { continue; }
        
        auto [c_local, c_longest] = dfs(now, to, e);
        local = max(local, c_local);
        longest = max(longest, c_longest + cost);
        paths.emplace_back(c_longest + cost);
    }

    sort(paths.begin(), paths.end());
    if (paths.size() >= 2) {
        local = max(local, paths[paths.size() - 1] + paths[paths.size() - 2]);
    } else if (paths.size() >= 1) {
        local = max(local, paths[paths.size() - 1]);
    }

    return {local, longest};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, k, ans_cost = 0;
    vector<int> par, lev;
    vector<pair<int, pair<int, int>>> e;

    cin >> n >> k;
    for (int i = 0; i < k; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        e.push_back({c, {a, b}});
    }
    sort(e.begin(), e.end());

    par.resize(n); lev.resize(n);
    for (int i = 0; i < n; i++) {
        par[i] = i;
    }

    vector<vector<pair<int, int>>> e_mst(n);

    for (auto &[c, t]: e) {
        auto &[a, b] = t;
        int uf_par_a = uf_par(a, par);
        int uf_par_b = uf_par(b, par);
        if (uf_par_a == uf_par_b) {
            continue;
        }

        ans_cost += c;
        uf_merge(uf_par_a, uf_par_b, par, lev);
        e_mst[a].emplace_back(b, c);
        e_mst[b].emplace_back(a, c);
    }

    cout << ans_cost << "\n";
    cout << dfs(-1, 0, e_mst).first << "\n";
}
