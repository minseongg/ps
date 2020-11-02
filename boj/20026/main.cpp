#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    vector<int> v;
    ll ans_min = 0, ans_max = 0, it_max = 0, it_min = 0;
    
    cin >> n;
    v.resize(n * (n - 1) / 2);
    for (int i = 0; i < n * (n - 1) / 2; i++) { cin >> v[i]; }
    sort(v.begin(), v.end());

    for (int i = 0; i < n - 1; i++) {
        ans_min += v[it_min];
        ans_max += v[it_max];
        it_min++;
        it_max += i + 1;
    }

    cout << ans_min << " " << ans_max << "\n";
}