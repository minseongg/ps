#include <cstdio>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using si = stack<int>;

vi visited;
vvi e, e_rev;
si fin;

void dfs(int x) {
    visited[x] = 1;

    for (int y : e[x]) {
        if (visited[y]) continue;

        dfs(y);
    }

    fin.push(x);
}

vi sz, id;

void dfs_rev(int x, int c) {
    id[x] = c;
    sz[c]++;

    for (int y : e_rev[x]) {
        if (id[y]) continue;

        dfs_rev(y, c);
    }
}

vvi e_cc, e_cc_rev;
vi d, in;

void construct() {
    for (int i = 0; i < (int)e.size(); i++) {
        for (int y : e[i]) {
            if (id[i] == id[y]) continue;
            e_cc[id[i]].emplace_back(id[y]);
            e_cc_rev[id[y]].emplace_back(id[i]);
            in[id[y]]++;
        }
    }
}

int main() {
    int n, m, s, t;

    scanf("%d%d%d%d", &n, &m, &s, &t);
    s--; t--;
    e.resize(n);
    e_rev.resize(n);
    for (int i = 0; i < m; i++) {
        int a, b;

        scanf("%d%d", &a, &b);
        a--; b--;
        e[a].emplace_back(b);
        e_rev[b].emplace_back(a);
    }

    visited.resize(n);
    for (int i = 0; i < n; i++) {
        if (!visited[i]) dfs(i);
    }

    int c = 1;

    sz.resize(n + 1);
    id.resize(n);
    while (!fin.empty()) {
        int top = fin.top();

        fin.pop();
        if (id[top]) continue;
        dfs_rev(top, c);
        c++;
    }

    e_cc.resize(c);
    e_cc_rev.resize(c);
    d.resize(c + 1);
    in.resize(c + 1);
    construct();

    queue<int> q;

    for (int i = 1; i < c; i++) {
        if (!in[i]) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int front = q.front();

        q.pop();

        if (front == id[s]) {
            d[id[s]] = sz[id[s]];
        } else {
            for (int x : e_cc_rev[front]) {
                if (!d[x]) continue;

                d[front] = max(d[front], d[x] + sz[front]);
            }
        }

        for (int y : e_cc[front]) {
            in[y]--;

            if (in[y] == 0) {
                q.push(y);
            }
        }
    }

    printf("%d\n", d[id[t]]);
}