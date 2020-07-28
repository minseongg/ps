#include <cstdio>
#include <set>

using namespace std;

using ull = unsigned long long;

const ull MOD = 1e9 + 7;

inline ull mul(ull a, ull b) {
    return (a % MOD) * (b % MOD) % MOD;
}

int main() {
    int t, n;
    ull ans;
    multiset<ull> m;

    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);

        ans = 1;
        m.clear();

        for (int i = 0; i < n; i++) {
            ull x;

            scanf("%llu", &x);
            m.insert(x);
        }

        ull l1, l2;
        while (m.size() > 1) {
            l1 = *(m.begin());
            m.erase(m.begin());

            l2 = *(m.begin());
            m.erase(m.begin());
            
            ans = mul(ans, mul(l1, l2));

            m.insert(l1 * l2);
        }

        printf("%llu\n", ans);
    }
}