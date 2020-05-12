#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 2e5;

class Q {
public:
    int x, y, z, l, h, ans = INF;

    Q() = default;

    explicit Q(int x, int y, int z, int l, int h) : x(x), y(y), z(z), l(l), h(h) {}
};

using pii = pair<int, int>;
using vi = vector<int>;
using vQ = vector<Q>;

int main() {
    int n, m, k, q;
    vi c, a;
    vQ query;

    scanf("%d%d%d%d", &n, &m, &k, &q);
    c.resize(m);
    a.resize(k);
    query.resize(q);

    for (int i = 0; i < m; i++) {
        scanf("%d", &c[i]);
    }

    for (int i = 0; i < k; i++) {
        scanf("%d", &a[i]);
        a[i]--;
    }

    for (int i = 0; i < q; i++) {
        int x, y, z;

        scanf("%d%d%d", &x, &y, &z);
        x--; y--; z--;
        query[i] = Q(x, y, z, 0, k);
    }

    vi v;

    v.resize(n);
    while (1) {
        vector<pii> rem;
        int it = 0, sz = 0;

        fill(v.begin(), v.end(), 0);

        for (int i = 0; i < q; i++) {
            if (query[i].l <= query[i].h) {
                int mid = (query[i].l + query[i].h) >> 1;

                rem.emplace_back(mid, i);
            }
        }

        sz = (int)rem.size();

        if (!sz) break;

        sort(rem.begin(), rem.end());

        for (int i = 0; i <= k; i++) {
            v[a[i]]++;

            while (it < sz && rem[it].first == i) {
                int idx = rem[it].second;

                it++;
                if (v[query[idx].x] + v[query[idx].y] >= c[query[idx].z]) {
                    query[idx].ans = i;
                    query[idx].h = i - 1;
                } else {
                    query[idx].l = i + 1;
                }
            }
        }
    }

    vi s;

    s.resize(k);

    for (int i = 0; i < q; i++) {
        if (query[i].ans < k) s[query[i].ans]++;
    }
    for (int i = 1; i < k; i++) {
        s[i] += s[i - 1];
    }
    for (int i = 0; i < k; i++) {
        printf("%d\n", s[i]);
    }

    return 0;
}