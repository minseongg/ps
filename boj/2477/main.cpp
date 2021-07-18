#include <iostream>
#include <vector>

using namespace std;

int main() {
    int k, ans = 0;
    int ny = 0, nx = 0;
    int dy[4] = {0, 0, 1, -1}, dx[4] = {1, -1, 0, 0};
    vector<int> y, x;
    
    cin >> k;

    for (int i = 0; i < 6; i++) {
        int dir, l;
        
        cin >> dir >> l;
        ny += dy[dir - 1] * l;
        nx += dx[dir - 1] * l;
        y.emplace_back(ny);
        x.emplace_back(nx);
    }

    for (int i = 0; i < 6; i++) {
        ans += x[i] * y[(i + 1) % 6];
        ans -= y[i] * x[(i + 1) % 6];
    }

    cout << k * abs(ans) / 2 << "\n";
}
