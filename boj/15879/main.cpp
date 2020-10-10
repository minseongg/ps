#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e8 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, ans = 1;
    vector<int> remain, used, parity;
    vector<pair<int, int>> e;
    vector<vector<int>> d;

    cin >> n >> m;

    remain.resize(n);
    d.resize(n);
    parity.resize(n);
    used.resize(m);

    for (int i = 0; i < n; i++) { parity[i] = 1; }

    for (int i = 0; i < m; i++) {
        int x, y;

        cin >> x >> y;

        remain[x - 1]++;
        remain[y - 1]++;
        d[x - 1].emplace_back(i);
        d[y - 1].emplace_back(i);
        e.emplace_back(x - 1, y - 1);
    }

    for (int k = 0; k < m; k++) {
        bool found = false;
        int idx = 0;

        for (int i = 0; i < n; i++) {
            if (remain[i] >= 1) {
                idx = i;

                if (remain[i] == 1) {
                    found = true;
                    break;
                }
            }
        }

        if (!found) { ans = ans * 2 % MOD; }

        for (int x : d[idx]) {
            if (!used[x]) {
                if (found) {
                    if (parity[idx]) {
                        parity[e[x].first] ^= 1;
                        parity[e[x].second] ^= 1;
                    }
                }

                used[x] = 1;
                remain[e[x].first]--;
                remain[e[x].second]--;
                break;
            }
        }
    }

    bool valid = true;

    for (int x : parity) {
        if (x == 1) {
            valid = false;
            break;
        }
    }

    cout << (valid ? ans : 0) << "\n";
}