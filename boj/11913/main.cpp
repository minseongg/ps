#include <stdio.h>
#include <vector>

using namespace std;

using ll = long long;
using vvll = vector<vector<ll>>;

void f(ll a, ll b, ll p, ll q, int c, vvll &d) {
    if (b == 0) {
        d[0][c] = d[1][c] = 0;

        return;
    }

    ll k = a / b, r = a % b;

    f(b, r, p, q, c+1, d);

    if ((p + d[0][c+1] - d[1][c+1]) / q < k) {
        d[0][c] = p + d[0][c+1];
    } else {
        d[0][c] = k * q + d[1][c+1];
    }

    if ((p + d[0][c] - d[0][c+1]) / q < k) {
        d[1][c] = p + d[0][c];
    } else {
        d[1][c] = k * q + d[0][c+1];
    }
}

int main() {
    int t;
    vvll v;

    v.resize(2);
    v[0].resize(300); v[1].resize(300);

    scanf("%d", &t);
    while (t--) {
        ll a, b, p, q;

        scanf("%lld%lld%lld%lld", &a, &b, &p, &q);
        f(max(a, b), min(a, b), p, q, 0, v);

        printf("%lld\n", v[a<b][0]);
    }
}