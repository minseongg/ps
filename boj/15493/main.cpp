#include <iostream>
#include <map>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

using ll = long long;
using til = tuple<int, ll>;
using tiil = tuple<int, int, ll>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    auto cmp = [](tiil l, tiil r) { return get<2>(l) < get<2>(r); };
    priority_queue<tiil, vector<tiil>, decltype(cmp)> pq(cmp);
    vector<til> left, right;
    int n, k;
    cin >> n >> k;
    left.resize(n);
    right.resize(n);
    for (int i = 0; i < n; i++) {
        ll x;
        cin >> x;
        left[(i + 1) % n] = { i, x };
        right[i] = { (i + 1) % n, x };
        pq.push({ i, (i + 1) % n, x });
    }

    ll ans = 0;
    int it = 0;
    while (it < k) {
        auto [ l, r, len ] = pq.top();
        pq.pop();

        if (get<0>(left[r]) != l || get<0>(right[l]) != r) { continue; }
        ans += len;

        auto [ l_left, len_left ] = left[l];
        auto [ r_right, len_right ] = right[r];
        ll mod_len = len_left - len + len_right;
        right[l_left] = { r_right, mod_len };
        left[r_right] = { l_left, mod_len };
        pq.push({ l_left, r_right, mod_len });
        left[l] = { -1, -1 };
        right[l] = { -1, -1 };
        left[r] = { -1, -1 };
        right[r] = { -1, -1 };
        it++;
    }

    cout << ans << "\n";
}