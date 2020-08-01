#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

const ll INF = 1e15;

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    vector<int> l;
    vector<ll> d, s;

    cin >> n >> m;

    l.resize(n);
    d.resize(n);
    s.resize(n);

    for (int i = 0; i < n; i++) {
        d[i] = INF;
    }

    for (int i = 0; i < m; i++) {
        cin >> l[i] >> s[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i - l[j] < 0) {
                d[i] = min(d[i], s[j]);
            } else {
                d[i] = min(d[i], d[i - l[j]] + s[j]);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << d[i] << "\n";
    }
}