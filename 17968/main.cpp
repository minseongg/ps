#include <iostream>
#include <vector>

using namespace std;

using vi = vector<int>;

int main() {
    ios::sync_with_stdio(false);

    int n;
    vi v, t;

    cin >> n;
    v.resize(n + 1);
    t.resize(n + 1);
    v[0] = v[1] = 1;
    for (int i = 2; i <= n; i++) {
        fill(t.begin(), t.end(), 0);
        for (int k = 1; i - 2 * k >= 0; k++) {
            int target = 2 * v[i - k] - v[i - 2 * k];

            if (target <= 0 || target > n) continue;

            t[target] = 1;
        }

        for (int k = 1; k <= n; k++) {
            if (!t[k]) {
                v[i] = k;
                break;
            }
        }
    }

    cout << v[n] << "\n";
}