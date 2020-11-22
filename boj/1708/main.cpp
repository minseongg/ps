#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long;

class Point {
public:
    int x, y;

    Point(int _x = 0, int _y = 0) : x(_x), y(_y) { }

    bool operator<(const Point &rhs) const {
        return x != rhs.x ? x < rhs.x : y < rhs.y;
    }

    static ll ccw(const Point &a, const Point &b, const Point &c) {
        return 1ll * (b.x - a.x) * (c.y - a.y) - 1ll * (c.x - a.x) * (b.y - a.y);
    }
};

vector<Point> convex_hull(vector<Point> &pts) {
    sort(pts.begin(), pts.end());
    vector<Point> ret;

    for (int step = 0; step < 2; step++) {
        auto start = ret.size();
        for (Point p : pts) {
            while (ret.size() >= start + 2 && Point::ccw(ret[ret.size() - 2], ret[ret.size() - 1], p) <= 0) { ret.pop_back(); }
            ret.push_back(p);
        }
        ret.pop_back();
        reverse(pts.begin(), pts.end());
    }

    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    vector<Point> pts;

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        pts.emplace_back(x, y);
    }

    vector<Point> ans = convex_hull(pts);
    cout << ans.size() << "\n";

    return 0;
}