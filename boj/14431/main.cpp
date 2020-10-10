#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

const int INF = 1e9;
const int UPPER = 1e4;

void get_prime(vector<int> &era) {
    era[1] = 1;

    for (int i = 2; i * i <= UPPER; i++) {
        if (era[i]) continue;

        for (int j = i * i; j <= UPPER; j += i) {
            era[j] = 1;
        }
    }
}

int get_dist(int x1, int y1, int x2, int y2) {
    int dist = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
    int dist_round = (int)sqrt(dist);

    return dist_round;
}

bool cmp(const pair<int, int> &a, const pair<int, int> &b) {
    return a.second > b.second;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    vector<int> x, y, era, d, visited;
    vector<vector<pair<int, int>>> e;
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(&cmp)> pq(cmp);

    era.resize(UPPER + 1);
    get_prime(era);

    for (int i = 0; i < 2; i++) {
        int tx, ty;

        cin >> tx >> ty;

        x.emplace_back(tx);
        y.emplace_back(ty);
    }

    cin >> n;

    for (int i = 0; i < n; i++) {
        int tx, ty;

        cin >> tx >> ty;

        x.emplace_back(tx);
        y.emplace_back(ty);
    }

    n += 2;

    e.resize(n);
    d.resize(n);
    visited.resize(n);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int d = get_dist(x[i], y[i], x[j], y[j]);

            if (!era[d]) {
                e[i].emplace_back(j, d);
                e[j].emplace_back(i, d);
            }
        }
    }

    for (int i = 0; i < n; i++) { d[i] = INF; }

    d[0] = 0;
    pq.push({0, 0});

    while (!pq.empty()) {
        auto top = pq.top();
        int now = top.first, cost = top.second;

        pq.pop();

        if (visited[now]) { continue; }
        visited[now] = 1;

        if (now == 1) { break; }

        for (auto &x : e[now]) {
            int to = x.first, to_cost = x.second;

            if (visited[to]) { continue; }

            if (d[to] > cost + to_cost) {
                d[to] = cost + to_cost;
                pq.push({to, cost + to_cost});
            }
        }
    }

    if (!visited[1]) {
        cout << "-1\n";
    } else {
        cout << d[1] << "\n";
    }
}