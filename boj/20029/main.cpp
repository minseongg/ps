#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, k, ans = 0;
    vector<int> b, c, selected;

    cin >> n >> k;
    b.resize(6); c.resize(n);
    for (int i = 0; i < 6; i++) { cin >> b[i]; }
    for (int i = 0; i < n; i++) { cin >> c[i]; c[i]--; }

    for (int i = 0; i < (1 << 6); i++) {
        int rem = k, avail = 0;

        selected.clear();
        selected.resize(6);
        for (int j = 0; j < 6; j++) { selected[j] = (i & (1 << j) ? 1 : 0); }
        for (int j = 0; j < n; j++) {
            if (selected[c[j]] && rem >= b[c[j]]) {
                avail++;
                rem -= b[c[j]];
            }
        }

        ans = max(ans, avail);
    }

    cout << ans << "\n";
}