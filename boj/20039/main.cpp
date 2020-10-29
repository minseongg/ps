#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class SegmentTree {
public:
    int n, p;
    vector<int> v;

    SegmentTree(int n) : n(n) {
        p = 1;
        while (p < n) { p <<= 1; }
        v.resize(p << 1);
    }

    int query(int l, int r) {
        int tl = p + l, tr = p + r, ans = 0;

        while (tl <= tr) {
            if (tl % 2 == 1) {
                ans = max(ans, v[tl]);
                tl++;
            }

            if (tr % 2 == 0) {
                ans = max(ans, v[tr]);
                tr--;
            }

            tl >>= 1;
            tr >>= 1;
        }

        return ans;
    }

    void update(int l, int x) {
        int tl = p + l;

        v[tl] = x;
        tl >>= 1;

        while (tl > 0) {
            v[tl] = max(v[tl << 1], v[(tl << 1) + 1]);
            tl >>= 1;
        }
    }
};

class Reorder {
public:
    int value, rank, idx;

    Reorder() : value(0), rank(0), idx(0) {}

    Reorder(int value, int rank, int idx) : value(value), rank(rank), idx(idx) {}
};

bool cmp_reorder_value(const Reorder &a, const Reorder &b) {
    return a.value < b.value;
}

bool cmp_reorder_idx(const Reorder &a, const Reorder &b) {
    return a.idx < b.idx;
}

inline void decompress(vector<int> &v, int n) {
    vector<Reorder> r(n);

    for (int i = 0; i < n; i++) { r[i] = Reorder(v[i], 0, i); }
    sort(r.begin(), r.end(), cmp_reorder_value);
    for (int i = 0; i < n; i++) { r[i].rank = i; }
    sort(r.begin(), r.end(), cmp_reorder_idx);
    for (int i = 0; i < n; i++) { v[i] = r[i].rank; }
}

inline int update_up_2(int x, int i, SegmentTree &down_3, vector<int> &culmin) {
    int prev = down_3.query(0, x - 1);
    if (prev) { prev++; }

    int alone = culmin[i] < x ? 2 : 0;

    return max(prev, alone);
}

inline int update_up_3(int x, SegmentTree &up_2, SegmentTree &up_3) {
    int prev = max(up_2.query(0, x - 1), up_3.query(0, x - 1));
    if (prev) { prev++; }

    return prev;
}

inline int update_down_2(int x, int i, int n, SegmentTree &up_3, vector<int> &culmax) {
    int prev = up_3.query(x + 1, n - 1);
    if (prev) { prev++; }

    int alone = culmax[i] > x ? 2 : 0;

    return max(prev, alone);
}

inline int update_down_3(int x, int n, SegmentTree &down_2, SegmentTree &down_3) {
    int prev = max(down_2.query(x + 1, n - 1), down_3.query(x + 1, n - 1));
    if (prev) { prev++; }

    return prev;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, ans = 0;
    vector<int> v;

    cin >> n;
    v.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    decompress(v, n);

    vector<int> culmin(n), culmax(n);
    SegmentTree up_2(n), up_3(n), down_2(n), down_3(n);

    for (int i = 0; i < n; i++) {
        culmin[i] = (i ? min(culmin[i - 1], v[i]) : v[i]);
        culmax[i] = (i ? max(culmax[i - 1], v[i]) : v[i]);
    }

    for (int i = 0; i < n; i++) {
        up_2.update(v[i], update_up_2(v[i], i, down_3, culmin));
        up_3.update(v[i], update_up_3(v[i], up_2, up_3));
        down_2.update(v[i], update_down_2(v[i], i, n, up_3, culmax));
        down_3.update(v[i], update_down_3(v[i], n, down_2, down_3));
    }

    ans = max(ans, up_3.query(0, n - 1));
    ans = max(ans, down_3.query(0, n - 1));

    cout << ans << "\n";
}
