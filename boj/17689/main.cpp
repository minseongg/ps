#include <iostream>
#include <tuple>
#include <queue>
#include <vector>

using namespace std;

using ll = long long;
using tiill = tuple<int, int, ll>;
using till = tuple<int, ll>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    vector<int> c;
    auto cmp = [](tiill left, tiill right) { return get<2>(left) < get<2>(right); };
    priority_queue<tiill, vector<tiill>, decltype(cmp)> pq(cmp);
    vector<till> left, right;
    cin >> n;
    c.resize(n);
    left.resize(n + 1);
    right.resize(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        pq.push({ i, i + 1, c[i] });
        left[i + 1] = { i, c[i] };
        right[i] = { i + 1, c[i] };
    }
    left[0] = { -1, -1 };
    right[n] = { -1, -1 };

    int it = 0;
    ll ans = 0;
    while (it < (n + 1) / 2) {
        if (pq.empty()) break;

        auto [ l, r, val ] = pq.top();
        pq.pop();

        if (get<0>(left[r]) != l || get<0>(right[l]) != r) { continue; }
        ans += val;

        cout << ans << "\n";

        auto [ l_left, val_left ] = left[l];
        auto [ r_right, val_right ] = right[r];

        if (l_left == -1 && r_right == -1) { break; }

        if (l_left == -1) {
            right[l] = { -1, -1 };
            left[r] = { -1, -1 };
            right[r] = { -1, -1 };
            left[r_right] = { -1, -1 };
        } else if (r_right == -1) {
            left[r] = { -1, -1 };
            left[l] = { -1, -1 };
            right[l] = { -1, -1 };
            right[l_left] = { -1, -1 };
        } else {
            right[l_left] = { r_right, val_left + val_right - val };
            left[l] = { -1, -1 };
            right[l] = { -1, -1 };
            left[r] = { -1, -1 };
            right[r] = { -1, -1 };
            left[r_right] = { l_left, val_left + val_right - val };
            pq.push({ l_left, r_right, val_left + val_right - val });
        }

        it++;
    }
}