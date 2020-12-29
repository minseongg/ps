#include <iostream>
#include <string>

using namespace std;

using ull = unsigned long long;

const ull REP = 1e6;
const ull INF = 1e16;
const ull ROOT_INF = 1e8;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string s1, s2;
    ull c, len_s1, len_s2, pre_s1 = 0, pre_s2 = 0, suf_s1 = 0, suf_s2 = 0;

    cin >> s1 >> s2 >> c;
    len_s1 = (ull)s1.size();
    len_s2 = (ull)s2.size();
    while (s1[pre_s1] == '0') { pre_s1++; }
    while (s2[pre_s2] == '0') { pre_s2++; }
    while (s1[len_s1 - suf_s1 - 1] == '0') { suf_s1++; }
    while (s2[len_s2 - suf_s2 - 1] == '0') { suf_s2++; }

    if (len_s1 == pre_s1 && len_s2 == pre_s2) {
        cout << 0 << "\n";
        return 0;
    }

    ull ans = -1;

    ull t = 0;
    for (int i = 0; i < len_s1; i++) {
        t = (s1[i] == '0' ? t + 1 : 0);
        if (t == c) {
            ans = min(ans, i - c + 1);
            break;
        }
    }

    t = 0;
    for (int i = 0; i < len_s2; i++) {
        t = (s2[i] == '0' ? t + 1 : 0);
        if (t == c) {
            ans = min(ans, REP * len_s1 + i - c + 1);
            break;
        }
    }

    if (suf_s1 + pre_s1 >= c) {
        ans = min(ans, len_s1 - suf_s1);
    }

    if (suf_s1 + pre_s2 >= c) {
        ans = min(ans, REP * len_s1 - suf_s1);
    }

    if (suf_s2 + pre_s1 >= c) {
        ans = min(ans, REP * len_s1 + len_s2 - suf_s2);
    }

    if (suf_s2 + pre_s2 >= c) {
        ans = min(ans, 2 * REP * len_s1 + 2 * len_s2 - suf_s2);
    }

    if (len_s1 == pre_s1) {
        if (REP * len_s1 + pre_s2 >= c) {
            ans = 0;
        }

        if (suf_s2 + REP * len_s1 + pre_s2 >= c) {
            ans = min(ans, REP * len_s1 + len_s2 - suf_s2);
        }
    }

    if (len_s2 == pre_s2) {
        t = (max(c - pre_s1, 0ull) + len_s2 - 1) / len_s2;
        if (t > 0 && t <= 2 * ROOT_INF && t * REP * len_s1 + t * (t - 1) * len_s2 / 2 + c <= INF) {
            ans = min(ans, t * REP * len_s1 + t * (t - 1) * len_s2 / 2);
        }

        t = (max(c - suf_s1 - pre_s1, 0ull) + len_s2 - 1) / len_s2;
        if (t > 0 && t <= 2 * ROOT_INF && t * REP * len_s1 + t * (t - 1) * len_s2 / 2 + c - suf_s1 <= INF) {
            ans = min(ans, t * REP * len_s1 + t * (t - 1) * len_s2 / 2 - suf_s1);
        }
    }

    cout << (long long)ans << "\n";
}