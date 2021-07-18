#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    
    int n, b, c;
    ll ans = 0;
    vector<int> a, used[3];

    cin >> n >> b >> c;
    if (b < c) { c = b; }
    a.resize(n);
    for (int i = 0; i < 3; i++) { used[i].resize(n); }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < n; i++) {
        int rem = a[i];
        if (i > 0) { rem -= used[1][i - 1]; }
        if (i > 1) { rem -= used[2][i - 2]; }

        if (i > 0) {
            int t = min(rem, used[0][i - 1]);
            used[0][i - 1] -= t;
            used[1][i - 1] += t;
            rem -= t;
        }

        if (i > 1) {
            int t = min(rem, used[1][i - 2]);
            used[1][i - 2] -= t;
            used[2][i - 2] += t;
            rem -= t;
        }

        used[0][i] += rem;
    }

    for (int i = 0; i < n; i++) {
        ans += (ll)b * (ll)used[0][i];
        ans += (ll)(b + c) * (ll)used[1][i];
        ans += (ll)(b + 2 * c) * (ll)used[2][i];
    }

    cout << ans << "\n";
}
