#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

int get_parent(int now, vector<int> &par) {
    return par[now] == now ? now : (par[now] = get_parent(par[now], par));
}

int merge(int x, int y, vector<int> &par, vector<int> &lev) {
    int par_x = get_parent(x, par);
    int par_y = get_parent(y, par);

    if (lev[par_x] < lev[par_y]) {
        par[par_x] = par_y;
        return par_y;
    } else {
        if (lev[par_x] == lev[par_y]) {
            par[par_x] = par_y;
            lev[par_y]++;
            return par_y;
        } else {
            par[par_y] = par_x;
            return par_x;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, q, wy = 0, wx = 0;
    string s;
    map<pair<int, int>, int> m;
    vector<int> par, lev;

    cin >> n >> s >> q;
    par.resize(q); lev.resize(q);
    for (int i = 0; i < q; i++) { par[i] = i; }
    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        if (m.find({ x, y }) != m.end()) {
            int value = m[{ x, y }];
            par[i] = value;
            lev[value] = 1;
        } else {
            m[{ x, y }] = i;
        }
    }

    for (int i = 0; i < n; i++) {
        int dy, dx;
        
        if (s[i] == 'R') { dx = -1; dy = 0; }
        if (s[i] == 'L') { dx = 1; dy = 0; }
        if (s[i] == 'U') { dx = 0; dy = -1; }
        if (s[i] == 'D') { dx = 0; dy = 1; }

        if (m.find({ wx + dx, wy + dy }) == m.end()) {
            wx += dx; wy += dy;
        } else {
            int value = m[{ wx + dx, wy + dy }];

            if (m.find({ wx + dx * 2, wy + dy * 2 }) == m.end()) {
                m.erase(m.find({ wx + dx, wy + dy }));
                m[{ wx + dx * 2, wy + dy * 2 }] = value;
                wx += dx; wy += dy;
            } else {
                int value_2 = m[{ wx + dx * 2, wy + dy * 2 }];

                m.erase(m.find({ wx + dx, wy + dy }));
                m.erase(m.find({ wx + dx * 2, wy + dy * 2 }));
                m[{ wx + dx * 2, wy + dy * 2 }] = merge(value, value_2, par, lev);
                wx += dx; wy += dy;
            }
        }
    }

    vector<pair<int, int>> pos;
    pos.resize(q);
    for (auto x : m) {
        pair<int, int> t = x.first;
        pos[x.second] = t;
    }

    for (int i = 0; i < q; i++) {
        int p = get_parent(i, par);
        cout << pos[p].first - wx << " " << pos[p].second - wy << "\n";
    }
}