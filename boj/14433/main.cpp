#include <iostream>
#include <vector>

using namespace std;

bool dfs(int now, vector<int> &visited, vector<int> &a, vector<int> &b, vector<vector<int>> &e) {
    visited[now] = 1;

    for (int x : e[now]) {
        if (b[x] == -1 || (!visited[b[x]] && dfs(b[x], visited, a, b, e))) {
            a[now] = x;
            b[x] = now;
            return true;
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, k[2], match[2] = {0, 0};
    vector<int> visited, a, b;
    vector<vector<int>> e;

    cin >> n >> m >> k[0] >> k[1];

    visited.resize(n);
    a.resize(n);
    b.resize(m);
    e.resize(n);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            a[j] = -1;
            e[j].clear();
        }

        for (int j = 0; j < m; j++) {
            b[j] = -1;
        }

        for (int j = 0; j < k[i]; j++) {
            int x, y;

            cin >> x >> y;

            e[x - 1].emplace_back(y - 1);
        }

        for (int j = 0; j < n; j++) {
            if (a[j] == -1) {
                for (int k = 0; k < n; k++) {
                    visited[k] = 0;
                }

                if (dfs(j, visited, a, b, e)) match[i]++;
            }
        }
    }

    if (match[0] < match[1]) {
        cout << "네 다음 힐딱이\n";
    } else {
        cout << "그만 알아보자\n";
    }
}
