#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

using ll = long long;
using vll = vector<ll>;
using vpll = vector<pair<ll, ll>>;

class Node {
public:
    Node *left, *right;
    ll value = 0, lazy = 0;

    Node() = default;
};

class SegmentTree {
public:
    int p = 1;
    Node *root;

    SegmentTree() = default;
    SegmentTree(int n) {
        root = new Node();
        while (p < n) { p <<= 1; }
    }

    void update(int s, int e, ll k) {
        update_lazy(s, e, 0, p - 1, root, k);
    }

    void update_lazy(int s, int e, int ts, int te, Node *x, ll k) {
        propagate(x, ts, te);
        if (s <= ts && te <= e) { x->lazy += k; }
        else if (te < s || ts > e) { return; }
        else {
            x->value += (ll)(min(e, te) - max(s, ts) + 1) * k;
            int tm = (ts + te) >> 1;
            update_lazy(s, e, ts, tm, x->left, k);
            update_lazy(s, e, tm + 1, te, x->right, k);
        }
    }

    ll get(int s, int e) {
        return get_lazy(s, e, 0, p - 1, root);
    }

    ll get_lazy(int s, int e, int ts, int te, Node *x) {
        propagate(x, ts, te);
        if (s <= ts && te <= e) { return x->value; }
        else if (te < s || ts > e) { return 0; }
        else {
            int tm = (ts + te) >> 1;
            return get_lazy(s, e, ts, tm, x->left) + get_lazy(s, e, tm + 1, te, x->right);
        }
    }

    void propagate(Node *x, int s, int e) {
        if (s != e && !x->left) { x->left = new Node(); }
        if (s != e && !x->right) { x->right = new Node(); }

        x->value += (ll)(e - s + 1) * x->lazy;
        if (s != e) {
            x->left->lazy += x->lazy;
            x->right->lazy += x->lazy;
        }
        x->lazy = 0;
    }
};

const int MAXV = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, k = 0;
    vector<tuple<int, int, ll>> query_1;
    vector<vector<tuple<int, int, int>>> query_2;
    vector<ll> ans;
    SegmentTree segtree(MAXV);

    cin >> n;
    ans.resize(n);
    query_2.resize(n);
    for (int i = 0; i < n; i++) {
        int x, a, b, c;
        cin >> x >> a >> b >> c;
        if (x == 1) {
            query_1.emplace_back(a - 1, b - 1, (ll)c);
            k++;
        } else {
            query_2[c - 1].emplace_back(a - 1, b - 1, i - k);
        }
    }

    for (int i = 0; i < k; i++) {
        auto &[ a1, b1, c1 ] = query_1[i];
        segtree.update(a1, b1, c1);
        for (auto &[ a2, b2, c2 ] : query_2[i]) {
            ans[c2] = segtree.get(a2, b2);
        }
    }

    for (int i = 0; i < n - k; i++) {
        cout << ans[i] << "\n";
    }
}