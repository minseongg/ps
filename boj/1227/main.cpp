#include <iostream>
#include <vector>
#include <queue>

using namespace std;

using ll = long long;

using pii = pair<int, int>;
using pll = pair<ll, ll>;

using vpii = vector<pii>;
using vvi = vector<vector<int>>;

using qpii = queue<pii>;

const int SIDE = 2001, HALF = 1000;

inline pii conv(pii p) {
    return {p.first + HALF, p.second + HALF};
}

inline bool valid(int x, int y, vvi &arr, vvi &visited) {
    if (x < 0 || x >= SIDE || y < 0 || y >= SIDE) return false;
    if (visited[x][y] || arr[x][y] == -1) return false;
    return true;
}

inline pll corner_c(int d) {
    if (d <= 0) return {0, 0};

    ll f = (ll)(d / 2), s = (ll)((d - 1) / 2 + 1);
    ll a = f * (f + 2), b = s * (s + 1);

    return {a, b};
}

inline pll side_c(int d, int p) {
    if (d <= 0) return {0, 0};

    ll a = (ll)(d - d / 2), b = (ll)(d / 2);

    if (p % 2) {
        return {a, b};
    } else {
        return {b, a};
    }
}

pll solve(int b, int s, vpii &v) {
    pll ans;
    qpii q;
    vvi arr, visited;
    int dx[] = {0, 1, 0, -1}, dy[] = {-1, 0, 1, 0};

    arr.resize(SIDE); visited.resize(SIDE);
    for (int i = 0; i < SIDE; i++) {
        arr[i].resize(SIDE); visited[i].resize(SIDE);
    }

    for (int i = 0; i < b; i++) {
        pii t = conv(v[i]);

        arr[t.first][t.second] = -1;
    }

    if (!arr[HALF][HALF]) q.push({HALF, HALF});

    while (!q.empty()) {
        pii t = q.front();
        int c = arr[t.first][t.second];

        q.pop();
        if (c <= s && c != 0) {
            if ((t.first + t.second) % 2) {
                ans.second++;
            } else {
                ans.first++;
            }
        }

        for (int i = 0; i < 4; i++) {
            int mx = t.first + dx[i], my = t.second + dy[i];

            if (valid(mx, my, arr, visited)) {
                arr[mx][my] = c + 1;
                visited[mx][my] = 1;
                q.push({mx, my});
            }
        }
    }

    if (!visited[0][0]) return ans;

    vvi side;

    side.resize(4);
    for (int i = 0; i < 4; i++) side[i].resize(SIDE - 1);

    for (int i = 0; i < SIDE - 1; i++) side[0][i] = arr[i][2000];
    for (int i = 0; i < SIDE - 1; i++) side[1][i] = arr[2000][2000-i];
    for (int i = 0; i < SIDE - 1; i++) side[2][i] = arr[2000-i][0];
    for (int i = 0; i < SIDE - 1; i++) side[3][i] = arr[0][i];

    for (int i = 0; i < 4; i++) {
        pll t;

        t = corner_c(s - side[i][0]);
        ans.first += t.first; ans.second += t.second;

        for (int j = 1; j < SIDE - 1; j++) {
            t = side_c(s - side[i][j], j % 2);
            ans.first += t.first; ans.second += t.second;
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);

    int b, s;
    vector<pii> v;

    cin >> b >> s;
    v.resize(b);
    for (int i = 0; i < b; i++) {
        pii t;

        cin >> t.first >> t.second;
        v[i] = t;
    }

    pll ans = solve(b, s, v);
    
    cout << ans.first << " " << ans.second << endl;
}