#include <iostream>
#include <vector>
#include <tuple>
#include <list>
#include <algorithm>

using namespace std;

using query = tuple<int, int, int>;

const int BUCKET_SZ = 330;
const int MAX_VAL = 1e5;

inline bool cmp_query_mo(const query &a, const query &b) {
    return get<2>(a) / BUCKET_SZ != get<2>(b) / BUCKET_SZ ? get<2>(a) < get<2>(b) : get<1>(a) < get<1>(b);
}

inline void insert(int k, vector<list<int>> &mark, vector<int> &cnt, vector<int> &buckets) {
    if (mark[k].size() > 1) {
        int len = mark[k].front() - mark[k].back();
        if (cnt[len]++ == 0) { buckets[len / BUCKET_SZ]++; }
    }
}

inline void erase(int k, vector<list<int>> &mark, vector<int> &cnt, vector<int> &buckets) {
    if (mark[k].size() > 1) {
        int len = mark[k].front() - mark[k].back();
        if (--cnt[len] == 0) { buckets[len / BUCKET_SZ]--; }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    vector<int> a, s;
    vector<query> queries;
    cin >> n;
    a.resize(n + 1); s.resize(n + 1);
    s[0] = MAX_VAL;
    for (int i = 1; i <= n; i++) { cin >> a[i]; s[i] = s[i - 1] + a[i]; }
    cin >> m;
    queries.resize(m);
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        queries[i] = { i, l - 1, r + 1 };
    }
    sort(queries.begin(), queries.end(), cmp_query_mo);

    vector<int> ans(m), cnt(BUCKET_SZ * BUCKET_SZ), buckets(BUCKET_SZ);
    vector<list<int>> mark((MAX_VAL << 1) + 1);
    int it_l = 0, it_r = 0;
    for (int i = 0; i < m; i++) {
        auto [ idx, l, r ] = queries[i];
        int len;
        
        if (it_r < r) {
            for (; it_r < r; it_r++) {
                erase(s[it_r], mark, cnt, buckets);
                mark[s[it_r]].emplace_front(it_r);
                insert(s[it_r], mark, cnt, buckets);
            }
        } else {
            for (; it_r > r; it_r--) {
                erase(s[it_r - 1], mark, cnt, buckets);
                mark[s[it_r - 1]].pop_front();
                insert(s[it_r - 1], mark, cnt, buckets);
            }
        }

        if (it_l < l) {
            for (; it_l < l; it_l++) {
                erase(s[it_l], mark, cnt, buckets);
                mark[s[it_l]].pop_back();
                insert(s[it_l], mark, cnt, buckets);
            }
        } else {
            for (; it_l > l; it_l--) {
                erase(s[it_l - 1], mark, cnt, buckets);
                mark[s[it_l - 1]].emplace_back(it_l - 1);
                insert(s[it_l - 1], mark, cnt, buckets);
            }
        }

        int t = 0;
        for (int j = BUCKET_SZ - 1; j >= 0; j--) {
            if (buckets[j]) {
                for (int k = (j + 1) * BUCKET_SZ - 1; k >= j * BUCKET_SZ; k--) {
                    if (cnt[k]) {
                        t = k;
                        break;
                    }
                }
                break;
            }
        }
        ans[idx] = t;
    }

    for (int i = 0; i < m; i++) {
        cout << ans[i] << "\n";
    }
}