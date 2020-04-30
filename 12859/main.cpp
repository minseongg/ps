#include <iostream>
#include <vector>
#include <map>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

vi get_prime(int x) {
    vi p;
    int c = 2;
    
    while (x > 1) {
        if (x % c == 0) p.push_back(c);
        while (x % c == 0) x /= c;
        c++;
    }

    return p;
}

inline int solve(int n, vi &l, vi &c) {
    vvi p;
    int ans = 1e9;

    p.resize(n);
    for (int i = 0; i < n; i++) {
        p[i] = get_prime(l[i]);
    }

    for (int i = 0; i < n; i++) {
        vi v[2], flag;
        int sz = (int)p[i].size(), par = 0;

        v[0].resize(1 << sz); v[1].resize(1 << sz);
        flag.resize(n);
        for (int j = i + 1; j < n; j++) {
            map<int, bool> mp;
            int f = 0, cnt = 0;

            for (int x : p[j]) mp[x] = true;
            
            for (int x : p[i]) {
                if (mp[x]) {
                    f |= (1 << cnt);
                }
                cnt++;
            }

            flag[j] = f;
        }

        v[0][(1 << sz) - 1] = c[i];
        for (int j = i + 1; j < n; j++) {
            for (int k = 0; k < (1 << sz); k++) {
                v[par^1][k] = v[par][k];
                if (!v[par][k]) continue;

                int t = k & flag[j];

                v[par^1][t] = v[par^1][t] ? min(v[par^1][t], v[par][k] + c[j]) : v[par][k] + c[j];
            }

            par ^= 1;
        }
        
        if (v[par][0]) ans = min(ans, v[par][0]);
    }

    return ans == 1e9 ? -1 : ans;
}

int main() {
    ios::sync_with_stdio(false);

    int n;
    vi l, c;

    cin >> n;
    l.resize(n);
    c.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> l[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    cout << solve(n, l, c) << "\n";
}