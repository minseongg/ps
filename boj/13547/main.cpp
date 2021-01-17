#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

using query = tuple<int, int, int>;

const int BUCKET_SZ = 330;
const int MAX_VAL = 1e6;

inline bool query_cmp_mo(const query &a, const query &b) {
    return get<2>(a) / BUCKET_SZ != get<2>(b) / BUCKET_SZ ? get<2>(a) < get<2>(b) : get<1>(a) < get<1>(b);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    vector<int> a, ans;
    vector<query> queries;
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) { cin >> a[i]; }
    cin >> m;
    queries.resize(m); ans.resize(m);
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        queries[i] = { i, l - 1, r };
    }
    sort(queries.begin(), queries.end(), query_cmp_mo);

    vector<int> freq(MAX_VAL + 1);
    int it_l = 0, it_r = 0, cnt = 0;
    for (int i = 0; i < m; i++) {
        auto [ idx, l, r ] = queries[i];

        if (it_r < r) {
            for (; it_r < r; it_r++) {
                if (freq[a[it_r]]++ == 0) {
                    cnt++;
                }
            }
        } else {
            for (; it_r > r; it_r--) {
                if (--freq[a[it_r - 1]] == 0) {
                    cnt--;
                }
            }
        }

        if (it_l < l) {
            for (; it_l < l; it_l++) {
                if (--freq[a[it_l]] == 0) {
                    cnt--;
                }
            }
        } else {
            for (; it_l > l; it_l--) {
                if (freq[a[it_l - 1]]++ == 0) {
                    cnt++;
                }
            }
        }

        ans[idx] = cnt;
    }

    for (int i = 0; i < m; i++) {
        cout << ans[i] << "\n";
    }
}