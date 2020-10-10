#include <iostream>
#include <vector>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

inline int acc(int idx, vi &v) {
    int sz = (int)v.size();

    if (idx < 0 || idx >= sz) return 0;
    return v[idx];
}

int f(int m, int n, vvi &arr) {
    int ans = 0;
    vi mx, d;

    mx.resize(m);
    d.resize(n);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int t = 0;

            t = max(t, acc(i-2, mx));
            t = max(t, acc(i-3, mx));
            t = max(t, acc(j-2, d));
            t = max(t, acc(j-3, d));
            t += arr[i][j];

            d[j] = t;
            mx[i] = max(mx[i], t);
            ans = max(ans, t);
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);

    int m, n;
    vvi arr;

    while (1) {
        cin >> m >> n;

        if (m + n == 0) break;

        arr.resize(m);
        for (int i = 0; i < m; i++) {
            arr[i].resize(n);
            for (int j = 0; j < n; j++) {
                cin >> arr[i][j];
            }
        }

        cout << f(m, n, arr) << "\n";
    }
}