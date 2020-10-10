#include <iostream>
#include <string>
#include <vector>

using namespace std;

using ll = long long;

const int P_UPPER = 3000;
const int S_UPPER = 3000;

vector<vector<ll>> cnt, num, sym;

void get_prime(vector<int> &v) {
    vector<int> s;

    s.resize(P_UPPER + 1);
    s[1] = 1;
    for (int i = 2; i <= P_UPPER; i++) {
        if (s[i]) continue;
        for (int j = i * i; j <= P_UPPER; j += i) {
            s[j] = 1;
        }
    }

    int c = 0, d = 0;

    for (int i = 1; i <= P_UPPER; i++) {
        if (s[i]) continue;

        v.push_back(i);
    }
}

inline ll len_of_prime(int x) {
    ll c = 0;

    while (x) {
        c++;
        x /= 10;
    }

    return c;
}

void get_table(vector<int> &p) {
    int sz = (int)p.size();

    cnt.resize(sz + 1);
    for (int i = 0; i <= sz; i++) cnt[i].resize(S_UPPER + 1);
    num.resize(sz + 1);
    for (int i = 0; i <= sz; i++) num[i].resize(S_UPPER + 1);
    sym.resize(sz + 1);
    for (int i = 0; i <= sz; i++) sym[i].resize(S_UPPER + 1);

    for (int i = sz - 1; i >= 0; i--) {
        int x = p[i];

        for (int j = 0; j <= S_UPPER; j++) {
            if (j < x) {
                cnt[i][j] = cnt[i+1][j];
                num[i][j] = num[i+1][j];
                sym[i][j] = sym[i+1][j];
            } else if (j == x) {
                cnt[i][j] = cnt[i+1][j] + 1;
                num[i][j] = num[i+1][j] + 1;
                sym[i][j] = sym[i+1][j] + len_of_prime(x);
            } else {
                cnt[i][j] = cnt[i+1][j] + cnt[i+1][j-x];
                num[i][j] = num[i+1][j] + cnt[i+1][j-x] + num[i+1][j-x];
                sym[i][j] = sym[i+1][j] + len_of_prime(x) * cnt[i+1][j-x] + sym[i+1][j-x];
            }
        }
    }
}

inline ll len_of_fixed_sum(int s, int p) {
    return sym[p][s] + 2 * num[p][s] + 2 * cnt[p][s];
}

inline ll len_of_fixed_sum_with_prefix(int s, int p, vector<int> &prefix) {
    ll preflen = 1;

    for (int x : prefix) {
        preflen += len_of_prime(x) + 2;
    }

    if (s == 0) return preflen + 1;
    return sym[p][s] + 2 * num[p][s] + (preflen + 1) * cnt[p][s];
}

string ptos(vector<int> &prefix) {
    string s = "";
    int sz = (int)prefix.size();

    s += "[";
    for (int i = 0; i < sz; i++) {
        s += to_string(prefix[i]);
        
        if (i == sz - 1) break;

        s += ", ";
    }
    s += "], ";

    return s;
}

void solve_with_prefix(int s, int idx, ll a, ll b, vector<int> &p, vector<int> &prefix) {
    int sz = (int)p.size();

    if (s == 0) {
        cout << ptos(prefix).substr(a, b-a+1);
        return;
    }

    ll c = 0;
    for (int i = idx; i < sz; i++) {
        int x = p[i];

        if (x > s) return;

        prefix.push_back(x);
        ll l = len_of_fixed_sum_with_prefix(s-(ll)x, i+1, prefix);
        ll lo = c, hi = c + l - 1;
        ll mlo = max(lo, a), mhi = min(hi, b);

        if (mlo <= mhi) {
            solve_with_prefix(s-(ll)x, i+1, mlo-c, mhi-c, p, prefix);
        }
        prefix.pop_back();

        c += l;
        if (c > (1e18)) break;
    }
}

void solve(ll a, ll b, vector<int> &p) {
    ll c = 1;
    vector<int> prefix;

    for (int i = 1; i <= S_UPPER; i++) {
        ll l = len_of_fixed_sum(i, 0);
        ll lo = c, hi = c + l - 1;
        ll mlo = max(lo, a), mhi = min(hi, b);

        if (mlo <= mhi) {
            solve_with_prefix(i, 0, mlo-c, mhi-c, p, prefix);
        }

        c += l;
        if (c > (1e18)) break;
    }
}

int main() {
    ll a, b;
    vector<int> p;

    cin >> a >> b;
    get_prime(p);
    get_table(p);
    solve(a, b, p);
    cout << "\n";

    return 0;
}