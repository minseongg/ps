#include <iostream>
#include <vector>

using namespace std;

const int NOFOOD = -1, NOTUPDATED = -2;

int main() {
    ios::sync_with_stdio(false);

    int n;
    vector<vector<int>> d;
    vector<int> ans;

    cin >> n;
    d.resize(n);
    for (int i = 0; i < n; i++) {
        int m;

        cin >> m;
        d[i].resize(10);
        for (int j = 0; j < 10; j++) d[i][j] = NOFOOD;
        for (int j = 0; j < m; j++) {
            int x;

            cin >> x;
            d[i][x - 1] = i == 0 ? 0 : NOTUPDATED;
        }
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < 10; j++) {
            if (d[i][j] == NOFOOD) continue;

            for (int k = 0; k < 10; k++) {
                if (j == k) continue;

                if (d[i - 1][k] != NOFOOD && d[i - 1][k] != NOTUPDATED) {
                    d[i][j] = k;
                    break;
                }
            }
        }
    }

    for (int i = 0; i < 10; i++) {
        if (d[n - 1][i] != NOFOOD && d[n - 1][i] != NOTUPDATED) {
            int it = n - 1, c = i;

            while (it >= 0) {
                ans.emplace_back(c + 1);
                c = d[it][c];
                it--;
            }

            for (int j = n - 1; j >= 0; j--) {
                cout << ans[j] << "\n";
            }

            return 0;
        }
    }

    cout << "-1\n";
}