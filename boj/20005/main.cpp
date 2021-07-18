#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

int m, n, p, hp;
int dy[4] = {-1, 0, 1, 0}, dx[4] = {0, 1, 0, -1};

void bfs(int y, int x, vector<string> &mp, vector<vector<int>> &sht, vector<vector<int>> &visit) {
    queue<pair<pair<int, int>, int>> q;

    q.push({{ y, x }, 0 });
    while (!q.empty()) {
        auto [t, cst] = q.front();
        auto [y, x] = t;
        q.pop();

        if (visit[y][x]) { continue; }

        visit[y][x] = 1;
        sht[y][x] = cst;
        
        for (int i = 0; i < 4; i++) {
            int ty = y + dy[i];
            int tx = x + dx[i];

            if (ty < 0 || ty >= m || tx < 0 || tx >= n || visit[ty][tx] || mp[ty][tx] == 'X') {
                continue;
            }
            q.push({{ ty, tx }, cst + 1});
        }
    }
}

int main() {
    ios::sync_with_stdio(false);

    vector<string> mp;
    vector<vector<int>> sht, visit;
    map<char, int> info;
    vector<pair<int, int>> k;

    cin >> m >> n >> p;
    mp.resize(m);
    sht.resize(m); visit.resize(m);
    for (int i = 0; i < m; i++) {
        sht[i].resize(n); visit[i].resize(n);
        cin >> mp[i];
    }
    for (int i = 0; i < p; i++) {
        char x;
        int d;

        cin >> x >> d;
        info[x] = d;
    }
    cin >> hp;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (mp[i][j] == 'B') {
                bfs(i, j, mp, sht, visit);
            }
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (mp[i][j] != '.' && mp[i][j] != 'X' && mp[i][j] != 'B' && visit[i][j]) {
                k.emplace_back(sht[i][j], info[mp[i][j]]);
            }
        }
    }

    int cul = 0, cdps = 0, ls = 0, ans = 0;
    
    sort(k.begin(), k.end());
    for (auto [ s, d ] : k) {
        cul += (s - ls) * cdps;
        if (cul > hp) {
            break;
        }
        ls = s;
        cdps += d;
        ans++;
    }

    cout << ans << "\n";
}
