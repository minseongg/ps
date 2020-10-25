#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 1e4 + 5;

void get_prime(vector<int> &v) {
    for (int i = 2; i * i <= MAXN; i++) {
        if (!v[i]) {
            for (int j = i * i; j <= MAXN; j += i) { v[j] = 1; }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    vector<int> p;
    p.resize(MAXN);
    get_prime(p);

    int n;
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        
        for (int j = x / 2; j >= 0; j--) {
            if (!p[j] && !p[x - j]) {
                cout << j << " " << x - j << "\n";
                break;
            }
        }
    }
}