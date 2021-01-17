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

    int n, k, m;
    vector<int> a;
    vector<query> queries;
    cin >> n >> k;
    a.resize(n);
    for (int i = 0; i < n; i++) { cin >> a[i]; }
    cin >> m;
    queries.resize(m);
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        queries[i] = { i, l - 1, r };
    }
    sort(queries.begin(), queries.end(), cmp_query_mo);

    vector<int> ans(m), cnt(BUCKET_SZ * BUCKET_SZ), buckets(BUCKET_SZ);
    vector<list<int>> mark(MAX_VAL + 1);
    int it_l = 0, it_r = 0;
    for (int i = 0; i < m; i++) {
        auto [ idx, l, r ] = queries[i];
        int len;
        
        if (it_r < r) {
            for (; it_r < r; it_r++) {
                erase(a[it_r], mark, cnt, buckets);
                mark[a[it_r]].emplace_front(it_r);
                insert(a[it_r], mark, cnt, buckets);
            }
        } else {
            for (; it_r > r; it_r--) {
                erase(a[it_r - 1], mark, cnt, buckets);
                mark[a[it_r - 1]].pop_front();
                insert(a[it_r - 1], mark, cnt, buckets);
            }
        }

        if (it_l < l) {
            for (; it_l < l; it_l++) {
                erase(a[it_l], mark, cnt, buckets);
                mark[a[it_l]].pop_back();
                insert(a[it_l], mark, cnt, buckets);
            }
        } else {
            for (; it_l > l; it_l--) {
                erase(a[it_l - 1], mark, cnt, buckets);
                mark[a[it_l - 1]].emplace_back(it_l - 1);
                insert(a[it_l - 1], mark, cnt, buckets);
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