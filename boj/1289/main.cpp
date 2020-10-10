#include <cstdio>
#include <vector>

using namespace std;

using ll = long long;
using pii = pair<int, int>;
using vvE = vector<vector<pii>>;

const int INF = 1e9 + 7;

inline int add(int a, int b) { return (a + b) % INF;}

inline int sub(int a, int b) { return (a - b + INF) % INF;}

inline int mul(int a, int b) { return (int)(((ll)a * (ll)b) % (ll)INF);}

inline int div2(int a) { return (int)(((ll)a * (ll)(INF / 2 + 1)) % (ll)INF);}

pii solve(int a, int p, vvE& edge) {
    int dr = 0, er = 0, s = 0;

    for (auto& e: edge[a]) {
        int b = e.first, w = e.second;

        if (b == p) continue;

        pii c = solve(b, a, edge);
        int dc = c.first, ec = c.second;

        dr = add(dr, mul(w, add(dc, 1)));
        s = add(s, mul(mul(w, add(dc, 1)), mul(w, add(dc, 1))));
        er = add(er, ec);
    }
    er = add(er, add(dr, div2(sub(mul(dr, dr), s))));

    return {dr, er};
}

int main() {
    int n;
    vvE edge;

    scanf("%d", &n);
    edge.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b, w;

        scanf("%d%d%d", &a, &b, &w);
        edge[a - 1].emplace_back(b - 1, w);
        edge[b - 1].emplace_back(a - 1, w);
    }

    printf("%d\n", solve(0, -1, edge).second);
}