#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, t = 0;
    vector<int> a, d;

    cin >> n;

    a.resize(n);
    d.resize(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());

    for (int i = n - 1; i >= 0; i--) {
        d[i] = 1;

        for (int j = i + 1; j < n; j++) {
            if (a[j] % a[i] == 0) {
                d[i] = max(d[i], d[j] + 1);
            }
        }

        t = max(t, d[i]);
    }

    cout << n - t << "\n";
}
