#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

const ll MAX = 1e8;

inline void get_prime(vector<bool> &p) {
    p[0] = true;
    p[1] = true;

    for (ll i = 2; i * i <= MAX; i++) {
        if (p[i]) continue;

        for (ll j = i * i; j <= MAX; j += i) {
            p[j] = true;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);

    vector<bool> p;

    p.resize(MAX + 1);
    get_prime(p);

    int t;

    cin >> t;
    while (t--) {
        int n, f = 0;
        vector<ll> v, s;

        cin >> n;
        v.resize(n);
        s.resize(n);

        for (int i = 0; i < n; i++) {
            cin >> v[i];
            s[i] = i ? s[i - 1] + v[i] : v[i];
        }

        for (int l = 2; l <= n; l++) {
            if (!p[(int)s[l - 1]]) {
                cout << "Shortest primed subsequence is length " << l << ": ";
                for (int j = 0; j < l; j++) {
                    cout << v[j] << " ";
                }
                cout << "\n";
                f = 1;
                break;
            }
            for (int i = 1; i + l <= n; i++) {
                if (!p[(int)s[i + l - 1] - (int)s[i - 1]]) {
                    cout << "Shortest primed subsequence is length " << l << ": ";
                    for (int j = i; j < i + l; j++) {
                        cout << v[j] << " ";
                    }
                    cout << "\n";
                    f = 1;
                    break;
                }
            }
            if (f) break;
        }

        if (!f) {
            cout << "This sequence is anti-primed.\n";
        }
    }
}