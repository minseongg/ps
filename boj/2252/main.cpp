#include <iostream>
#include <vector>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

vi topological_sort(int v, vvi &e) {
    vi ans, in(v);
    for (int x = 0; x < v; x++) {
        for (int &y : e[x]) {
            in[y]++;
        }
    }

    for (int x = 0; x < v; x++) {
        if (!in[x]) {
            ans.emplace_back(x);
        }
    }

    for (int i = 0; i < v; i++) {
        int x = ans[i];
        for (int &y : e[x]) {
            in[y]--;
            if (!in[y]) {
                ans.emplace_back(y);
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    vvi e;
    cin >> n >> m;
    e.resize(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        e[x - 1].emplace_back(y - 1);
    }
    auto ans = topological_sort(n, e);
    for (auto &x : ans) {
        cout << x + 1 << " ";
    }
    cout << "\n";
}