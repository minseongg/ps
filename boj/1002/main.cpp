#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int x1, y1, r1, x2, y2, r2;
        cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
        
        if (x1 == x2 && y1 == y2) {
            if (r1 == r2) {
                 cout << -1 << "\n";
            } else {
                cout << 0 << "\n";
            }
        } else {
            int t1 = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
            int t2 = (r1 + r2) * (r1 + r2);
            int t3 = (r1 - r2) * (r1 - r2);

            if (t1 > t2) {
                cout << 0 << "\n";
            } else if (t1 == t2) {
                cout << 1 << "\n";
            } else if (t1 < t2 && t1 > t3) {
                cout << 2 << "\n";
            } else if (t1 == t3) {
                cout << 1 << "\n";
            } else if (t1 < t3) {
                cout << 0 << "\n";
            }
        }
    }
}