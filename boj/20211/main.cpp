#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MAXX = 2e5;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    string s;
    vector<int> c;
    vector<pair<int, int>> ans;
    cin >> n >> s;
    c.resize(n + 1);
    int p = 0;
    for (int i = 1; i <= n; i++) {
        c[i] = c[i - 1] + (s[i - 1] == 'H' ? 3 : (p ? 1 : 5));
        p ^= 1;
    }

    for (int x = 1; x <= MAXX; x++) {
        int it = 1, lev = 0, flag = 1;
        while (it <= n) {
            int lo = it, hi = n, t = -1;
            while (lo <= hi) {
                int mi = (lo + hi) >> 1;
                int cs = (it % 2 ? c[mi] - c[it - 1] : 6 * (mi - it + 1) - c[mi] + c[it - 1]);
                if (cs >= x) {
                    hi = mi - 1;
                    t = mi;
                } else {
                    lo = mi + 1;
                }
            }

            if (t == -1) {
                flag = 0;
                break;
            }

            it = t + 1;
            lev++;
        }

        if (flag) { ans.emplace_back(x, lev); }
    }

    cout << ans.size() << "\n";
    for (auto &[ x, y ] : ans) {
        cout << x << " " << y << "\n";
    }
}