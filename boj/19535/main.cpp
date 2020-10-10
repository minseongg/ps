#include <iostream>
#include <vector>
#include <queue>

using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);

    int n;
    vector<ll> d;
    vector<pair<int, int>> e;

    ll ans1 = 0, ans2 = 0;

    cin >> n;

    d.resize(n);

    for (int i = 0; i < n - 1; i++) {
        int u, v;

        cin >> u >> v;
        d[u - 1]++;
        d[v - 1]++;

        e.emplace_back(u - 1, v - 1);
    }

    for (auto &p : e) {
        int u = p.first, v = p.second;

        ans1 += (d[u] - 1) * (d[v] - 1);
    }

    for (int v = 0; v < n; v++) {
        ans2 += d[v] * (d[v] - 1) * (d[v] - 2) / 6;
    }

    if (ans1 > ans2 * 3) {
        cout << "D\n";
    } else if (ans1 < ans2 * 3) {
        cout << "G\n";
    } else {
        cout << "DUDUDUNGA\n";
    }
}