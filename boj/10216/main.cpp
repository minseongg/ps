#include <iostream>
#include <vector>

using namespace std;

int uf_find_par(vector<int> &par, int x) {
    return (par[x] == x ? x : (par[x] = uf_find_par(par, par[x])));
}

void uf_merge(vector<int> &par, vector<int> &lev, int x, int y) {
    x = uf_find_par(par, x);
    y = uf_find_par(par, y);

    if (x == y) { return; }

    if (lev[x] < lev[y]) {
        par[x] = y;
    } else if (lev[y] < lev[x]) {
        par[y] = x;
    } else {
        par[x] = y;
        lev[y]++;
    }
}

bool is_cross(
    int x1, int y1, int r1,
    int x2, int y2, int r2
) {
    return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) <= (r1 + r2) * (r1 + r2);
}

int main() {
    int t;

    cin >> t;
    while (t--) {
        int n, groups = 0;
        vector<int> x, y, r;
        vector<int> par, lev;

        cin >> n;
        x.resize(n); y.resize(n); r.resize(n);
        par.resize(n); lev.resize(n);
        for (int i = 0; i < n; i++) { par[i] = i; }
        for (int i = 0; i < n; i++) {
            cin >> x[i] >> y[i] >> r[i];
            for (int j = 0; j < i; j++) {
                if (is_cross(
                    x[j], y[j], r[j],
                    x[i], y[i], r[i]
                    )) {
                    uf_merge(par, lev, j, i);
                }
            }
        }

        for (int i = 0; i < n; i++) {
            if (par[i] == i) { groups++; }
        }

        cout << groups << "\n";
    }
}
