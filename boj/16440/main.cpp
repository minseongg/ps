#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int n, d = 0;
    string s;

    cin >> n >> s;

    for (int i = 0; i < n / 2; i++) {
        if (s[i] == 's') d++;
        else d--;
    }

    if (d == 0) {
        cout << "1\n" << n / 2 << "\n";
        return 0;
    }

    for (int i = n / 2; i < n; i++) {
        if (s[i] == 's') d++;
        else d--;
        if (s[i - n / 2] == 's') d--;
        else d++;

        if (d == 0) {
            cout << "2\n" << i - n / 2 + 1 << " " << i + 1 << "\n";
            return 0;
        }
    }
}