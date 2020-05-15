#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

class E {
public:
    int u, v, t;

    E() = default;

    explicit E(int u, int v, int t) : u(u), v(v), t(t) {}
};

class Q {
public:
    int u, v, l, h;
    int anst = -1, ansv = 0;

    Q() = default;

    explicit Q(int u, int v, int l, int h) : u(u), v(v), l(l), h(h) {}
};

using pii = pair<int, int>;

using vE = vector<E>;
using vQ = vector<Q>;
using vi = vector<int>;
using vpii = vector<pii>;

const int INF = 1e6 + 1;

bool cmpE(const E& a, const E& b) {
    return a.t < b.t;
}

bool cmpPii(const pii& a, const pii& b) {
    return a.second < b.second;
}

int find(int n, vi& p) {
    return p[n] == n ? n : (p[n] = find(p[n], p));
}

void merge(int n, int m, vi& p, vi& r, vi& sz) {
    int pn = find(n, p), pm = find(m, p);

    if (pn == pm) return;

    if (r[pn] <= r[pm]) {
        p[pn] = pm;
        if (r[pn] == r[pm]) r[pm]++;
        sz[pm] += sz[pn];
    } else {
        p[pm] = pn;
        sz[pn] += sz[pm];
    }
}

void kruskal(int n, vE& edge, vQ& query, vpii& rem) {
    vi p, r, sz;
    int c = 0;

    p.resize(n);
    r.resize(n);
    sz.resize(n);

    for (int i = 0; i < n; i++) {
        p[i] = i;
        sz[i] = 1;
    }

    for (E& e : edge) {
        int u = e.u, v = e.v, t = e.t;

        merge(u, v, p, r, sz);
        
        while (c < (int)rem.size() && t >= rem[c].second) {
            int pu = find(query[rem[c].first].u, p), pv = find(query[rem[c].first].v, p);

            if (pu == pv) {
                query[rem[c].first].anst = t;
                query[rem[c].first].ansv = sz[pu];
                query[rem[c].first].h = rem[c].second - 1;
            } else {
                query[rem[c].first].l = rem[c].second + 1;
            }

            c++;
        }
    }

    while (c < (int)rem.size()) {
        int pu = find(query[rem[c].first].u, p), pv = find(query[rem[c].first].v, p);

        if (pu == pv) {
            query[rem[c].first].anst = rem[c].second;
            query[rem[c].first].ansv = sz[pu];
            query[rem[c].first].h = rem[c].second - 1;
        } else {
            query[rem[c].first].l = rem[c].second + 1;
        }

        c++;
    }
}

int main() {
    int n, m, q;
    vE edge;
    vQ query;

    scanf("%d%d", &n, &m);
    edge.resize(m);

    for (int i = 0; i < m; i++) {
        int u, v, t;

        scanf("%d%d%d", &u, &v, &t);
        edge[i] = E(u - 1, v - 1, t);
    }
    sort(edge.begin(), edge.end(), cmpE);

    scanf("%d", &q);
    query.resize(q);

    for (int i = 0; i < q; i++) {
        int u, v;

        scanf("%d%d", &u, &v);
        query[i] = Q(u - 1, v - 1, 1, INF);
    }

    while (1) {
        vpii rem;

        for (int i = 0; i < q; i++) {
            if (query[i].l > query[i].h) continue;
            rem.emplace_back(i, (query[i].l + query[i].h) >> 1);
        }

        if (!rem.size()) break;

        sort(rem.begin(), rem.end(), cmpPii);

        kruskal(n, edge, query, rem);
    }

    for (int i = 0; i < q; i++) {
        if (query[i].anst == -1) {
            printf("-1\n");
        } else {
            printf("%d %d\n", query[i].anst, query[i].ansv);
        }
    }
}
