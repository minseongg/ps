#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    vector<int> s, ans;

    cin >> n >> k;

    k--;

    for (int su = 0; su < 5 * n; su++) {
        vector<int> f;

        int t = su;

        if (t == 0) {
            f.emplace_back(0);
        } else {
            while (t) {
                f.emplace_back(t & 1);
                t >>= 1;
            }
        }

        reverse(f.begin(), f.end());

        for (int x : f) {
            s.emplace_back(x);
        }
    }

    for (int i = 0; i < 5 * n; i++) {
        if (i % n == k) {
            cout << s[i] << " ";
        }
    }
    cout << "\n";
}