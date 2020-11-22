#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t, d[41][2];

    d[0][0] = 1; d[0][1] = 0;
    d[1][0] = 0; d[1][1] = 1;
    for (int i = 2; i <= 40; i++) {
        d[i][0] = d[i - 1][0] + d[i - 2][0];
        d[i][1] = d[i - 1][1] + d[i - 2][1];
    }

    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << d[n][0] << " " << d[n][1] << "\n";
    }
}