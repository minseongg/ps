#include <iostream>

using namespace std;

int main() {
    cout << "30000\n";

    for (int i = 0; i < 10000; i++) {
        cout << "2000000000\n";
    }

    for (int i = 0; i < 10000; i++) {
        cout << "-1999999999\n";
    }

    for (int i = 0; i < 10000; i++) {
        cout << "-1\n";
    }
}