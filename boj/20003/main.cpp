#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

ll gcd(ll x, ll y) {
    if (x < y) { return gcd(y, x); }
    return x % y ? gcd(y, x % y) : y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    ll p = 1, q = 1;
    vector<pair<int, int>> v;

    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        ll g = gcd(x, y);
        x /= g; y /= g;
        v.emplace_back(x, y);
    }
    p = v[0].first;

    for (int i = 0; i < n; i++) {
        p = gcd(p, (ll)v[i].first);
        q = q / gcd(q, (ll)v[i].second) * v[i].second;
    }

    cout << p << " " << q << "\n";
}