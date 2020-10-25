#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, t;
    cin >> n;
    t = n;

    vector<int> ans;

    for (int i = 2; i * i <= n; i++) {
        while (t % i == 0) {
            ans.emplace_back(i);
            t /= i;
        }
    }

    if (t > 1) {
        ans.emplace_back(t);
    }

    for (int x : ans) {
        cout << x << "\n";
    }
}