#include <iostream>
#include <vector>

using namespace std;

const int DATE = 365;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    vector<int> v(DATE + 1);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int s, e;
        cin >> s >> e;
        for (int j = s - 1; j < e; j++) {
            v[j]++;
        }
    }

    int it = 0, t = 0, ans = 0;
    for (int i = 0; i <= DATE; i++) {
        if (v[i] == 0) {
            ans += t * (i - it);
            t = 0;
        } else {
            if (t == 0) { it = i; }
            t = max(t, v[i]);
        }
    }

    cout << ans << "\n";
}
