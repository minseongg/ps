#include <iostream>
#include <vector>

using namespace std;

const int MAX = 1e6 + 5;

int main() {
    ios::sync_with_stdio(false);

    int n, m,ans = 0;
    vector<int> q, v;

    v.resize(MAX);

    cin >> n;

    for (int i = 0; i < n; i++) {
        int x;

        cin >> x;
        q.emplace_back(x);
    }

    cin >> m;

    for (int i = 0; i < n; i++) {
        if (q[i] >= m) continue;

        if (v[m - q[i]]) ans++;

        v[q[i]] = 1;
    }

    cout << ans << "\n";
}