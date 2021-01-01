#include <iostream>
#include <map>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

using tii = tuple<int, int>;
using tiii = tuple<int, int, int>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    auto cmp = [](tiii l, tiii r) { return get<2>(l) > get<2>(r); };
    priority_queue<tiii, vector<tiii>, decltype(cmp)> pq(cmp);
    vector<tii> left, right;
    int n, k, p, f;
    cin >> n >> k;
    cin >> p;
    left.resize(n);
    right.resize(n);
    for (int i = 1; i < n; i++) {
        cin >> f;
        pq.push({ i - 1, i, f - p });
        left[i] = { i - 1, f - p };
        right[i - 1] = { i, f - p };
        p = f;
    }
    left[0] = { -1, -1 };
    right[n - 1] = { -1, -1 };

    int ans = 0, it = 0;
    while (it < k) {
        auto [ l, r, len ] = pq.top();
        pq.pop();

        if (get<0>(left[r]) != l || get<0>(right[l]) != r) { continue; }
        ans += len;

        auto [ l_left, len_left ] = left[l];
        auto [ r_right, len_right ] = right[r];

        if (l_left == -1 && r_right == -1) {
            break;
        } else if (l_left == -1) {
            right[l] = { -1, -1 };
            left[r] = { -1, -1 };
            right[r] = { -1, -1 };
            left[r_right] = { -1, -1 };
        } else if (r_right == -1) {
            left[l] = { -1, -1 };
            right[l] = { -1, -1 };
            left[r] = { -1, -1 };
            right[l_left] = { -1, -1 };
        } else {
            int mod_len = len_left - len + len_right;
            right[l_left] = { r_right, mod_len };
            left[r_right] = { l_left, mod_len };
            pq.push({ l_left, r_right, mod_len });
            left[l] = { -1, -1 };
            right[l] = { -1, -1 };
            left[r] = { -1, -1 };
            right[r] = { -1, -1 };
        }
        it++;
    }

    cout << ans << "\n";
}