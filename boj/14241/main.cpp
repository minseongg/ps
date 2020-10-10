#include <iostream>

using namespace std;

int main() {
    int n, a = 0, b = 0;

    cin >> n;
    while (n--) {
        int x;
        
        cin >> x;
        a += x;
        b += x * x;
    }

    cout << ((a * a - b) >> 1) << "\n";
}