#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

const int MAXK = 1e3;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    vector<int> s(MAXK, 1), p;
    vector<tuple<int, int, int, int>> v(MAXK);
    s[0] = s[1] = 0;
    for (int i = 2; i < MAXK; i++) {
        if (s[i]) {
            p.emplace_back(i);
            for (int j = i * i; j < MAXK; j += i) {
                s[j] = 0;
            }
        }
    }

    int sz = (int)p.size();
    for (int i = 0; i < sz; i++) {
        for (int j = i; j < sz; j++) {
            for (int k = j; k < sz; k++) {
                if (p[i] + p[j] + p[k] >= MAXK) { continue; }
                v[p[i] + p[j] + p[k]] = { 1, p[i], p[j], p[k] };
            }
        }
    }

    int t;
    cin >> t;
    while (t--) {
        int k;
        cin >> k;
        auto [ is_avail, a, b, c ] = v[k];
        if (is_avail) { cout << a << " " << b << " " << c << "\n"; }
        else { cout << "0\n"; }
    }
}