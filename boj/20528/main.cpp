#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, flag = 1;
    string s;
    char k;

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s;
        if (i == 1) {
            k = s[0];
        } else {
            if (s[0] == k) {
                continue;
            } else {
                flag = 0;
                break;
            }
        }
    }

    if (flag) {
        cout << "1\n";
    } else {
        cout << "0\n";
    }
}