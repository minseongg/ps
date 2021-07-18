#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);

    cout << fixed;
    cout.precision(1);

    int n;
    vector<ll> x, y;
    ll ans = 0;
    cin >> n;
    x.resize(n); y.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }
    for (int i = 0; i < n; i++) {
        ans += x[i] * y[(i + 1) % n];
        ans -= y[i] * x[(i + 1) % n];
    }
    cout << abs(ans) / 2.0 << "\n";
}
