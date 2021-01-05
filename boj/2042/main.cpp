#include <iostream>
#include <vector>

using namespace std;

using ll = long long;
using vll = vector<ll>;

class SegmentTree {
public:
    int p = 1;
    vll v;

    SegmentTree() = default;
    SegmentTree(int n) {
        while (p < n) { p <<= 1; }
        v.resize(p << 1);
    }

    void init(vll &w) {
        int sz = (int)w.size();
        for (int i = 0; i < sz; i++) { v[p + i] = w[i]; }
        for (int i = p - 1; i > 0; i--) { v[i] = v[i << 1] + v[(i << 1) + 1]; }
    }

    void update(int s, ll k) {
        int l = p + s;
        v[l] = k;
        l >>= 1;
        while (l) { v[l] = v[l << 1] + v[(l << 1) + 1]; l >>= 1; }
    }

    ll get(int s, int e) {
        ll ans = 0;
        int l = p + s, r = p + e;
        while (l <= r) {
            if (l % 2 == 1) { ans += v[l]; l++; }
            if (r % 2 == 0) { ans += v[r]; r--; }
            l >>= 1;
            r >>= 1;
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, k;
    vll v;
    cin >> n >> m >> k;
    v.resize(n);
    for (int i = 0; i < n; i++) { cin >> v[i]; }
    SegmentTree segtree(n);
    segtree.init(v);
    for (int i = 0; i < m + k; i++) {
        int t, a;
        ll b;
        cin >> t >> a >> b;
        if (t == 1) {
            segtree.update(a - 1, b);
        } else {
            cout << segtree.get(a - 1, b - 1) << "\n";
        }
    }
}
