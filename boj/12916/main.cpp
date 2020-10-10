#include <iostream>
#include <vector>

using namespace std;

using ll = long long;
using vvi = vector<vector<int>>;

const ll MOD = 1e9 + 7;

vvi matmul(int n, vvi &a, vvi &b) {
    vvi c;

    c.resize(n);

    for (int i = 0; i < n; i++) {
        c[i].resize(n);

        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                c[i][j] = (int)(((ll)c[i][j] + (ll)a[i][k] * (ll)b[k][j]) % MOD);
            }
        }
    }

    return c;
}

vvi matpow(int n, vvi &a, int k) {
    if (k == 1) {
        return a;
    }

    vvi b = matpow(n, a, k / 2);
    b = matmul(n, b, b);

    if (k % 2) {
        b = matmul(n, b, a);
    }

    return b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n, k, ans = 0;
    vvi a;

    cin >> n >> k;

    a.resize(n);

    for (int i = 0; i < n; i++) {
        a[i].resize(n);

        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    vvi r = matpow(n, a, k);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ans = (int)(((ll)ans + r[i][j]) % MOD);
        }
    }

    cout << ans << "\n";
}