#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int br, bc, dr, dc, jr, jc;
    int b, d;

    cin >> br >> bc >> dr >> dc >> jr >> jc;

    b = max(abs(br - jr), abs(bc - jc));
    d = abs(dr - jr) + abs(dc - jc);

    if (b < d) {
        cout << "bessie" << "\n";
    } else if (b == d) {
        cout << "tie" << "\n";
    } else {
        cout << "daisy" << "\n";
    }
}