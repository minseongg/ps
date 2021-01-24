#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    vector<ll> x;
    cin >> n;
    x.resize(n);
    for (int i = 0; i < n; i++) { cin >> x[i]; }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            int p1 = 0, p2 = 0;
            while (x[j] >> p1) { p1++; }
            while (x[i] >> p2) { p2++; }
            p1--; p2--;
            if (p1 / 4 == p2 / 4) { cout << "1 "; }
            else if (p1 / 16 == p2 / 16) { cout << "2 "; }
            else { cout << "3 "; }
        }
        cout << "\n";
    }
}