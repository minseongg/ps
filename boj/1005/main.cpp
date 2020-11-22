#include <iostream>
#include <vector>
#include <queue>

using namespace std;

using pii = pair<int, int>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--){
        int n, k, w;
        vector<int> d, rem;
        vector<vector<int>> e;

        auto cmp = [](pii left, pii right) { return left.second > right.second; };
        priority_queue<pii, vector<pii>, decltype(cmp)> pq(cmp);

        cin >> n >> k;
        d.resize(n);
        rem.resize(n);
        e.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> d[i];
        }
        for (int i = 0; i < k; i++) {
            int x, y;
            cin >> x >> y;
            e[x - 1].emplace_back(y - 1);
            rem[y - 1]++;
        }
        cin >> w;
        w--;

        for (int i = 0; i < n; i++) {
            if (rem[i] == 0) {
                pq.push({i, d[i]});
            }
        }

        while (!pq.empty()) {
            pii top = pq.top();
            pq.pop();

            int v = top.first, c = top.second;
            if (v == w) {
                cout << c << "\n";
                break;
            }

            for (int x : e[v]) {
                rem[x]--;
                if (rem[x] == 0) {
                    pq.push({x, c + d[x]});
                }
            }
        }
    }
}