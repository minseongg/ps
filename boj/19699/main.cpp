#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int bitcount(int x) {
    int c = 0;
    
    while (x) {
        if (x % 2) {
            c++;
        }
        x >>= 1;
    }

    return c;
}

bool is_prime(int x) {
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int n, m;
    vector<int> h;
    vector<int> ans;

    cin >> n >> m;
    h.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }

    for (int i = 0; i < (1 << n); i++) {
        if (bitcount(i) == m) {
            int s = 0;

            for (int t = 0; t < n; t++) {
                if (i & (1 << t)) {
                    s += h[t];
                }
            }

            if (is_prime(s)) {
                ans.emplace_back(s);
            }
        }
    }

    sort(ans.begin(), ans.end());
    auto last = unique(ans.begin(), ans.end());
    ans.erase(last, ans.end());

    if (ans.size()) {
        for (int x: ans) {
            cout << x << " ";
        }
    } else {
        cout << "-1";
    }
    cout << "\n";
}
