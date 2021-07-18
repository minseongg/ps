#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int p, m;
    vector<pair<int, string>> info;
    vector<pair<int, vector<pair<string, int>>>> s;

    cin >> p >> m;
    for (int i = 0; i < p; i++) {
        int l;
        string n;
        cin >> l >> n;
        info.emplace_back(l, n);
    }

    for (auto [ l, n ] : info) {
        bool flag = false;

        for (auto &[ ll, r ] : s) {
            if (r.size() == m) {
                continue;
            }

            if (ll - 10 <= l && l <= ll + 10) {
                r.emplace_back(n, l);
                flag = true;
                break;
            }
        }

        if (!flag) {
            vector<pair<string, int>> t = {{n, l}};
            s.emplace_back(l, t);
        }
    }

    for (auto &[ _, r ] : s) {
        sort(r.begin(), r.end());
        
        if (r.size() == m) {
            cout << "Started!\n";
        } else {
            cout << "Waiting!\n";
        }

        for (auto &[ n, l ] : r) {
            cout << l << " " << n << "\n";
        }
    }
}
