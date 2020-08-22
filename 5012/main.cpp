#include <iostream>
#include <vector>

using namespace std;

class SegTree {
public:
    int n, p = 1;
    vector<int> v;

    SegTree() = default;

    explicit SegTree(int n) : n(n) {
        while (p < n) {
            p <<= 1;
        }

        v.resize(p << 1);
    }

    void update(int idx) {
        int it = p + idx;

        v[it]++;
        it >>= 1;
        while (it) {
            v[it] = v[it << 1] + v[(it << 1) + 1];
            it >>= 1;
        }
    }

    int get(int l, int r) {
        if (l > r) { return 0; }

        int ans = 0;
        l = p + l;
        r = p + r;

        while (l <= r) {
            if (l % 2 == 1) { ans += v[l]; l++; }
            if (r % 2 == 0) { ans += v[r]; r--; }

            l >>= 1;
            r >>= 1;
        }

        return ans;
    }
};

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    ll ans = 0;
    vector<int> v, d, e;
    SegTree dd, ee;

    cin >> n;
    v.resize(n);
    d.resize(n);
    e.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        v[i]--;
    }

    dd = SegTree(n);
    ee = SegTree(n);

    for (int i = 0; i < n; i++) {
        d[i] = dd.get(v[i] + 1, n - 1);
        dd.update(v[i]);
    }

    for (int i = n - 1; i >= 0; i--) {
        e[i] = ee.get(0, v[i] - 1);
        ee.update(v[i]);
    }

    for (int i = 0; i < n; i++) {
        ans += (ll)d[i] * (ll)e[i];
    }

    cout << ans << "\n";

    return 0;
}