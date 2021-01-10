#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

using vi = vector<int>;

class SegmentTree {
public:
    int p = 1;
    vi v;

    SegmentTree() = default;
    SegmentTree(int n) {
        while (p < n) { p <<= 1; }
        v.resize(p << 1);
    }

    void init(vi &w) {
        int sz = (int)w.size();
        for (int i = 0; i < sz; i++) { v[p + i] = w[i]; }
        for (int i = p - 1; i > 0; i--) { v[i] = max(v[i << 1], v[(i << 1) + 1]); }
    }

    void update(int s, int k) {
        int l = p + s;
        v[l] = k;
        l >>= 1;
        while (l) { v[l] = max(v[l << 1], v[(l << 1) + 1]); }
    }

    int get(int s, int e) {
        int ans = 0, l = p + s, r = p + e;
        while (l <= r) {
            if (l % 2 == 1) { ans = max(ans, v[l]); l++; }
            if (r % 2 == 0) { ans = max(ans, v[r]); r--; }
            l >>= 1;
            r >>= 1;
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, s, g, p, d;
    string h;
    vector<vector<int>> t;

    cin >> n >> s >> g >> p >> d >> h;
    SegmentTree segtree(d + 1);
    t.resize(n + 1);
    for (int i = 1; i <= n; i++) { t[i].resize(d + 1); }

    int l, r;
    if (h[0] == 'B') { l = 0; r = s - 1; }
    else if (h[0] == 'S') { l = s; r = g - 1; }
    else if (h[0] == 'G') { l = g; r = p - 1; }
    else if (h[0] == 'P') { l = p; r = d - 1; }
    else { l = d; r = d; }
    for (int j = l; j <= r; j++) { t[1][j] = j; }
    
    for (int i = 2; i <= n; i++) {
        segtree.init(t[i - 1]);
        if (h[i - 1] == 'B') { l = 0; r = s - 1; }
        else if (h[i - 1] == 'S') { l = s; r = g - 1; }
        else if (h[i - 1] == 'G') { l = g; r = p - 1; }
        else if (h[i - 1] == 'P') { l = p; r = d - 1; }
        else { l = d; r = d << 1; }
        for (int j = 0; j <= d; j++) {
            int tl = l - j, tr = r - j;
            if (tr < 0) { break; }
            t[i][j] = segtree.get(max(tl, 0), min(tr, d)) + j;
        }
    }

    int ans = 0;
    for (int i = 0; i <= d; i++) { ans = max(ans, t[n][i]); }
    cout << ans << "\n";
}