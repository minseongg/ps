#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

using vi = vector<int>;

const int MAXN = 1e6;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    vi last(MAXN), suf(MAXN);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        if (n == 1) {
            cout << 1 << "\n";
            continue;
        }

        vi checked(n);
        queue<int> q;
        q.push(1);

        while (!q.empty()) {
            int top = q.front();
            q.pop();
            if (top == 0) { break; }
            
            if (!checked[10 * top % n]) {
                last[10 * top % n] = top;
                suf[10 * top % n] = 0;
                checked[10 * top % n] = 1;
                q.push(10 * top % n);
            }

            if (!checked[(10 * top + 1) % n]) {
                last[(10 * top + 1) % n] = top;
                suf[(10 * top + 1) % n] = 1;
                checked[(10 * top + 1) % n] = 1;
                q.push((10 * top + 1) % n);
            }
        }

        if (!checked[0]) {
            cout << "BRAK\n";
        } else {
            vi ans;
            int idx = 0;
            while (idx != 1) {
                ans.emplace_back(suf[idx]);
                idx = last[idx];
            }
            reverse(ans.begin(), ans.end());
            cout << 1;
            for (auto x : ans) {
                cout << x;
            }
            cout << "\n";
        }
    }
}