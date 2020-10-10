#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

using ll = long long;

class K {
public:
    ll x, y;

    K(int x = 0, int y = 0) : x(x), y(y) {}
};

bool cmp(const K& a, const K& b) {
    return a.x < b.x;
}

using vK = vector<K>;

int main() {
    ios::sync_with_stdio(false);

    int n;
    vK knot;

    cin >> n;
    knot.resize(n);
    for (int i = 0; i < n; i++) {
        ll x, l;

        cin >> x >> l;
        knot[i] = K(x, x + l);
    }

    sort(knot.begin(), knot.end(), cmp);

    ll s = 0, e = 2e9, ans;

    while (s <= e) {
        ll m = (s + e) >> 1, prev = knot[0].x;
        bool flag = true;

        for (int i = 1; i < n; i++) {
            ll lower = max(knot[i].x, prev + m);

            if (lower > knot[i].y) {
                flag = false;
                break;
            }

            prev = lower;
        }

        if (flag) {
            ans = m;
            s = m + 1;
        } else {
            e = m - 1;
        }
    }

    cout << ans << "\n";
}