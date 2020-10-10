#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int n, s = 3, t = 1, a = 0;

    cin >> n;

    while (1) {
        if (n <= s) break;
        s += t;
        a++;
        t <<= 1;

        if (n <= s) break;
        s += t;
        a++;
    }

    cout << a << "\n";
}