#include <iostream>
#include <vector>
#include <queue>

using namespace std;

inline bool valid(int x, int n, vector<int> &p, vector<int> &v) {
    if (x < 0 || x >= n) return false;
    if (p[x] || v[x]) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);

    int n, s, d, f, b, k;
    vector<int> p, c, v;
    queue<int> q;

    cin >> n >> s >> d >> f >> b >> k;

    s--;
    d--;
    p.resize(n);
    c.resize(n);
    v.resize(n);

    for (int i = 0; i < k; i++) {
        int x;

        cin >> x;
        p[x - 1] = 1;
    }

    q.push(s);
    v[s] = 1;

    while (!q.empty()) {
        int front = q.front();
        q.pop();

        if (front == d) {
            cout << c[front] << "\n";
            return 0;
        }

        if (valid(front + f, n, p, v)) {
            q.push(front + f);
            c[front + f] = c[front] + 1;
            v[front + f] = 1;
        }

        if (valid(front - b, n, p, v)) {
            q.push(front - b);
            c[front - b] = c[front] + 1;
            v[front - b] = 1;
        }
    }

    cout << "BUG FOUND\n";
    return 0;
}