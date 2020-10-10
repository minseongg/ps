#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

int pisano(int x) {
    int a = 0, b = 1;

    for (int i = 1;; i++) {
        if (b % x == 0) return i;

        int c = (a + b) % x;

        a = b;
        b = c;
    }
}

int solve(int n, int x, vector<int> &ans) {
    int c = 1e9, t = x;

    for (int j = 2; j < x; j++) {
        int k = 0;

        while (!(t % j)) {
            k++;
            t /= j;
        }
        
        if (k) c = min(c, ans[j] / k);
    }

    if (t == 1) {
        ans[x] = c;
    } else {
        int l = pisano(x), q = n / l;

        for (int j = 1;; j++) {
            if (!q) break;

            ans[x] += q;

            if (j != 2 || x != 2) q /= x;
        }
    }

    return ans[x];
}

int main() {
    int n, p;
    vector<int> ans;

    cin >> n >> p;
    ans.resize(p+1);
    for (int i = 2; i <= p; i++) {
        cout << solve(n, i, ans) << endl;
    }
}