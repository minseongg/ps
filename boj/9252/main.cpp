#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int LEFT = 0;
const int UP = 1;
const int DIAG = 2;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string a, b;
    cin >> a >> b;
    int sza = (int)a.size(), szb = (int)b.size();

    vector<vector<int>> d, trace;
    d.resize(sza + 1); trace.resize(sza + 1);
    for (int i = 0; i <= sza; i++) { d[i].resize(szb + 1); trace[i].resize(szb + 1); }
    for (int i = 1; i <= sza; i++) {
        for (int j = 1; j <= szb; j++) {
            d[i][j] = d[i - 1][j]; trace[i][j] = UP;
            if (d[i][j] < d[i][j - 1]) { d[i][j] = d[i][j - 1]; trace[i][j] = LEFT; }
            if (a[i - 1] == b[j - 1] && d[i][j] < d[i - 1][j - 1] + 1) { d[i][j] = d[i - 1][j - 1] + 1; trace[i][j] = DIAG; }
        }
    }
    
    int ans = d[sza][szb];
    cout << ans << "\n";
    if (ans == 0) { return 0; }
    string s;
    int ty = sza, tx = szb;
    while (tx && ty) {
        if (trace[ty][tx] == DIAG) {
            s += a[ty - 1];
            ty--; tx--;
        } else if (trace[ty][tx] == UP) {
            ty--;
        } else {
            tx--;
        }
    }
    reverse(s.begin(), s.end());
    cout << s << "\n";
}
    
