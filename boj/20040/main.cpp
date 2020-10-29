#include <iostream>
#include <vector>

using namespace std;

int find(int n, vector<int> &par) {
    return par[n] == n ? n : par[n] = find(par[n], par);
}

void merge(int n, int m, vector<int> &par, vector<int> &lev) {
    int parn = find(n, par), parm = find(m, par);

    if (parn == parm) { return; }
    if (lev[parn] < lev[parm]) {
        par[parn] = parm;
    } else {
        if (lev[parn] == lev[parm]) {
            par[parm] = parn;
            lev[parn]++;
        } else {
            par[parm] = parn;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    vector<int> par, lev;

    cin >> n >> m;
    par.resize(n); lev.resize(n);
    for (int i = 0; i < n; i++) { par[i] = i; }
    for (int i = 0; i < m; i++) {
        int x, y, parx, pary;

        cin >> x >> y;
        parx = find(x, par); pary = find(y, par);
        if (parx == pary) {
            cout << i + 1 << "\n";
            return 0;
        }
        merge(x, y, par, lev);
    }
    cout << "0\n";
}