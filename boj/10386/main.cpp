#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

ll gcd(ll a, ll b) {
    if (a < 0 || b < 0) { return gcd(abs(a), abs(b)); }
    if (a == 0 || b == 0) { return a + b; }
    if (a < b) { return gcd(b, a); }

    return a % b ? gcd(b, a % b) : b;
}

pair<ll, ll> f(vector<ll> v) {
    if (v.size() == 1) { return { v[0], 1 }; }

    ll a = v[0];

    v.erase(v.begin());

    auto b = f(v);
    ll q = a * b.first + b.second, p = b.first;

    return { q, p };
}

inline pair<ll, ll> mul(pair<ll, ll> a, pair<ll, ll> b) {
    ll q = a.first * b.first, p = a.second * b.second;
    ll g = gcd(q, p);

    return { q / g, p / g };
}

inline pair<ll, ll> add(pair<ll, ll> a, pair<ll, ll> b) {
    ll q = a.first * b.second + a.second * b.first, p = a.second * b.second;
    ll g = gcd(q, p);

    return { q / g, p / g };
}

inline pair<ll, ll> sub(pair<ll, ll> a, pair<ll, ll> b) {
    ll q = a.first * b.second - a.second * b.first, p = a.second * b.second;
    ll g = gcd(q, p);

    return { q / g, p / g };
}

inline pair<ll, ll> div(pair<ll, ll> a, pair<ll, ll> b) {
    ll q = a.first * b.second, p = a.second * b.first;

    if (p < 0) {
        q *= -1;
        p *= -1;
    }

    ll g = gcd(q, p);

    return { q / g, p / g };
}

inline void represent(pair<ll, ll> frac, vector<ll> &v) {
    ll q = frac.first, p = frac.second;

    if (p == 1) { v.emplace_back(q); return; }

    if (q < 0) {
        ll qu = -((-q) / p + ((-q) % p ? 1 : 0));

        v.emplace_back(qu);
        represent({ p, q - qu * p }, v);
    } else {
        v.emplace_back(q / p);
        represent({ p, q % p }, v);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int tc = 1, n1, n2;
    vector<ll> v1, v2, ans;

    while (true) {
        cin >> n1 >> n2;

        if (n1 == 0 && n2 == 0) { break; }

        v1.clear();
        v2.clear();

        v1.resize(n1);
        v2.resize(n2);

        for (int i = 0; i < n1; i++) { cin >> v1[i]; }
        for (int i = 0; i < n2; i++) { cin >> v2[i]; }

        cout << "Case " << tc << ":\n";
        tc++;

        ans.clear();
        represent(add(f(v1), f(v2)), ans);
        for (ll x : ans) { cout << x << " "; }
        cout << "\n";

        ans.clear();
        represent(sub(f(v1), f(v2)), ans);
        for (ll x : ans) { cout << x << " "; }
        cout << "\n";

        ans.clear();
        represent(mul(f(v1), f(v2)), ans);
        for (ll x : ans) { cout << x << " "; }
        cout << "\n";

        ans.clear();
        represent(div(f(v1), f(v2)), ans);
        for (ll x : ans) { cout << x << " "; }
        cout << "\n";
    }
}
