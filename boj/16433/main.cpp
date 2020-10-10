#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int n, r, c;

    cin >> n >> r >> c;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << (((i + j) % 2 == (r + c) % 2) ? 'v' : '.');
        }
        cout << "\n";
    }
}