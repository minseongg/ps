#include <iostream>
#include <vector>
#include <queue>

using namespace std;

using vi = vector<int>;
using vvi = vector<vector<int>>;

const int MAXN = 5e5 + 5;

int main() {
    ios::sync_with_stdio(false);

    int n, a, b, da, db;
    vi d, visited;
    vvi e;
    queue<int> q;

    cin >> n >> a >> b >> da >> db;

    d.resize(MAXN << 1);
    visited.resize(MAXN << 1);
    e.resize(MAXN << 1);
    
    q.push(min(abs(a - b), n - abs(a - b)));
    visited[min(abs(a - b), n - abs(a - b))] = 1;

    while (!q.empty()) {
        int f = q.front(), t, dist;
        q.pop();

        if (f == 0 || f == MAXN) {
            cout << d[f] << "\n";
            return 0;
        }

        if (f < MAXN) {
            t = n - da;
            dist = min(abs(t - f), n - abs(t - f));

            if (!visited[dist + MAXN]) {
                visited[dist + MAXN] = 1;
                d[dist + MAXN] = d[f] + 1;
                q.push(dist + MAXN);
            }

            t = da;
            dist = min(abs(t - f), n - abs(t - f));

            if (!visited[dist + MAXN]) {
                visited[dist + MAXN] = 1;
                d[dist + MAXN] = d[f] + 1;
                q.push(dist + MAXN);
            }
        } else {
            t = n - db;
            dist = min(abs(t - f + MAXN), n - abs(t - f + MAXN));

            if (!visited[dist]) {
                visited[dist] = 1;
                d[dist] = d[f] + 1;
                q.push(dist);
            }

            t = db;
            dist = min(abs(t - f + MAXN), n - abs(t - f + MAXN));

            if (!visited[dist]) {
                visited[dist] = 1;
                d[dist] = d[f] + 1;
                q.push(dist);
            }
        }
    }

    cout << "Evil Galazy\n";
}