#include <iostream>
#include <vector>

using namespace std;

const long long MOD = 1e9 + 9;

int main() {
    int n;
    vector<long long> v[3];

    cin >> n;
    for (int i = 0; i < 3; i++) {
        v[i].resize(n + 1);
    }

    v[2][0] = v[0][1] = v[1][1] = v[2][1] = 1;

    for (int i = 2; i <= n; i++) {
        v[1][i] = v[0][i - 1] + v[1][i - 1] + v[2][i - 1];
        
        v[0][i] = v[2][i] = v[1][i];
        for (int j = 0; j < i - 1; j++) {
            v[0][i] += v[2][j];
            v[2][i] += v[0][j];
        }

        v[0][i] %= MOD;
        v[1][i] %= MOD;
        v[2][i] %= MOD;
    }

    cout << v[0][n] << "\n";
}
