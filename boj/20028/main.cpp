#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

using ll = long long;

class Point {
public:
    int c, idx;

    Point() : c(0), idx(0) {}
};

inline bool cmp(const Point &a, const Point &b) {
    return a.c > b.c;
}

void dfs(int now, vector<vector<int>> &e, vector<int> *visited, int value, vector<int> &d, int parity) {
    visited[parity][now] = 1;
    if (parity == 0) { d[now] = value; }

    for (int x : e[now]) {
        if (visited[parity^1][x]) { continue; }
        dfs(x, e, visited, value, d, parity^1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    vector<int> c, visited[2], d;
    vector<vector<int>> e;
    vector<Point> ord;
    
    cin >> n >> m;
    c.resize(n); e.resize(n); ord.resize(n); visited[0].resize(n); visited[1].resize(n); d.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        ord[i].c = c[i];
        ord[i].idx = i;
    }
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y; x--; y--;
        e[x].emplace_back(y);
        e[y].emplace_back(x);
    }

    sort(ord.begin(), ord.end(), cmp);
    for (int i = 0; i < n; i++) {
        int now = ord[i].idx;

        if (!visited[0][now]) {
            dfs(now, e, visited, c[now], d, 0);
        }
    }

    ll ans = 0;
    map<int, int> pair;

    for (int i = 0; i < n; i++) {
        pair[d[i]]++;
    }

    for (auto x : pair) {
        int t = x.second;
        ans += (ll)t * (ll)(t - 1) / 2;
    }

    cout << ans << "\n";
}