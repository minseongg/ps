#include <iostream>
#include <vector>

using namespace std;

const int INF = 1e8;

inline bool valid(int al, int bl, int au, int bu) {
    if (au < al || bu < bl) { return false; }
    return true;
}

int solve(int al, int bl, int au, int bu, vector<vector<int>> &d, vector<int> &a, vector<int> &b, int w) {
    int offset = bu - au, ans = INF;

    if (d[offset + 1][au]) { return d[offset + 1][au]; }
    if (al == au && bl == bu) { return 0; }

    if (offset == 1) {
        if (valid(al, bl, au, bu - 1)) { ans = min(ans, solve(al, bl, au, bu - 1, d, a, b, w) + 1); }
        if (valid(al, bl, au, bu - 2) && b[bu - 2] + b[bu - 1] <= w) { ans = min(ans, solve(al, bl, au, bu - 2, d, a, b, w) + 1); }
    } else if (offset == 0) {
        if (valid(al, bl, au - 1, bu)) { ans = min(ans, solve(al, bl, au - 1, bu, d, a, b, w) + 1); }
        if (valid(al, bl, au, bu - 1)) { ans = min(ans, solve(al, bl, au, bu - 1, d, a, b, w) + 1); }
        if (valid(al, bl, au - 2, bu - 2) && a[au - 2] + a[au - 1] <= w && b[bu - 2] + b[bu - 1] <= w) { ans = min(ans, solve(al, bl, au - 2, bu - 2, d, a, b, w) + 2); }
        if (valid(al, bl, au - 1, bu - 1) && a[au - 1] + b[bu - 1] <= w) { ans = min(ans, solve(al, bl, au - 1, bu - 1, d, a, b, w) + 1); }
    } else {
        if (valid(al, bl, au - 1, bu)) { ans = min(ans, solve(al, bl, au - 1, bu, d, a, b, w) + 1); }
        if (valid(al, bl, au - 2, bu) && a[au - 2] + a[au - 1] <= w) { ans = min(ans, solve(al, bl, au - 2, bu, d, a, b, w) + 1); }
    }

    return d[offset + 1][au] = ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t, n, w, ans;
    vector<int> a, b;
    vector<vector<int>> d;

    cin >> t;
    while (t--) {
        ans = INF;

        cin >> n >> w;
        a.clear(); a.resize(n);
        b.clear(); b.resize(n);
        for (int i = 0; i < n; i++) { cin >> a[i]; }
        for (int i = 0; i < n; i++) { cin >> b[i]; }

        d.clear(); d.resize(3);

        for (int i = 0; i < 3; i++) { d[i].clear(); d[i].resize(n + 1); }
        ans = min(ans, solve(0, 0, n, n, d, a, b, w));

        if (b[0] + b[n - 1] <= w) {
            for (int i = 0; i < 3; i++) { d[i].clear(); d[i].resize(n + 1); }
            ans = min(ans, solve(0, 1, n, n - 1, d, a, b, w) + 1);
        }

        if (a[0] + a[n - 1] <= w) {
            for (int i = 0; i < 3; i++) { d[i].clear(); d[i].resize(n + 1); }
            ans = min(ans, solve(1, 0, n - 1, n, d, a, b, w) + 1);
        }

        if (a[0] + a[n - 1] <= w && b[0] + b[n - 1] <= w) {
            for (int i = 0; i < 3; i++) { d[i].clear(); d[i].resize(n + 1); }
            ans = min(ans, solve(1, 1, n - 1, n - 1, d, a, b, w) + 2);
        }

        cout << ans << "\n";
    }
}