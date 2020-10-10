#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

int main() {
    int n, m;
    vector<int> h, ans, outdeg;
    vector<vector<int>> e, reve;
    queue<int> q;
    
    scanf("%d%d", &n, &m);

    e.resize(n);
    reve.resize(n);
    ans.resize(n);
    outdeg.resize(n);

    for (int i = 0; i < n; i++) {
        int x;

        scanf("%d", &x);
        h.emplace_back(x);
    }

    for (int i = 0; i < m; i++) {
        int u, v;

        scanf("%d%d", &u, &v);
        
        if (h[u - 1] < h[v - 1]) {
            e[u - 1].emplace_back(v - 1);
            reve[v - 1].emplace_back(u - 1);
            outdeg[u - 1]++;
        } else {
            e[v - 1].emplace_back(u - 1);
            reve[u - 1].emplace_back(v - 1);
            outdeg[v - 1]++;
        }
    }

    for (int i = 0; i < n; i++) {
        if (!e[i].size()) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int f = q.front(), l = 0;

        q.pop();

        for (int x : e[f]) {
            l = max(l, ans[x]);
        }

        ans[f] = l + 1;

        for (int x : reve[f]) {
            outdeg[x]--;

            if (!outdeg[x]) {
                q.push(x);
            }
        }
    }

    for (int x : ans) {
        printf("%d\n", x);
    }
}