#include <iostream>
#include <vector>

using namespace std;

inline bool is_prime(int n) {
    if (n == 1) { return false; }
    for (int i = 2; i * i <= n; i++) { if (n % i == 0) { return false; } }
    return true;
}

inline void get_p(int n, vector<int> &p) {
    if (is_prime(n)) { p.emplace_back(n); }

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            if (is_prime(i)) { p.emplace_back(i); }
            if (i * i != n && is_prime(n / i)) { p.emplace_back(n / i); }
        }
    }
}

inline int f(int m, vector<int> &p) {
    int t = m;
    
    for (int x : p) {
        if (m % x == 0) {
            t /= x;
            t *= (x - 1);
        }
    }

    return t;
}

using ll = long long;

const int INF = 1e9 + 5;

int main() {
    int n, ans = INF;
    vector<int> p;

    cin >> n;

    get_p(n, p);

    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            if ((ll)i * (ll)f(i, p) == (ll)n) { ans = min(ans, i); }
            if ((ll)(n / i) * (ll)f(n / i, p) == (ll)n) { ans = min(ans, n / i); }
        }
    }

    if (ans == INF) {
        cout << "-1\n";
    } else {
        cout << ans << "\n";
    }
}
