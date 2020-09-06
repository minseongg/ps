#include <iostream>
#include <vector>

using namespace std;

inline bool is_all2(vector<int> &v) {
    int c = 0;

    for (int x : v) {
        if (x == 2) { c++; }
    }

    return (c == 7);
}

inline bool is_avail(vector<int> &v) {
    if (is_all2(v)) { return true; }

    vector<int> w;

    for (int h = 0; h < 9; h++) {
        bool flag = true;

        w = v;

        if (w[h] < 2) { continue; }

        w[h] -= 2;

        for (int i = 0; i < 9; i++) {
            if (w[i] == 1 && i < 7) {
                w[i]--;
                w[i + 1]--;
                w[i + 2]--;
            } else if (w[i] == 2 && i < 7) {
                w[i] -= 2;
                w[i + 1] -= 2;
                w[i + 2] -= 2;
            } else if (w[i] == 3) {
                w[i] -= 3;
            } else if (w[i] == 4 && i < 7) {
                w[i] -= 4;
                w[i + 1]--;
                w[i + 2]--;
            }
        }

        for (int i = 0; i < 9; i++) {
            if (w[i]) { flag = false; }
        }

        if (flag) { return true; }
    }

    return false;
}

int main() {
    vector<int> v, w, ans;
    
    v.resize(9);

    for (int i = 0; i < 13; i++) {
        int x;

        cin >> x;
        v[x - 1]++;
    }

    for (int i = 0; i < 9; i++) {
        w = v;
        
        if (w[i] == 4) { continue; }

        w[i]++;
        
        if (is_avail(w)) {
            ans.emplace_back(i + 1);
        }
    }

    if (ans.empty()) {
        cout << "-1\n";
    } else {
        for (int x : ans) {
            cout << x << " ";
        }
        cout << "\n";
    }
}