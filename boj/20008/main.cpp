#include <iostream>
#include <vector>

using namespace std;

int n, hp;
vector<int> c, d;

inline int vec2int(vector<int> s) {
    int t = 0;
    for (int i = n - 1; i >= 0; i--) {
        t *= 10;
        t += s[i];
    }
    return t;
}

inline vector<int> int2vec(int s) {
    vector<int> t;
    for (int i = 0; i < n; i++) {
        t.emplace_back(s % 10);
        s /= 10;
    }
    return t;
}

inline bool is_valid_vec(vector<int> s) {
    for (int i = 0; i < n; i++) {
        if (s[i] >= c[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    cin >> n >> hp;
    c.resize(n); d.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i] >> d[i];
    }

    vector<vector<int>> map, v;

    map.resize(101); v.resize(101);
    for (int i = 0; i < 101; i++) {
        map[i].resize(100000);
        v[i].resize(100000);
    }

    v[0][0] = 1;
    
    for (int i = 0; i <= 100; i++) {
        for (int j = 0; j < 100000; j++) {
            vector<int> s = int2vec(j);
            if (!is_valid_vec(s) || !v[i][j]) {
                continue;
            }

            for (int k = 0; k < n; k++) {
                if (s[k] == 0) {
                    vector<int> t = s;
                    int mm = 10000;
                    for (int l = 0; l < n; l++) {
                        if (l == k) {
                            t[l] = c[l] - 1;
                        } else {
                            t[l] = s[l] > 0 ? s[l] - 1 : 0;
                        }
                        mm = min(mm, t[l]);
                    }
                    for (int l = 0; l < n; l++) {
                        t[l] -= mm;
                    }
                    if (i + 1 + mm <= 100) {
                        map[i + 1 + mm][vec2int(t)] = max(map[i + 1 + mm][vec2int(t)], map[i][j] + d[k]);
                        v[i + 1 + mm][vec2int(t)] = 1;
                        if (map[i + 1 + mm][vec2int(t)] >= hp) {
                            cout << i + 1 << "\n";
                            return 0;
                        }
                    }
                }
            }
        }
    }
}
