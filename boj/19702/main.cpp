#include <iostream>
#include <vector>
#include <list>

using namespace std;

using vi = vector<int>;
using vvi = vector<vector<int>>;

list<int> path_to_cycle(int n, list<int> &prev, vvi &a) {
    if (a[prev.front()][prev.back()]) {
        return prev;
    }

    for (auto it = prev.begin();; it++) {
        auto it_next = it;
        it_next++;
        if (it_next == prev.end()) { break; }

        if (a[prev.front()][*it_next] && a[*it][prev.back()]) {
            list<int> next;
            for (auto it_temp = it_next; it_temp != prev.end(); it_temp++) {
                next.push_back(*it_temp);
            }
            for (auto it_temp = prev.begin(); it_temp != it_next; it_temp++) {
                next.push_front(*it_temp);
            }
            return next;
        }
    }
}

list<int> next_path(int n, list<int> &prev, vvi &a) {
    vi visited(n);

    for (int x: prev) {
        visited[x] = 1;
    }

    for (int i = 0; i < n; i++) {
        if (visited[i]) { continue; }
        if (a[i][prev.front()]) {
            prev.push_front(i);
            return prev;
        }
        if (a[i][prev.back()]) {
            prev.push_back(i);
            return prev;
        }
    }

    list<int> cycle = path_to_cycle(n, prev, a);
    
    for (auto it = cycle.begin(); it != cycle.end(); it++) {
        for (int i = 0; i < n; i++) {
            if (visited[i]) { continue; }
            if (a[i][*it]) {
                list<int> next;
                next.push_back(i);
                for (auto it_temp = it; it_temp != cycle.end(); it_temp++) {
                    next.push_back(*it_temp);
                }
                for (auto it_temp = cycle.begin(); it_temp != it; it_temp++) {
                    next.push_back(*it_temp);
                }
                return next;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);

    int n;
    vvi a;

    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) { a[i].resize(n); }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    list<int> ans;

    ans.push_back(0);
    for (int i = 1; i < n; i++) {
        ans = next_path(n, ans, a);
    }
    ans = path_to_cycle(n, ans, a);
    for (int x: ans) {
        cout << x + 1 << " ";
    }
    cout << "\n";
}
