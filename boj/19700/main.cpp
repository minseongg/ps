#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int n;
    vector<pair<int, int>> p;
    vector<pair<int, int>> team;

    cin >> n;
    p.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i].first >> p[i].second;
        p[i].first = -p[i].first;
    }

    sort(p.begin(), p.end());

    multiset<int> s;
    auto it = s.begin();
    
    for (int i = 0; i < n; i++) {
        if (s.empty()) {
            s.insert(1);
            continue;
        }

        it = s.lower_bound(p[i].second);
        
        if (it == s.begin()) {
            s.insert(1);
            continue;
        }
        it--;

        int v = *it;
        s.erase(it);
        s.insert(v + 1);
    }

    cout << s.size() << "\n";
}
