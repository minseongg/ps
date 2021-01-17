#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

class SegmentTree {
public:
    int p = 1;
    vvi v;

    SegmentTree() = default;
    SegmentTree(int n) {
        while (p < n) { p <<= 1; }
        v.resize(p << 1);
    }

    void init(vi &w) {
        int sz = (int)w.size();
        for (int i = 0; i < sz; i++) { v[p + i].emplace_back(w[i]); }
        for (int i = p - 1; i > 0; i--) {
            for (auto &x : v[i << 1]) { v[i].emplace_back(x); }
            for (auto &x : v[(i << 1) + 1]) { v[i].emplace_back(x); }
            sort(v[i].begin(), v[i].end());
        }
    }

    int get(int idx, int l, int r, int i, int j, int k) {
        if (i <= l && r <= j) { return v[idx].end() - upper_bound(v[idx].begin(), v[idx].end(), k); }
        else if (r < i || j < l) { return 0; }
        else {
            int m = (l + r) >> 1;
            return get(idx << 1, l, m, i, j, k) + get((idx << 1) + 1, m + 1, r, i, j, k);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n;
    vi a(n);
    SegmentTree segtree(n);
    for (int i = 0; i < n; i++) { cin >> a[i]; }
    segtree.init(a);
    cin >> m;
    int ans = 0;
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        int i = a ^ ans, j = b ^ ans, k = c ^ ans;
        ans = segtree.get(1, 0, segtree.p - 1, i - 1, j - 1, k);
        cout << ans << "\n";
    }
}