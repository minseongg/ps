#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

using pii = pair<int, int>;

bool cmp(const pii &a, const pii &b) {
    double angle_a = atan2(a.second, a.first);
    double angle_b = atan2(b.second, b.first);

    if (angle_a < 0) { angle_a += 180.0; }
    if (angle_b < 0) { angle_b += 180.0; }

    return angle_a < angle_b;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    vector<pii> q;
    vector<int> c, t;
    pii p;

    cin >> n >> k;

    if (n % k) {
        cout << "NO\n";
        return 0;
    }

    for (int i = 0; i < n; i++) {
        int x, y;

        cin >> x >> y;

        q.emplace_back(x - p.first, y - p.second);
    }

    cin >> p.first >> p.second;

    for (int i = 0; i < n; i++) {
        q[i].first -= p.first;
        q[i].second -= p.second;
    }

    sort(q.begin(), q.end(), cmp);

    for (int i = 0; i < n; i++) {
        if (!i) {
            c.emplace_back(1);
        } else {
            if (atan2(q[i].second, q[i].first) == atan2(q[i - 1].second, q[i - 1].first)) {
                c[(int)c.size() - 1]++;
            } else {
                c.emplace_back(1);
            }
        }
    }

    int sz = (int)c.size(), cul = 0;
    bool flag, ans = false;

    for (int i = 0; i < sz; i++) {
        t.clear();
        flag = true;

        for (int j = 0; j < sz; j++) {
            cul += c[j];

            if (cul > n / k) {
                flag = false;
                break;
            }

            if (j == i || j == sz - 1) {
                t.emplace_back(cul);
                cul = 0;
            } else if (j > i && cul == n / k) {
                t.emplace_back(cul);
                cul = 0;
            }
        }

        if (flag && ((int)t.size() == k || ((int)t.size() == k + 1 && t[0] + t[k] == n / k))) {
            ans = true;
            break;
        }
    }

    if (ans) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}
