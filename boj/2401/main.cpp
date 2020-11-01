#include <iostream>
#include <string>
#include <vector>

using namespace std;

inline void get_pi(vector<int> &pi, string &p) {
    int sz = (int)p.size(), j = 0;

    for (int i = 1; i < sz; i++) {
        while (j && p[i] != p[j]) { j = pi[j - 1]; }
        if (p[i] == p[j]) { pi[i] = ++j; }
    }
}

inline void kmp(vector<int> &ans, vector<int> &pi, string &t, string &p) {
    int sz_t = (int)t.size(), sz_p = (int)p.size(), j = 0;

    for (int i = 0; i < sz_t; i++) {
        while (j && t[i] != p[j]) { j = pi[j - 1]; }
        if (t[i] == p[j]) {
            if (j == sz_p - 1) {
                ans.emplace_back(i - sz_p + 2);
                j = pi[j];
            } else {
                j++;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string s;
    int n;
    vector<string> v;
    vector<int> vlen, ans;
    vector<vector<int>> pi;

    cin >> s >> n;
    v.resize(n); vlen.resize(n); pi.resize(n); ans.resize((int)s.size() + 1);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        vlen[i] = (int)v[i].size();
        pi[i].resize(vlen[i]);
        get_pi(pi[i], v[i]);
    }

    vector<int> it;
    it.resize(n);

    for (int i = 0; i < (int)s.size(); i++) {
        ans[i + 1] = ans[i];
        for (int j = 0; j < n; j++) {
            while (it[j] && s[i] != v[j][it[j]]) { it[j] = pi[j][it[j] - 1]; }
            if (s[i] == v[j][it[j]]) {
                if (it[j] == vlen[j] - 1) {
                    ans[i + 1] = max(ans[i + 1], ans[i + 1 - vlen[j]] + vlen[j]);
                    it[j] = pi[j][it[j]];
                } else {
                    it[j]++;
                }
            }
        }
    }

    cout << ans[(int)s.size()] << "\n";
}