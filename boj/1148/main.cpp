#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int INF = 2e6;

bool valid(vector<int> &a, vector<int> &b) {
    for (int i = 0; i < 26; i++) {
        if (a[i] > b[i]) return false;
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);

    vector<vector<int>> w;

    while (1) {
        string s;
        vector<int> v;

        v.resize(26);
        cin >> s;
        if (s == "-") break;
        for (char x : s) {
            v[(int)x - (int)'A']++;
        }

        w.push_back(v);
    }

    while (1) {
        string s;
        vector<int> v, c;

        v.resize(26);
        c.resize(26);
        cin >> s;
        if (s == "#") break;
        for (char x : s) {
            c[(int)x - (int)'A']++;
        }

        for (auto &x : w) {
            if (valid(x, c)) {
                for (int i = 0; i < 26; i++) {
                    if (x[i] && c[i]) v[i]++;
                }
            }
        }

        int minc = INF, maxc = 0;
        string minv, maxv;

        for (int i = 0; i < 26; i++) {
            if (!c[i]) continue;

            minc = min(minc, v[i]);
            maxc = max(maxc, v[i]);
        }

        for (int i = 0; i < 26; i++) {
            if (!c[i]) continue;

            if (v[i] == minc) minv += (char)(i + (int)'A');
            if (v[i] == maxc) maxv += (char)(i + (int)'A');
        }

        cout << minv << " " << minc << " " << maxv << " " << maxc << "\n";
    }
}