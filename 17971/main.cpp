#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Ladder {
public:
    int x, d, idx;
    int a, b, flag = 1;

    Ladder(int x, int d, int idx) {
        this->x = x;
        this->d = d;
        this->idx = idx;
    }
};

bool cmp(const Ladder &a, const Ladder &b) {
    return a.d < b.d;
}

int main() {
    ios::sync_with_stdio(false);

    int n;
    vector<Ladder> v;
    vector<int> pi;
    
    cin >> n;
    pi.resize(n);
    for (int i = 0; i < n; i++) pi[i] = i;
    for (int i = 0; i < n-1; i++) {
        int d;

        for (int j = 0;; j++) {
            cin >> d;
            if (!d) break;

            v.push_back(Ladder(i, d, j));
        }
    }
    
    sort(v.begin(), v.end(), cmp);

    int sz = (int)v.size();
    int ans = sz;

    for (int i = 0; i < sz; i++) {
        Ladder &l = v[i];
        int a = pi[l.x], b = pi[l.x + 1];
        
        l.a = a; l.b = b;
        pi[l.x] = b; pi[l.x + 1] = a;

        for (int j = 0; j < i; j++) {
            if (!v[j].flag) continue;

            int ta = v[j].a, tb = v[j].b;

            if (a == tb && b == ta) {
                v[j].flag = 0; v[i].flag = 0;
                
                for (int k = j+1; k < i; k++) {
                    if (v[k].a == a) v[k].a = b;
                    else if (v[k].a == b) v[k].a = a;
                    if (v[k].b == a) v[k].b = b;
                    else if (v[k].b == b) v[k].b = a;
                }

                ans -= 2;
                break;
            }
        }
    }

    cout << ans << "\n";
    for (int i = 0; i < sz; i++) {
        if (!v[i].flag) continue;
        cout << v[i].x + 1 << " " << v[i].idx + 1 << "\n";
    }
}