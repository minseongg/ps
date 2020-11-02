#include <iostream>
#include <vector>

using namespace std;

int solve(vector<int> &v, int l, int r) {
    if (l == r) { return 1; }
    
    int ans = 0, m = (l + r) / 2;

    ans = max(ans, solve(v, l, m));
    ans = max(ans, solve(v, m + 1, r));

    int it_l = m, it_r = m + 1, h = min(v[it_l], v[it_r]);

    while (true) {
        h = min(h, v[it_l]); h = min(h, v[it_r]);
        ans = max(ans, min(h, it_r - it_l + 1));

        if (h < it_r - it_l + 1) { break; }
        if (it_l == l && it_r == r) { break; }
        
        int next_l = (it_l == l ? 0 : v[it_l - 1]);
        int next_r = (it_r == r ? 0 : v[it_r + 1]);

        if (next_l > next_r) { it_l--; }
        else { it_r++; }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    vector<int> v;

    cin >> n;
    v.resize(n);
    for (int i = 0; i < n; i++) { cin >> v[i]; }

    cout << solve(v, 0, n - 1) << "\n";
}