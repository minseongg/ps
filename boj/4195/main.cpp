#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int uf_merge(int x, int y, vector<int> &lev, vector<int> &par, vector<int> &cnt) {
    int ans;
    if (lev[x] < lev[y]) {
        par[x] = y;
        cnt[y] += cnt[x];
        ans = cnt[y];
    } else {
        par[y] = x;
        cnt[x] += cnt[y];
        ans = cnt[x];
        if (lev[x] == lev[y]) { lev[x]++; }
    }
    return ans;
}

int uf_find_par(int x, vector<int> &par) {
    if (par[x] == x) { return x; }
    return par[x] = uf_find_par(par[x], par);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int f;
        vector<int> lev, par, cnt;
        map<string, int> name_to_id;
        string a, b;
        cin >> f;
        lev.resize(f << 1);
        par.resize(f << 1);
        cnt.resize(f << 1);
        for (int i = 0; i < (f << 1); i++) {
            par[i] = i;
            cnt[i] = 1;
        }
        while (f--) {
            cin >> a >> b;
            if (name_to_id.find(a) == name_to_id.end()) { name_to_id[a] = name_to_id.size(); }
            if (name_to_id.find(b) == name_to_id.end()) { name_to_id[b] = name_to_id.size(); }
            int a_id = name_to_id[a], b_id = name_to_id[b];
            int par_a = uf_find_par(a_id, par), par_b = uf_find_par(b_id, par);
            if (par_a == par_b) {
                cout << cnt[par_a] << "\n";
            } else {
                cout << uf_merge(par_a, par_b, lev, par, cnt) << "\n";
            }
        }
    }
}