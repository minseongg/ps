#include <iostream>

using namespace std;

using ll = long long;

ll pow(ll a, ll n, ll m) {
    if (n == 0) { return 1; }
    else if (n == 1) { return a; }
    ll t = pow(a, n / 2, m);
    ll s = t * t % m;
    return (n % 2 ? s * a % m : s);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll m, seed, x1, x2;
    cin >> m >> seed >> x1 >> x2;
    
    if (seed == x1) {
        cout << 1 << " " << 0 << "\n";
    } else {
        ll a = ((x1 - x2 + m) % m) * pow((seed - x1 + m) % m, m - 2, m) % m;
        ll c = (x1 - (a * seed % m) + m) % m;
        cout << a << " " << c << "\n";
    }
}