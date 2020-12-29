#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> scc_get_rev_e(int v, vector<vector<int>> &e) {
    vector<vector<int>> rev_e(v);
    for (int x = 0; x < v; x++) {
        for (int &y : e[x]) {
            rev_e[y].emplace_back(x);
        }
    }
    return rev_e;
}

void scc_dfs(int now, vector<vector<int>> &e, vector<int> &visited, vector<int> &order) {
    visited[now] = 1;
    for (int x : e[now]) {
        if (visited[x]) { continue; }
        scc_dfs(x, e, visited, order);
    }
    order.emplace_back(now);
}

void scc_dfs_rev(int now, vector<vector<int>> &e, vector<int> &visited, vector<int> &ans) {
    visited[now] = 1;
    ans.emplace_back(now);
    for (int x : e[now]) {
        if (visited[x]) { continue; }
        scc_dfs_rev(x, e, visited, ans);
    }
}

vector<vector<int>> scc(int v, vector<vector<int>> &e) {
    vector<int> visited(v), rev_visited(v), order;
    vector<vector<int>> rev_e = scc_get_rev_e(v, e);
    vector<vector<int>> ans;
    
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

    int v, e;
    vector<vector<int>> adj;

    cin >> v >> e;
    adj.resize(v);
    for (int i = 0; i < e; i++) {
        int x, y;
        cin >> x >> y;
        adj[x - 1].emplace_back(y - 1);
    }

    auto ans = scc(v, adj);
    vector<int> idx(v), visited(ans.size());
    
    for (int i = 0; i < (int)ans.size(); i++) {
        for (int &x : ans[i]) {
            idx[x] = i;
        }
    }

    cout << ans.size() << "\n";
    for (int i = 0; i < v; i++) {
        if (visited[idx[i]]) { continue; }
        visited[idx[i]] = 1;
        sort(ans[idx[i]].begin(), ans[idx[i]].end());
        for (int &x : ans[idx[i]]) {
            cout << x + 1 << " ";
        }
        cout << "-1\n";
    }
}