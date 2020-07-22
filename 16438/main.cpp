#include <iostream>
#include <string>

using namespace std;

int main() {
    int n;
    string s;

    cin >> n;

    for (int i = 0; i < 7; i++) {
        bool flag = false;

        s = "";

        for (int j = 0; j < n; j++) {
            s += (j >> i) % 2 ? 'B' : 'A';
            
            if (s[j] == 'B') flag = true;
        }

        if (!flag) s[n - 1] = 'B';

        cout << s << "\n";
    }
}