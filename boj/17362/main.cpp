#include <iostream>

using namespace std;

int main() {
    int n;
    int ans[8] = {1, 2, 3, 4, 5, 4, 3, 2};

    cin >> n;
    cout << ans[(n - 1) % 8] << "\n";

    return 0;
}

