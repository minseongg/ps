#include <iostream>

using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

const int MAX_AREA = 4500;

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

void topological_sort_dfs(int now, vvi &e, vi &visited, vi &order) {
    visited[now] = 1;
    for (int &to : e[now]) {
        if (visited[to]) { continue; }
        topological_sort_dfs(to, e, visited, order);
    }
    order.emplace_back(now);
}

vi topological_sort(int v, vvi &e) {
    vi visited(v), order;
    for (int i = 0; i < v; i++) {
        if (!visited[i]) {
            topological_sort_dfs(i, e, visited, order);
        }
    }
    reverse(order.begin(), order.end());
    return order;
}

bool two_sat(int v, vector<pair<int, int>> clauses) {
    vvi e(v << 1);
    for (auto &[ v1, v2 ] : clauses) {
        int mod_v1 = (v1 < 0 ? -v1 - 1 + v : v1 - 1);
        int mod_v2 = (v2 < 0 ? -v2 - 1 + v : v2 - 1);
        e[(mod_v1 + v) % (v << 1)].emplace_back(mod_v2);
        e[(mod_v2 + v) % (v << 1)].emplace_back(mod_v1);
    }
    auto comps = scc(v << 1, e);
    vi comp_map(v << 1);
    for (int i = 0; i < (int)comps.size(); i++) {
        for (int &x : comps[i]) {
            comp_map[x] = i;
        }
    }
    for (int x = 0; x < v; x++) {
        if (comp_map[x] == comp_map[x + v]) {
            return false;
        }
    }
    return true;
}

bool is_cross(
    int lx1, int ly1, int ux1, int uy1,
    int lx2, int ly2, int ux2, int uy2
) {
    return !(
        ux1 <= lx2 ||
        ux2 <= lx1 ||
        uy1 <= ly2 ||
        uy2 <= ly1
    );
}

int main() {
    ios::sync_with_stdio(false);

    int n;
    vector<int> m, s;
    vector<int> lx, ly, ux, uy;
    vector<pair<int, int>> clauses;

    cin >> n;
    m.resize(n);
    s.resize(n);
    lx.resize(MAX_AREA);
    ly.resize(MAX_AREA);
    ux.resize(MAX_AREA);
    uy.resize(MAX_AREA);
    for (int i = 0; i < n; i++) {
        cin >> m[i];
        if (i) { s[i] = s[i - 1] + m[i - 1]; }
        for (int j = 0; j < m[i]; j++) {
            for (int k = j + 1; k < m[i]; k++) {
                clauses.emplace_back(-(s[i]+j+1), -(s[i]+k+1));
            }
        }
        for (int j = s[i]; j < s[i] + m[i]; j++) {
            cin >> lx[j] >> ly[j] >> ux[j] >> uy[j];
            for (int k = 0; k < s[i]; k++) {
                if (is_cross(
                    lx[k], ly[k], ux[k], uy[k],
                    lx[j], ly[j], ux[j], uy[j]
                )) {
                    clauses.emplace_back(k+1, j+1);
                }
            }
        }
    }

    auto is_avail = two_sat(s[n-1]+m[n-1], clauses);
    if (is_avail) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}
