#include <iostream>

using namespace std;

int main() {
    int x1, y1, x2, y2, x3, y3, prod;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    prod = (x2 - x1) * (y3 - y2) - (y2 - y1) * (x3 - x2);

    if (prod > 0) {
        cout << "1\n";
    } else if (prod == 0) {
        cout << "0\n";
    } else {
        cout << "-1\n";
    }
}
