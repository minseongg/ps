#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

const int MAXM = 2e6 + 1;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    ll ans = 0;
    vector<int> v;

    cin >> n;

    v.resize(MAXM);

    for (int i = 0; i < n; i++) {
        int x;

        cin >> x;

        v[x]++;
    }

    for (int i = 1; i < MAXM; i++) {
        ll c = 0;

        for (int j = i; j < MAXM; j += i) {
            c += v[j];
        }

        if (c <= 1) { continue; }

        ans = max(ans, (ll)i * c);
    }

    cout << ans << "\n";
}