#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, tx, ty, flag[4] = { 1, 1, 1, 1 };
    vector<int> x, y;

    cin >> n;
    x.resize(n); y.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }
    cin >> tx >> ty;

    for (int i = 0; i < n; i++) { if (x[i] > tx && abs(y[i] - ty) <= abs(x[i] - tx)) { flag[0] = 0; break; } }
    for (int i = 0; i < n; i++) { if (x[i] < tx && abs(y[i] - ty) <= abs(x[i] - tx)) { flag[1] = 0; break; } }
    for (int i = 0; i < n; i++) { if (y[i] > ty && abs(y[i] - ty) >= abs(x[i] - tx)) { flag[2] = 0; break; } }
    for (int i = 0; i < n; i++) { if (y[i] < ty && abs(y[i] - ty) >= abs(x[i] - tx)) { flag[3] = 0; break; } }

    if (flag[0] || flag[1] || flag[2] || flag[3]) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}