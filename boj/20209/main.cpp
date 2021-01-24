#include <iostream>
#include <vector>

using namespace std;

void f(int now, int k, int n, vector<int> &s, int &ans, vector<vector<int>> &b, vector<int> &a) {
    if (now == k) {
        int t = 0;
        vector<int> c = a;
        for (int i = 0; i < k; i++) {
            for (int &x : b[i]) {
                c[x] = (c[x] + s[i] * (i + 1)) % 5;
            }
        }    
        
        for (int x : s) {
            t += x;
        }

        int flag = 1;
        for (int i = 0; i < n - 1; i++) {
            if (c[i] != c[i + 1]) { flag = 0; break; }
        }
        if (flag) { ans = min(ans, t); }
        return;
    }

    for (int i = 0; i < 5; i++) {
        s[now] = i;
        f(now + 1, k, n, s, ans, b, a);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    vector<int> a;
    vector<vector<int>> b;

    cin >> n >> k;
    a.resize(n);
    b.resize(k);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < k; i++) {
        int x;
        cin >> x;
        b[i].resize(x);
        for (int j = 0; j < x; j++) {
            cin >> b[i][j];
            b[i][j]--;
        }
    }

    int ans = 100000;
    vector<int> s(k);
    f(0, k, n, s, ans, b, a);

    cout << (ans == 100000 ? -1 : ans) << "\n";
}
