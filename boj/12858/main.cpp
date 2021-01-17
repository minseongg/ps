#include <iostream>
#include <vector>

using namespace std;

using ll = long long;
using vll = vector<ll>;
using vpll = vector<pair<ll, ll>>;

inline ll gcd(ll a, ll b) {
    if (a == 0 && b == 0) { return 0; }
    if (a < b) { return gcd(b, a); }
    if (b == 0) { return a; }
    return a % b == 0 ? b : gcd(b, a % b);
}

class SegmentTreeLazy {
public:
    int p = 1;
    vpll v;

    SegmentTreeLazy() = default;
    SegmentTreeLazy(int n) {
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
        if (s <= ts && te <= e) { v[x].second += (te - ts + 1) * k; }
        else if (te < s || ts > e) { return; }
        else {
            v[x].first += (min(e, te) - max(s, ts) + 1) * k;
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
        for (int i = p - 1; i > 0; i--) { v[i] = gcd(v[i << 1], v[(i << 1) + 1]); }
    }

    void update(int s, ll k) {
        int l = p + s;
        v[l] = k;
        l >>= 1;
        while (l) { v[l] = gcd(v[l << 1], v[(l << 1) + 1]); l >>= 1; }
    }

    ll get(int s, int e) {
        int ans = 0, l = p + s, r = p + e;
        while (l <= r) {
            if (l % 2 == 1) { ans = gcd(ans, v[l]); l++; }
            if (r % 2 == 0) { ans = gcd(ans, v[r]); r--; }
            l >>= 1;
            r >>= 1;
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    vll a, d;
    cin >> n;
    a.resize(n + 1); d.resize(n + 1);
    for (int i = 1; i <= n; i++) { cin >> a[i]; d[i] = abs(a[i] - a[i - 1]); }
    cin >> q;
    SegmentTreeLazy segtree_value(n + 1);
    SegmentTree segtree_gcd(n + 1);
    segtree_value.init(a);
    segtree_gcd.init(d);
    while (q--) {
        ll t;
        int a, b;
        cin >> t >> a >> b;
        if (t) {
            segtree_value.update(a, b, t);
            segtree_gcd.update(a, abs(segtree_value.get(a, a) - segtree_value.get(a - 1, a - 1)));
            if (b < n) { segtree_gcd.update(b + 1, abs(segtree_value.get(b + 1, b + 1) - segtree_value.get(b, b))); }
        } else {
            if (a == b) {
                cout << segtree_value.get(a, b) << "\n";
            } else {
                cout << gcd(segtree_value.get(a, a), segtree_gcd.get(a + 1, b)) << "\n";
            }
        }
    }
}