#include <iostream>

using namespace std;

const int MOD = 1e9;

int fib(int n) {
    if (n <= 1) return n;
    
    int a = 0, b = 1;

    for (int i = 2; i < n; i++) {
        int t = a;

        a = b;
        b = (a + t) % MOD;
    }

    return (a + b) % MOD;
}

int sign(int n) {
    return n ? (n >= 0 || n % 2 ? 1 : -1) : 0;
}

int main() {
    ios::sync_with_stdio(false);

    int n;

    cin >> n;
    cout << sign(n) << "\n" << fib(abs(n)) << "\n";

    return 0;
}