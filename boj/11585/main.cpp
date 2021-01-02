#include <iostream>
#include <string>
#include <vector>

using namespace std;

using vi = vector<int>;

int gcd(int a, int b) {
    return a % b ? gcd(b, a % b) : b;
}

vi get_pi(const string &s) {
    const auto sz = s.size();
    vi pi(sz);
    int j = 0;

    for (int i = 1; i < sz; i++) {
        while (j && s[i] != s[j]) { j = pi[j - 1]; }
        if (s[i] == s[j]) { pi[i] = ++j; }
    }

    return pi;
}

vi kmp(const string &origin, const string &target) {
    const auto osz = origin.size(), tsz = target.size();
    vi ret, pi = get_pi(target);
    int j = 0;
    
    for (int i = 0; i < osz; i++) {
        while (j && origin[i] != target[j]) { j = pi[j - 1]; }
        if (origin[i] == target[j]) {
            if (j == tsz - 1) {
                ret.emplace_back(i - tsz + 1);
                j = pi[j];
            } else {
                j++;
            }
        }
    }

    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n;
    string origin, target;
    cin >> n;
    for (int i = 0; i < n; i++) {
        char x;
        cin >> x;
        target += x;
    }
    for (int i = 0; i < n; i++) {
        char x;
        cin >> x;
        origin += x;
    }
    origin += origin.substr(0, n - 1);
    
    auto idxs = kmp(origin, target);
    int q = (int)idxs.size(), p = n;
    int g = gcd(q, p);
    cout << q / g << "/" << p / g << "\n";
}