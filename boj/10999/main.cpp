#include <iostream>
#include <vector>

using namespace std;

using ll = long long;
using vll = vector<ll>;
using vpll = vector<pair<ll, ll>>;

class SegmentTree {
public:
    int p = 1;
    vpll v;

    SegmentTree() = default;
    SegmentTree(int n) {
        while (p < n) { p <<= 1; }
        v.resize(p << 1);
    }

    void init(vll &w) {
        int sz = (int)w.size();
        for (int i = 0; i < sz; i++) { v[p + i] = { w[i], 0 }; }
        for (int i = p - 1; i > 0; i--) { v[i] = { v[i << 1].first + v[(i << 1) + 1].first, 0 }; }
    }

    void update(int s, int e, ll k) {
        update_lazy(s, e, 0, p - 1, 1, k);
    }

    void update_lazy(int s, int e, int ts, int te, int x, ll k) {
        propagate(x);
        if (s <= ts && te <= e) { v[x].second += (ll)(te - ts + 1) * k; }
        else if (te < s || ts > e) { return; }
        else {
            v[x].first += (ll)(min(e, te) - max(s, ts) + 1) * k;
            int tm = (ts + te) / 2;
            update_lazy(s, e, ts, tm, x << 1, k);
            update_lazy(s, e, tm + 1, te, (x << 1) + 1, k);
        }
    }

    ll get(int s, int e) {
        return get_lazy(s, e, 0, p - 1, 1);
    }

    ll get_lazy(int s, int e, int ts, int te, int x) {
        propagate(x);
        if (s <= ts && te <= e) { return v[x].first; }
        else if (te < s || ts > e) { return 0; }
        else {
            int tm = (ts + te) / 2;
            return get_lazy(s, e, ts, tm, x << 1) + get_lazy(s, e, tm + 1, te, (x << 1) + 1);
        }
    }

    void propagate(int x) {
        v[x].first += v[x].second;
        if (x < p) {
            v[x << 1].second += v[x].second / 2;
            v[(x << 1) + 1].second += v[x].second / 2;
        }
        v[x].second = 0;
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
        int t, a, b, c;
        cin >> t;
        if (t == 1) {
            cin >> a >> b >> c;
            segtree.update(a - 1, b - 1, c);
        } else {
            cin >> a >> b;
            cout << segtree.get(a - 1, b - 1) << "\n";
        }
    }
}
