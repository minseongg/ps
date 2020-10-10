#include <iostream>

using namespace std;

const int UPPER = 250;

int main() {
    int n;

    cin >> n;

    for (int i = 1; i < UPPER; i++) {
        if (i * i == n) {
            cout << "1\n";
            return 0;
        }
    }

    for (int i = 1; i < UPPER; i++) {
        for (int j = i; j < UPPER; j++) {
            if (i * i + j * j == n) {
                cout << "2\n";
                return 0;
            }
        }
    }

    for (int i = 1; i < UPPER; i++) {
        for (int j = i; j < UPPER; j++) {
            for (int k = j; k < UPPER; k++) {
                if (i * i + j * j + k * k == n) {
                    cout << "3\n";
                    return 0;
                }
            }
        }
    }

    cout << "4\n";
}