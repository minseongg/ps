#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    vector<vector<int>> v;

    cin >> n >> k;
    v.resize(n);
    for (int i = 0; i < n; i++) { v[i].resize(n); }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> v[i][j];
        }
    }

    for (int i = 0; i < n * k; i++) {
        for (int j = 0; j < n * k; j++) {
            cout << v[i / k][j / k] << " ";
        }
        cout << "\n";
    }
}
