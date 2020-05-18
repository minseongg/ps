#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>

using namespace std;

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
    vector<int> v_SUM, v_LSUM, v_RSUM, v_MAXSUM;

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

        v_SUM[c] += val;
        v_LSUM[c] += val;
        v_RSUM[c] += val;
        v_MAXSUM[c] += val;
        c >>= 1;

        while (c) {
            int l = c << 1, r = (c << 1) + 1;

            v_SUM[c] = v_SUM[l] + v_SUM[r];
            v_LSUM[c] = max(v_LSUM[l], v_SUM[l] + v_LSUM[r]);
            v_RSUM[c] = max(v_RSUM[r], v_SUM[r] + v_RSUM[l]);
            v_MAXSUM[c] = max(v_RSUM[l] + v_LSUM[r], max(v_MAXSUM[l], v_MAXSUM[r]));
            c >>= 1;
        }
    }

    int ans() {
        return v_MAXSUM[1];
    }
};

void input(int &n1, int &n2, vector<Data> &p1, vector<Data> &p2, int &c1, int &c2, vector<Data> &p) {
    cin >> n1;
    p1.resize(n1);
    for (int i = 0; i < n1; i++) {
        int x, y;
        
        cin >> x >> y;
        p1[i] = Data(x, y);
    }

    cin >> n2;
    p2.resize(n2);
    for (int i = 0; i < n2; i++) {
        int x, y;

        cin >> x >> y;
        p2[i] = Data(x, y);
    }

    cin >> c1 >> c2;

    p.resize(n1+n2);
    for (int i = 0; i < n1; i++) p[i] = Data(p1[i].x, p1[i].y, c1);
    for (int i = n1; i < n1+n2; i++) p[i] = Data(p2[i-n1].x, p2[i-n1].y, -c2);
}

int fill_mp(vector<Data> &p, map<int, int> &mp) {
    set<int> s;
    
    for (Data &x : p) {
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
    
    int n1, n2;
    vector<Data> p1, p2, p;
    int c1, c2;

    int mpsz;
    map<int, int> mp;

    SegTree segtree;

    input(n1, n2, p1, p2, c1, c2, p);
    sort(p.begin(), p.end(), cmp_Data);
    mpsz = fill_mp(p, mp);

    for (Data &x : p) {
        x.xidx = mp[x.x];
    }

    int c = 0, ans = 0;

    while (c < n1+n2) {
        int d = c;

        segtree = SegTree(mpsz);

        while (d < n1+n2) {
            do {
                segtree.update(p[d].xidx, p[d].w);
                d++;
            } while (d < n1 + n2 && p[d].y == p[d-1].y);
            ans = max(ans, segtree.ans());
        }

        do {
            c++;
        } while (c < n1+n2 && p[c].y == p[c-1].y);
    }

    cout << ans << endl;
}