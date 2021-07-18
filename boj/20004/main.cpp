#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int a;
    
    cin >> a;
    for (int n = 1; n <= a; n++) {
        int t = 30 % (n + 1);
        
        if (!(t >= 1 && t <= n)) {
            cout << n << "\n";
        }
    }
}
