#include <iostream>

using namespace std;

int f(int a, int b) {
    if (b == 1) { return a % 10; }
    int c = f(a, b / 2);
    c *= c;
    return b % 2 ? c * a % 10 : c % 10;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int a, b, ans;
        cin >> a >> b;
        ans = f(a, b);
        cout << (ans ? ans : 10) << "\n";
    }
}