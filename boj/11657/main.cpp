#include <iostream>
#include <vector>

using namespace std;

class Bus {
public:
    int a, b, c;

    Bus(int a, int b, int c) : a(a), b(b), c(c) {}
};

const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);

    int n, m, flag = 0, par = 0;
    vector<Bus> e;
    vector<int> d[2];

    cin >> n >> m;

    d[0].resize(n);
    d[1].resize(n);
    for (int i = 0; i < n; i++) {
        d[par][i] = INF;
        d[par^1][i] = INF;
    }
    d[par][0] = 0;

    for (int i = 0; i < m; i++) {
        int a, b, c;

        cin >> a >> b >> c;

        e.emplace_back(a - 1, b - 1, c);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) { d[par^1][j] = d[par][j]; }

        for (int j = 0; j < m; j++) {
            int a = e[j].a, b = e[j].b, c = e[j].c;

            if (d[par][a] == INF) { continue; }
            if (d[par^1][b] > d[par][a] + c) {
                d[par^1][b] = d[par][a] + c;
                if (i == n - 1) { flag = 1; }
            }
        }
        
        par ^= 1;
    }

    if (flag) {
        cout << "-1\n";
    } else {
        for (int i = 1; i < n; i++) {
            if (d[par][i] == INF) {
                cout << "-1\n";
            } else {
                cout << d[par][i] << "\n";
            }
        }
    }
}