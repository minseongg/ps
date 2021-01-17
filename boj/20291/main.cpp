#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    map<string, int> dic;
    int n;
    cin >> n;
    while (n--) {
        string s, t;
        cin >> s;
        int idx = 0;
        while (s[idx++] != '.') { }
        t = s.substr(idx, s.size() - idx);
        if (dic.find(t) == dic.end()) {
            dic[t] = 1;
        } else {
            dic[t]++;
        }
    }

    for (auto &[ key, value ] : dic) {
        cout << key << " " << value << "\n";
    }
}