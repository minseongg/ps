#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    vector<string> nm, nw;
    map<string, int> m, w;
    vector<vector<int>> pm, pw;
    vector<vector<int>> sm, sw;
    int n;

    cin >> n;
    pm.resize(n); pw.resize(n);
    sm.resize(n); sw.resize(n);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        m[s] = i;
        nm.emplace_back(s);
    }
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        w[s] = i;
        nw.emplace_back(s);
    }
    
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        int idx = m[s];
        sm[idx].resize(n);
        for (int j = 0; j < n; j++) {
            string t;
            cin >> t;
            int widx = w[t];
            sm[idx][widx] = n - 1 - j;
            pm[idx].emplace_back(widx);
        }
    }
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        int idx = w[s];
        sw[idx].resize(n);
        for (int j = 0; j < n; j++) {
            string t;
            cin >> t;
            int midx = m[t];
            sw[idx][midx] = n - 1 - j;
            pw[idx].emplace_back(midx);
        }
    }

    int rem = n;
    vector<int> cm(n), cw(n);
    for (int i = 0; i < n; i++) {
        cm[i] = -1; cw[i] = -1;
    }
    while (true) {
        if (rem == 0) { break; }
        for (int i = 0; i < n; i++) {
            if (cm[i] != -1) { continue; }
            for (auto j: pm[i]) {
                if (cw[j] == -1) {
                    cm[i] = j;
                    cw[j] = i;
                    rem--;
                    break;
                }
                if (sw[j][cw[j]] > sw[j][i]) {
                    continue;
                } else {
                    cm[cw[j]] = -1;
                    cm[i] = j;
                    cw[j] = i;
                    break;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << nm[i] << " " << nw[cm[i]] << "\n";
    }
}
