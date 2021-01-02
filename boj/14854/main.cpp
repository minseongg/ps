#include <iostream>
#include <vector>

using namespace std;

using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;

const ll MOD = 142857;

inline void factorization(ll n, ll k, ll p, vll &a, vll &b) {
    while (n) {
        a.emplace_back(n % p);
        b.emplace_back(k % p);
        n /= p;
        k /= p;
    }
}

inline pair<ll, ll> mod_inv(ll n) {
    vll inv = { 0, 1, 14, 0, 7, 11, 0, 4, 17, 0, 19, 5, 0, 25, 2, 0, 22, 8, 0, 10, 23, 0, 16, 20, 0, 13, 26 };
    ll a = 1, alpha = 0;
    while (!(n % 3)) {
        a *= 3;
        n /= 3;
    }
    alpha = n;
    return { a, inv[alpha % 27] };
}

ll mod27(ll n, ll k, vvll &bc,vvll &mod_bc_2, vvll &mod_bc_3) {
    vll a, b;
    ll ans = 1;
    if (n < 27) { return bc[n][k] % 27; }
    factorization(n, k, 3, a, b);
    ans = (ans * mod_bc_3[a[0] + 3 * a[1] + 9 * a[2]][b[0] + 3 * b[1] + 9 * b[2]]) % 27;
    for (int i = 1; i < (int)a.size() - 2; i++) {
        ll t1;
        pair<ll, ll> t2;
        t1 = mod_bc_3[a[i] + 3 * a[i + 1] + 9 * a[i + 2]][b[i] + 3 * b[i + 1] + 9 * b[i + 2]];
        t2 = mod_inv(mod_bc_2[a[i] + 3 * a[i + 1]][b[i] + 3 * b[i + 1]]);
        t1 /= t2.first;
        t1 = (t1 * t2.second) % 27;
        ans = ans * t1 % 27;
    }
    return ans;
}

ll modp(ll n, ll k, ll p, vvll &bc) {
    vll a, b;
    ll ans = 1;
    factorization(n, k, p, a, b);
    for (int i = 0; i < (int)a.size(); i++) {
        ans = (ans * bc[a[i]][b[i]]) % p;
    }
    return ans;
}

ll solve(ll n, ll k, vvll &bc, vvll &mod_bc_2, vvll &mod_bc_3) {
    ll a = mod27(n, k, bc, mod_bc_2, mod_bc_3), b = modp(n, k, 11, bc), c = modp(n, k, 13, bc), d = modp(n, k, 37, bc), ans = 0;
    ans = (ans + 26 * 11 * 13 * 37 * a) % MOD;
    ans = (ans + 27 * 8  * 13 * 37 * b) % MOD;
    ans = (ans + 27 * 11 * 10 * 37 * c) % MOD;
    ans = (ans + 27 * 11 * 13 * 20 * d) % MOD;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    vvll bc(38), mod_bc_2(9), mod_bc_3(28);
    for (int i = 0; i <= 37; i++) { bc[i].resize(38); }
    for (int i = 0; i <= 8; i++) { mod_bc_2[i].resize(9); }
    for (int i = 0; i <= 27; i++) { mod_bc_3[i].resize(28); }
    bc[0][0] = 1;
    mod_bc_2[0][0] = 1;
    mod_bc_3[0][0] = 1;
    for (int i = 1; i <= 37; i++) {
        bc[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            bc[i][j] = (bc[i - 1][j - 1] + bc[i - 1][j]) % MOD;
        }
    }
    for (int i = 1; i <= 8; i++) {
        mod_bc_2[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            mod_bc_2[i][j] = mod_bc_2[i - 1][j - 1] + mod_bc_2[i - 1][j];
        }
    }
    for (int i = 1; i <= 27; i++) {
        mod_bc_3[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            mod_bc_3[i][j] = mod_bc_3[i - 1][j - 1] + mod_bc_3[i - 1][j];
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            mod_bc_2[i][j] = 3;
            mod_bc_3[i][j] = 3;
        }
    }
    for (int i = 0; i < 9; i++) {
        for (int j = i + 1; j < 9; j++) {
            mod_bc_2[i][j] = 3 * (i % 3 < j % 3 ? 3 : bc[i % 3][j % 3]);
            mod_bc_3[i][j] = 3 * mod_bc_2[i % 3][j % 3];
        }
    }
    for (int i = 0; i < 27; i++) {
        for (int j = i + 1; j < 27; j++) {
            mod_bc_3[i][j] = 3 * mod_bc_2[i % 9][j % 9];
        }
    }

    int t;
    cin >> t;
    while (t--) {
        ll n, k;
        cin >> n >> k;
        cout << solve(n, k, bc, mod_bc_2, mod_bc_3) << "\n";
    }
}