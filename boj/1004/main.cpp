#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        int n;
        cin >> n;

        int ans = 0;
        while (n--) {
            int cx, cy, r;
            cin >> cx >> cy >> r;

            int f1 = (x1 - cx) * (x1 - cx) + (y1 - cy) * (y1 - cy) - r * r < 0;
            int f2 = (x2 - cx) * (x2 - cx) + (y2 - cy) * (y2 - cy) - r * r < 0;

            ans += (f1 != f2);
        }

        cout << ans << "\n";
    }
}