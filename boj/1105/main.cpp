#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string l, r;
    int ans = 0;

    cin >> l >> r;
    if (l.size() != r.size()) {
        cout << 0 << "\n";
        return 0;
    }

    for (int i = 0; i < (int)l.size(); i++) {
        if (l[i] != r[i]) {
            break;
        }
        
        if (l[i] == '8') {
            ans++;
        }
    }

    cout << ans << "\n";
}