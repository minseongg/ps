#include <iostream>

using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, f = 0;
    ll x, p, s = 0, d = 0, e = 0, d2 = 0, e2 = 0;

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> x >> p;

        if (!f) { d = max(d, p); }
        if (f && s > x) { e2 = max(e2, s - x); }
        if (i && s > x) {
            e = max(e, s - x);

            if (!f) {
                d2 = p;
                f = 1;
            }
        }

        s += p;
    }

    if (!f || d >= e || d2 >= e2) {
        cout << "Kkeo-eok\n";
    } else {
        cout << "Zzz\n";
    }
}
