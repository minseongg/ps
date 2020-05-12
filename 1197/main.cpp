#include <iostream>
#include <vector>
#include <queue>

using namespace std;

using vi = vector<int>;

class E {
public:
    int u, v, w;

    explicit E(int u, int v, int w) {
        this->u = u;
        this->v = v;
        this->w = w;
    }
};

int find(int v, vi &p) {
    return p[v] == v ? v : (p[v] = find(p[v], p));
}

int main() {
    ios::sync_with_stdio(false);

    int n, m, ans = 0;
    const auto cmp = [](const E& a, const E& b) { return a.w > b.w; };
    priority_queue<E, vector<E>, decltype(cmp)> pq(cmp);
    vi p, r;
    
    cin >> n >> m;

    p.resize(n);
    r.resize(n);

    for (int i = 0; i < n; i++) p[i] = i;

    for (int i = 0; i < m; i++) {
        int u, v, w;

        cin >> u >> v >> w;
        pq.push(E(u - 1, v - 1, w));
    }

    while (!pq.empty()) {
        E top = pq.top();
        pq.pop();

        int pu = find(top.u, p), pv = find(top.v, p);

        if (pu != pv) {
            ans += top.w;

            if (r[pu] <= r[pv]) {
                p[pu] = pv;
                if (r[pu] == r[pv]) r[pv]++;
            } else {
                p[pv] = pu;
            }
        }
    }

    cout << ans << "\n";
}