#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

using vi = vector<int>;

int gcd(int a, int b) {
    if (a < b) { return gcd(b, a); }
    return a % b == 0 ? b : gcd(b, a % b);
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    map<char, char> c, m;
    c['A'] = 'A'; m['A'] = 'A';
    c['B'] = 'b';
    c['D'] = 'd';
    c['E'] = 'E'; m['E'] = '3';
    c['H'] = 'H'; m['H'] = 'H';
    c['I'] = 'I'; m['I'] = 'I';
    c['L'] = 'l';
    c['M'] = 'M'; m['M'] = 'M';
    c['N'] = 'n';
    c['O'] = 'O'; m['O'] = 'O';
    c['P'] = 'p';
    c['Q'] = 'q';
    c['R'] = 'r';
    c['S'] = 'S'; m['S'] = '2';
    c['T'] = 'T'; m['T'] = 'T';
    c['U'] = 'U'; m['U'] = 'U';
    c['V'] = 'V'; m['V'] = 'V';
    c['W'] = 'W'; m['W'] = 'W';
    c['X'] = 'X'; m['X'] = 'X';
    c['Y'] = 'Y'; m['Y'] = 'Y';
    c['Z'] = 'Z'; m['Z'] = '5';
    c['a'] = 'A';
    c['b'] = 'b'; m['b'] = 'd';
    c['d'] = 'd'; m['d'] = 'b';
    c['e'] = 'E';
    c['h'] = 'H';
    c['i'] = 'I';
    c['l'] = 'l'; m['l'] = 'l';
    c['m'] = 'M';
    c['n'] = 'n'; m['n'] = 'n';
    c['o'] = 'O';
    c['p'] = 'p'; m['p'] = 'q';
    c['q'] = 'q'; m['q'] = 'p';
    c['r'] = 'r'; m['r'] = '7';
    c['s'] = 'S';
    c['t'] = 'T';
    c['u'] = 'U';
    c['v'] = 'V';
    c['w'] = 'W';
    c['x'] = 'X';
    c['y'] = 'Y';
    c['z'] = 'Z';
    c['0'] = '0'; m['0'] = '0';
    c['1'] = '1'; m['1'] = '1';
    c['2'] = '2'; m['2'] = 'S';
    c['3'] = '3'; m['3'] = 'E';
    c['5'] = '5'; m['5'] = 'Z';
    c['7'] = '7'; m['7'] = 'r';
    c['8'] = '8'; m['8'] = '8';

    string s;
    int sz;
    cin >> s;
    sz = (int)s.size();
    for (int i = 0; i < sz; i++) {
        if (c.find(s[i]) == c.end()) {
            cout << "-1\n";
            return 0;
        }
        s[i] = c[s[i]];
    }
    
    string rev_s;
    for (int i = 0; i < sz; i++) {
        rev_s += m[s[i]];
    }
    reverse(rev_s.begin(), rev_s.end());

    string union_s = rev_s + s;
    vi pi = get_pi(union_s);
    string ans_s_1;
    int t = pi[(sz << 1) - 1];
    while (t > sz) { t = pi[t - 1]; }
    ans_s_1 += s;
    for (int i = t; i < sz; i++) { ans_s_1 += rev_s[i]; }

    string union_s_2 = s + rev_s;
    pi = get_pi(union_s_2);
    string ans_s_2;
    t = pi[(sz << 1) - 1];
    while (t > sz) { t = pi[t - 1]; }
    for (int i = 0; i < sz - t; i++) { ans_s_2 += rev_s[i]; }
    ans_s_2 += s;

    if (ans_s_1.size() < ans_s_2.size()) {
        cout << ans_s_1 << "\n";
    } else {
        cout << ans_s_2 << "\n";
    }
}