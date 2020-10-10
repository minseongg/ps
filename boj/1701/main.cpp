#include <iostream>
#include <vector>
#include <string>

using namespace std;

using vi = vector<int>;

inline void get_fail(string &s, vi &v) {
    int sz = (int)s.size();

    for (int i = 1; i < sz; i++) {
        int t = i - 1;

        do {
            if (s[v[t]] == s[i]) {
                v[i] = v[t] + 1;
                break;
            }
            t = v[t] - 1;
        } while (t >= 0);
    }
}

inline int f(string &s) {
    int ans = 0;
    vi v;

    v.resize((int)s.size());
    get_fail(s, v);

    for (int x : v) {
        ans = max(ans, x);
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);

    string s;
    int sz = (int)s.size(), ans = 0;

    cin >> s;

    while ((int)s.size()) {
        ans = max(ans, f(s));
        s = s.substr(1, (int)s.size() - 1);
    }
    cout << ans << "\n";
}