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

    string t, p;
    vector<int> pi, ans;

    getline(cin, t);
    getline(cin, p);

    pi.resize((int)p.size());
    get_pi(pi, p);

    kmp(ans, pi, t, p);

    cout << ans.size() << "\n";
    for (int x : ans) {
        cout << x << " ";
    }
    cout << "\n";
}