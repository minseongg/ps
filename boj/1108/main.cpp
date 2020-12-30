#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using ll = long long;
using vll = vector<ll>;

const int MAXN = 2550;

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

vi topological_sort(int v, vvi &e) {
    vi ans, in(v);
    for (int x = 0; x < v; x++) {
        for (int &y : e[x]) {
            in[y]++;
        }
    }

    for (int x = 0; x < v; x++) {
        if (!in[x]) {
            ans.emplace_back(x);
        }
    }

    for (int i = 0; i < v; i++) {
        int x = ans[i];
        for (int &y : e[x]) {
            in[y]--;
            if (!in[y]) {
                ans.emplace_back(y);
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    map<string, int> name_to_id;
    map<int, string> id_to_name;
    vvi e(MAXN), rev_e(MAXN);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s;
        int m;
        cin >> s >> m;
        if (name_to_id.find(s) == name_to_id.end()) {
            name_to_id[s] = name_to_id.size();
            id_to_name[name_to_id[s]] = s;
        }
        for (int j = 0; j < m; j++) {
            string t;
            cin >> t;
            if (name_to_id.find(t) == name_to_id.end()) {
                name_to_id[t] = name_to_id.size();
                id_to_name[name_to_id[t]] = t;
            }
            e[name_to_id[t]].emplace_back(name_to_id[s]);
            rev_e[name_to_id[s]].emplace_back(name_to_id[t]);
        }
    }

    map<string, int> name_to_comp_id;
    int v = (int)name_to_id.size();
    vvi comps = scc(v, e);
    for (int i = 0; i < (int)comps.size(); i++) {
        for (int &x : comps[i]) {
            name_to_comp_id[id_to_name[x]] = i;
        }
    }

    int comp_v = (int)comps.size();
    vvi comp_e_adj(comp_v);
    vvi comp_e(comp_v);
    for (int i = 0; i < comp_v; i++) {
        comp_e_adj[i].resize(comp_v);
    }

    for (int x = 0; x < v; x++) {
        for (int &y : e[x]) {
            comp_e_adj[name_to_comp_id[id_to_name[x]]][name_to_comp_id[id_to_name[y]]] = 1;
        }
    }

    for (int x = 0; x < comp_v; x++) {
        for (int y = 0; y < comp_v; y++) {
            if (x == y) { continue; }
            if (comp_e_adj[x][y]) {
                comp_e[x].emplace_back(y);
            }
        }
    }

    vll ans(v);
    vi order = topological_sort(comp_v, comp_e);
    for (int &i : order) {
        for (int &x : comps[i]) {
            ans[x] = 1;
            for (int &y : rev_e[x]) {
                if (name_to_comp_id[id_to_name[x]] == name_to_comp_id[id_to_name[y]]) { continue; }
                ans[x] += ans[y];
            }
        }
    }

    string a;
    cin >> a;
    cout << ans[name_to_id[a]] << "\n";
}