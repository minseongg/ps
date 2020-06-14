#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>

using namespace std;

using ll = long long;

class Data {
public:
    int x, y, w;
    int xidx;

    Data(int x = 0, int y = 0, int w = 0) {
        this->x = x;
        this->y = y;
        this->w = w;
    }
};

bool cmp_Data(const Data &a, const Data &b) {
    return a.y < b.y;
}

class SegTree {
public:
    int p;
    vector<ll> v_SUM, v_LSUM, v_RSUM, v_MAXSUM;

    SegTree(int sz = 0) {
        p = 1;

        while (p < sz) p <<= 1;
        v_SUM.resize(p << 1);
        v_LSUM.resize(p << 1);
        v_RSUM.resize(p << 1);
        v_MAXSUM.resize(p << 1);
    }

    void update(int idx, int val) {
        int c = p + idx;

        v_SUM[c] += (ll)val;
        v_LSUM[c] += (ll)val;
        v_RSUM[c] += (ll)val;
        v_MAXSUM[c] += (ll)val;
        c >>= 1;

        while (c) {
            int l = (c << 1), r = (c << 1) + 1;

            v_SUM[c] = v_SUM[l] + v_SUM[r];
            v_LSUM[c] = max(v_LSUM[l], v_SUM[l] + v_LSUM[r]);
            v_RSUM[c] = max(v_RSUM[r], v_SUM[r] + v_RSUM[l]);
            v_MAXSUM[c] = max(v_RSUM[l] + v_LSUM[r], max(v_MAXSUM[l], v_MAXSUM[r]));
            c >>= 1;
        }
    }

    ll ans() {
        return v_MAXSUM[1];
    }
};

int fill_mp(vector<Data> &v, map<int, int> &mp) {
    set<int> s;

    for (Data &x : v) {
        s.insert(x.x);
    }

    int c = 0;
    for (int x : s) {
        mp[x] = c;
        c++;
    }

    return c;
}

int main() {
    ios::sync_with_stdio(false);

    int n, mpsz;
    vector<Data> v;
    SegTree segtree;
    map<int, int> mp;
    ll ans = 0;

    cin >> n;
    v.resize(n);
    for (int i = 0; i < n; i++) {
        int x, y, w;

        cin >> x >> y >> w;
        v[i] = Data(x, y, w);
    }

    sort(v.begin(), v.end(), cmp_Data);
    mpsz = fill_mp(v, mp);

    for (int i = 0; i < n; i++) {
        v[i].xidx = mp[v[i].x];
    }

    int c = 0;

    while (c < n) {
        int d = c;

        segtree = SegTree(mpsz);

        while (d < n) {
            do {
                segtree.update(v[d].xidx, v[d].w);
                d++;
            } while (d < n && v[d].y == v[d-1].y);

            ans = max(ans, segtree.ans());
        }

        do {
            c++;
        } while (c < n && v[c].y == v[c-1].y);
    }

    cout << ans << "\n";
}