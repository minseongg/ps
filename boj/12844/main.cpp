#include <stdio.h>
#include <vector>

using namespace std;

using vi = vector<int>;

class node {
public:
    int val = 0, lazy = 0;

    node() = default;
};

using vn = vector<node>;

class segtree {
public:
    int p = 1;
    vn v;

    segtree() = default;

    segtree(int n) {
        while (p < n) p <<= 1;
        
        v.resize(p << 1);
    }

    void init(vi &a) {
        int sz = (int)a.size();

        for (int i = 0; i < sz; i++) {
            v[p + i].val = a[i];
        }

        for (int i = p - 1; i > 0; i--) {
            v[i].val = v[i << 1].val ^ v[(i << 1) + 1].val;
        }
    }

    void update(int s, int e, int k) {
        update_(s, e, k, 0, p - 1, 1);
    }

    int get(int s, int e) {
        return get_(s, e, 0, p - 1, 1);
    }

private:
    void update_(int s, int e, int k, int ss, int ee, int idx) {
        propagate_(idx);

        if (s <= ss && ee <= e) {
            v[idx].lazy ^= k;
        } else if (ee < s || e < ss) {
            return;
        } else {
            int ts = max(s, ss), te = min(e, ee);

            if ((te - ts + 1) % 2) v[idx].val ^= k;

            update_(s, e, k, ss, (ss + ee) / 2, idx << 1);
            update_(s, e, k, (ss + ee) / 2 + 1, ee, (idx << 1) + 1);
        }
    }

    int get_(int s, int e, int ss, int ee, int idx) {
        propagate_(idx);

        if (s <= ss && ee <= e) return v[idx].val;
        else if (ee < s || e < ss) return 0;
        else return get_(s, e, ss, (ss + ee) / 2, idx << 1) ^ get_(s, e, (ss + ee) / 2 + 1, ee, (idx << 1) + 1);
    }

    void propagate_(int idx) {
        if (idx >= p) {
            v[idx].val ^= v[idx].lazy;
        } else {
            v[idx << 1].lazy ^= v[idx].lazy;
            v[(idx << 1) + 1].lazy ^= v[idx].lazy;
        }
        v[idx].lazy = 0;
    }
};

int main() {
    int n, m;
    vi a;
    segtree s;

    scanf("%d", &n);
    a.resize(n);
    s = segtree(n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    s.init(a);

    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        int q, x, y;

        scanf("%d%d%d", &q, &x, &y);

        if (q == 1) {
            int k;

            scanf("%d", &k);
            s.update(x, y, k);
        } else {
            printf("%d\n", s.get(x, y));
        }
    }
}