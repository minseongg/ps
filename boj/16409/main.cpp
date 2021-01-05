#include <iostream>
#include <vector>

using namespace std;

using vi = vector<int>;
using ll = long long;

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

ll solve(int a, int b, vi &mob_psum) {
    int it = 1;
    ll ans = 0;
    while (it <= min(a, b)) {
        int it_next = it + min((a % it) / (a / it), (b % it) / (b / it));
        ans += (ll)(mob_psum[it_next] - mob_psum[it - 1]) * (ll)(a / it) * (ll)(b / it);
        it = it_next + 1;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int a, b, c, d;
    cin >> a >> b >> c >> d;
    vi mob = mobius(max(b, d));
    vi mob_psum(max(b, d) + 1);
    for (int i = 1; i <= max(b, d); i++) { mob_psum[i] = mob_psum[i - 1] + mob[i]; }
    cout << solve(b, d, mob_psum) - solve(b, c - 1, mob_psum) - solve(a - 1, d, mob_psum) + solve(a - 1, c - 1, mob_psum) << "\n";
}