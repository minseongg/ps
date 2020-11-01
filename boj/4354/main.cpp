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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string s;
    int sz;
    vector<int> pi;

    while (true) {
        cin >> s;

        sz = (int)s.size();
        if (s == ".") { break; }

        pi.clear();
        pi.resize(sz);
        get_pi(pi, s);

        int len = sz - pi[sz - 1], flag = 1;

        if (sz % len != 0) { flag = 0; }
        else {
            for (int i = 0; i < sz; i++) {
                if (s[i] != s[i % len]) {
                    flag = 0;
                    break;
                }
            }
        }

        cout << (flag ? sz / len : 1) << "\n";
    }
}