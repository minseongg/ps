#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int INF = 1e8;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, ans = INF;
    vector<int> v;

    cin >> n;
    v.resize(n * 2);
    for (int i = 0; i < n * 2; i++) {
        cin >> v[i];
    }
    sort(v.begin(), v.end());

    for (int i = 0; i < n; i++) {
        ans = min(ans, v[i] + v[2 * n - 1 - i]);
    }

    cout << ans << "\n";
}