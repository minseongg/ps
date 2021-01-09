#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string a, b, c;
    cin >> a >> b >> c;
    int sza = (int)a.size(), szb = (int)b.size(), szc = (int)c.size();
    vector<vector<vector<int>>> d;
    d.resize(sza + 1);
    for (int i = 0; i <= sza; i++) {
        d[i].resize(szb + 1);
        for (int j = 0; j <= szb; j++) {
            d[i][j].resize(szc + 1);
        }
    }
    for (int i = 1; i <= sza; i++) {
        for (int j = 1; j <= szb; j++) {
            for (int k = 1; k <= szc; k++) {
                d[i][j][k] = max(d[i][j][k], d[i - 1][j][k]);
                d[i][j][k] = max(d[i][j][k], d[i][j - 1][k]);
                d[i][j][k] = max(d[i][j][k], d[i][j][k - 1]);
                if (a[i - 1] == b[j - 1] && b[j - 1] == c[k - 1]) { d[i][j][k] = max(d[i][j][k], d[i - 1][j - 1][k - 1] + 1); }
            }
        }
    }
    cout << d[sza][szb][szc] << "\n";
}
