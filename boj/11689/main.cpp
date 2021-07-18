#include <iostream>

using namespace std;

using ll = long long;

int main() {
    ll n, t, ans;
    cin >> n;
    ans = t = n;
    for (ll i = 2; i * i <= t; i++) {
        if (n % i == 0) {
            ans = ans / i * (i - 1);
            while (n % i == 0) { n /= i; }
        }
    }
    if (n > 1) {
        ans = ans / n * (n - 1);
    }
    cout << ans << "\n";
}