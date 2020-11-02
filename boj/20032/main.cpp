#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using pii = pair<int, int>;

class Point {
public:
    int x, y, idx;

    Point() : x(0), y(0), idx(0) {}
};

inline bool cmp(const Point &a, const Point &b) {
    return a.x == b.x ? a.y < b.y : a.x < b.x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    vector<Point> v;

    cin >> n;
    v.resize(n);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        v[i].x = x; v[i].y = y; v[i].idx = i + 1;
    }

    sort(v.begin(), v.end(), cmp);

    cout << 2 * n - 1 << "\n";
    for (int i = 0; i < n; i++) {
        cout << v[i].idx << " ";
    }
    for (int i = n - 2; i >= 0; i--) {
        cout << v[i].idx << " ";
    }
    cout << "\n";
}