#include <iostream>
#include <vector>

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
        v[l] = k; l >>= 1;
        while (l) { v[l] = max(v[l << 1], v[(l << 1) + 1]); l >>= 1; }
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

    int n;
    vector<int> a, b_inv;
    cin >> n;
    a.resize(n); b_inv.resize(n + 1);
    for (int i = 0; i < n; i++) { cin >> a[i]; }
    for (int i = 0; i < n; i++) { int x; cin >> x; b_inv[x] = i; }

    int ans = 0;
    SegmentTree segtree(n);
    for (int i = 0; i < n; i++) {
        int t = segtree.get(0, b_inv[a[i]] - 1);
        ans = max(ans, t + 1);
        segtree.update(b_inv[a[i]], t + 1);
    }
    cout << ans << "\n";
}

