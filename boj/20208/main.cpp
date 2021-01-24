#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, h, sx, sy;
    vector<int> tx, ty;
    
    cin >> n >> m >> h;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
            if (x == 1) { sy = i; sx = j; }
            else if (x == 2) { ty.emplace_back(i); tx.emplace_back(j); }
        }
    }

    int ans = 0;
    vector<int> perm;
    for (int i = 0; i < (int)tx.size(); i++) { perm.emplace_back(i); }

    do {
        int r = m, nx = sx, ny = sy;
        for (int i = 0; i < (int)perm.size(); i++) {
            if (abs(tx[perm[i]] - nx) + abs(ty[perm[i]] - ny) <= r) {
                r = r - abs(tx[perm[i]] - nx) - abs(ty[perm[i]] - ny) + h;
                nx = tx[perm[i]];
                ny = ty[perm[i]];
                if (abs(nx - sx) + abs(ny - sy) <= r) { ans = max(ans, i + 1); }
            } else {
                break;
            }
        }
    } while (next_permutation(perm.begin(), perm.end()));

    cout << ans << "\n";
}
    
