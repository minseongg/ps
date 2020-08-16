#include <iostream>
#include <vector>

using namespace std;

void dfs(int now, int par, vector<vector<int>> &c, vector<vector<int>> &e, vector<int> &d, vector<int> &f, vector<int> &s, vector<int> &a) {
    for (int ch : e[now]) {
        if (ch == par) { continue; }

        if (!d[ch]) {
            c[now].emplace_back(ch);
            d[ch] = d[now] + 1;

            int fnow = f[now];

            dfs(ch, now, c, e, d, f, s, a);

            a[ch] = f[now] - fnow;
            f[now] += f[ch];
            s[now] += s[ch];
        } else if (d[ch] < d[now]) {
            f[ch]++;
            s[now]++;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    long long ans = 0;
    int n, m;
    vector<vector<int>> e, c;
    vector<int> d, f, s, a;

    cin >> n >> m;

    e.resize(n + 1);
    c.resize(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v;

        cin >> u >> v;
        
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }
    
    d.resize(n + 1);
    f.resize(n + 1);
    s.resize(n + 1);
    a.resize(n + 1);

    d[1] = 1;
    dfs(1, -1, c, e, d, f, s, a);

    for (int i = 1; i <= n; i++) {
        bool flag = true;

        for (int ch : c[i]) {
            if (f[ch] || s[ch] - a[ch] >= 2) {
                flag = false;
            }
        }

        if (m - n + 1 - s[i]) { flag = false; }

        if (flag) { ans += (long long)i; }
    }
    
    cout << ans << "\n";
}
