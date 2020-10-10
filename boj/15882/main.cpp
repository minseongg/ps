#include <iostream>
#include <vector>

using namespace std;

const int XXX = 0;
const int XXO = 1;
const int XOX = 2;
const int OXX = 3;
const int XOO = 4;
const int OXO = 5;
const int OOX = 6;
const int OOO = 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, ans = -1e9;
    vector<vector<int>> p, d;

    cin >> n;

    p.resize(n);
    d.resize(n);
    for (int i = 0; i < n; i++) {
        p[i].resize(3);
        d[i].resize(8);

        cin >> p[i][0] >> p[i][1] >> p[i][2];
    }

    for (int i = 1; i < n; i++) {
        d[i][XXX] = max(d[i - 1][OXX], d[i - 1][XXX]);
        d[i][XOX] = max(d[i - 1][OXO], d[i - 1][XXO]);
        d[i][OXX] = max(d[i - 1][OOX], d[i - 1][XOX]);
        d[i][OOX] = max(d[i - 1][OOO], d[i - 1][XOO]);
        d[i][XXO] = max(d[i - 1][OXX] + p[i][0], d[i - 1][XXX]);
        d[i][XOO] = max(d[i - 1][OXO] + p[i][0] + p[i][2], d[i - 1][XXO] + p[i][2]);
        d[i][OXO] = max(d[i - 1][OOX] + p[i][0] + p[i][1], d[i - 1][XOX] + p[i][1]);
        d[i][OOO] = max(d[i - 1][OOO] + p[i][0] + p[i][1] + p[i][2], d[i - 1][XOO] + p[i][1] + p[i][2]);
    }

    for (int i = 0; i < 8; i++) {
        ans = max(ans, d[n - 1][i]);
    }

    cout << ans << "\n";
}