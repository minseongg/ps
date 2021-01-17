#include <iostream>
#include <vector>

using namespace std;

const int LG = 18;

void dfs(int x, int p, vector<vector<int>> &e, vector<vector<int>> &par, vector<int> &lev, vector<vector<int>> &sc, vector<int> &c) {
    par[x][0] = p == -1 ? x : p;
    for (int i = 1; i < LG; i++) { par[x][i] = par[par[x][i - 1]][i - 1]; }
    for (int i = 0; i < 5; i++) { sc[x][i] = sc[par[x][0]][i]; }
    sc[x][c[x]]++;
    for (int y : e[x]) {
        if (y == p) { continue; }
        lev[y] = lev[x] + 1;
        dfs(y, x, e, par, lev, sc, c);
    }
}

int lca(int x, int y, vector<vector<int>> &par, vector<int> &lev) {
    int tx = x, ty = y;
    if (lev[tx] > lev[ty]) { swap(tx, ty); }
    
    int t = lev[ty] - lev[tx];
    for (int i = LG - 1; i >= 0; i--) {
        if ((1 << i) <= t) {
            ty = par[ty][i];
            t -= (1 << i);
        }
    }

    if (tx == ty) { return tx; }
    if (par[tx][0] == par[ty][0]) { return par[tx][0]; }
    for (int i = LG - 1; i >= 0; i--) {
        if (par[tx][i] != par[ty][i]) {
            tx = par[tx][i];
            ty = par[ty][i];
        }
    }
    return par[tx][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, cnt[5] = { 0 };
    vector<int> c, lev;
    vector<vector<int>> e, par, sc;

    cin >> n;
    c.resize(n); lev.resize(n); e.resize(n); par.resize(n); sc.resize(n);
    for (int i = 0; i < n; i++) { par[i].resize(LG); sc[i].resize(5); }
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        c[i]--;
        cnt[c[i]]++;
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        e[u - 1].emplace_back(v - 1);
        e[v - 1].emplace_back(u - 1);
    }
    dfs(0, -1, e, par, lev, sc, c);
    cin >> m;
    
    int it = 0;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        if (i == 0) {
            if (cnt[y]) {
                cout << "PLAY\n";
            } else {
                cout << "CRY\n";
            }
        } else {
            int p = lca(it, x, par, lev);
            int t = sc[it][y] + sc[x][y] - sc[p][y] - (p ? sc[par[p][0]][y] : 0);
            if (t) {
                cout << "PLAY\n";
            } else {
                cout << "CRY\n";
            }
        }
        it = x;
    }
}
