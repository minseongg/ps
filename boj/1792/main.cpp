#include <iostream>
#include <vector>

using namespace std;

using vi = vector<int>;
using ll = long long;

const int MAX = 5e4;

vi mobius(int n) {
    vi p(n + 1), m(n + 1);

    for (int i = 2; i <= n; i++) { p[i] = 1; }
    for (int i = 1; i <= n; i++) { m[i] = 1; }
    for (int i = 2; i <= n; i++) {
        if (p[i]) {
            for (int j = 1; j <= n / i; j++) {
                if (j >= i) { p[i * j] = 0; }
                m[i * j] *= (-1);
                if (j % i == 0) { m[i * j] = 0; }
            }
        }
    }

    return m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    vi mob = mobius(MAX);
    vi mob_psum(MAX + 1);
    for (int i = 1; i <= MAX; i++) { mob_psum[i] = mob_psum[i - 1] + mob[i]; }
    int n;
    cin >> n;
    while (n--) {
        ll ans = 0;
        int a, b, d;
        cin >> a >> b >> d;
        int k = a / d, l = b / d, it = 1;
        while (it <= min(k, l)) {
            int it_next = it + min((k % it) / (k / it), (l % it) / (l / it));
            ans += (ll)(mob_psum[it_next] - mob_psum[it - 1]) * (ll)(k / it) * (ll)(l / it);
            it = it_next + 1;
        }
        cout << ans << "\n";
    }
}