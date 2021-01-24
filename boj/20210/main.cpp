#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

inline bool isupper(const char x) {
    return (int)x >= (int)'A' && (int)x <= (int)'Z';
}

inline char toupper(const char x) {
    if (isupper(x)) { return x; }
    return (char)((int)x - (int)'a' + (int)'A');
}

inline bool islower(const char x) {
    return (int)x >= (int)'a' && (int)x <= (int)'z';
}

inline char tolower(const char x) {
    if (islower(x)) { return x; }
    return (char)((int)x - (int)'A' + (int)'a');
}

inline bool isdigit(const char x) {
    return (int)x >= (int)'0' && (int)x <= (int)'9';
}

inline bool cmp(const string &a, const string &b) {
    int sz_a = (int)a.size(), sz_b = (int)b.size();
    int it_a = 0, it_b = 0;

    while (1) {
        if (it_a == sz_a && it_b == sz_b) { return 0; }
        if (it_a == sz_a) { return 1; }
        if (it_b == sz_b) { return 0; }

        if (!isdigit(a[it_a]) || !isdigit(b[it_b])) {
            if (isdigit(a[it_a])) { return 1; }
            if (isdigit(b[it_b])) { return 0; }
            if (tolower(a[it_a]) == tolower(b[it_b])) {
                if (a[it_a] == b[it_b]) { it_a++; it_b++; continue; }
                if (isupper(a[it_a])) { return 1; }
                else { return 0; }
            } else {
                return tolower(a[it_a]) < tolower(b[it_b]);
            }
        } else {
            int zero_a = 0, ot_a = 0, zero_b = 0, ot_b = 0;
            
            while (it_a + zero_a < sz_a && a[it_a + zero_a] == '0') { zero_a++; }
            while (it_a + zero_a + ot_a < sz_a && isdigit(a[it_a + zero_a + ot_a])) { ot_a++; }

            while (it_b + zero_b < sz_b && b[it_b + zero_b] == '0') { zero_b++; }
            while (it_b + zero_b + ot_b < sz_b && isdigit(b[it_b + zero_b + ot_b])) { ot_b++; }

            if (ot_a != ot_b) {
                return ot_a < ot_b;
            }

            for (int i = 0; i < ot_a; i++) {
                if (a[it_a + zero_a + i] != b[it_b + zero_b + i]) {
                    return a[it_a + zero_a + i] < b[it_b + zero_b + i];
                }
            }

            if (zero_a != zero_b) {
                return zero_a < zero_b;
            }

            it_a += zero_a + ot_a;
            it_b += zero_b + ot_b;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    vector<string> v;
    
    cin >> n;
    v.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    sort(v.begin(), v.end(), cmp);
    
    for (string &s : v) {
        cout << s << "\n";
    }
}
