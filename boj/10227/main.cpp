#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int r, c, h, w;
    vector<vector<int>> b, s, t;
    cin >> r >> c >> h >> w;
    b.resize(r + 1); s.resize(r + 1); t.resize(r + 1);
    for (int i = 0; i <= r; i++) { b[i].resize(c + 1); s[i].resize(c + 1); t[i].resize(c + 1); }
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            cin >> b[i][j];
        }
    }

    int lo = 1, hi = r * c, ans;
    while (lo <= hi) {
        int mi = (lo + hi) >> 1, flag = 0, avail = 0;
        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= c; j++) {
                s[i][j] = b[i][j] < mi ? 1 : 0;
                t[i][j] = b[i][j] > mi ? 1 : 0;
                s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
                t[i][j] += t[i - 1][j] + t[i][j - 1] - t[i - 1][j - 1];
            }
        }
        for (int i = h; i <= r; i++) {
            for (int j = w; j <= c; j++) {
                int scnt = s[i][j] - s[i - h][j] - s[i][j - w] + s[i - h][j - w];
                int tcnt = t[i][j] - t[i - h][j] - t[i][j - w] + t[i - h][j - w];
                if (scnt == tcnt) { avail = 1; }
                if (scnt >= tcnt) { flag = 1; }
            }
        }

        if (flag) {
            hi = mi - 1;
        } else {
            lo = mi + 1;
        }

        if (avail) {
            ans = mi;
        }
    }

    cout << ans << "\n";
}