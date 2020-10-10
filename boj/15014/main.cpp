#include <iostream>
#include <string>
#include <map>
#include <cmath>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    map<string, double> d;

    d["pink"] = 0;

    cin >> n;

    for (int i = 0; i < n; i++) {
        string o, w;
        double r;

        cin >> o >> w >> r;

        if (d.find(w) == d.end()) { continue; }

        if (d.find(o) == d.end()) {
            d[o] = d[w] + log10(r);
        } else {
            d[o] = max(d[o], d[w] + log10(r));
        }
    }

    if (d.find("blue") != d.end()) { d["blue"] = min(1.0, d["blue"]); }

    cout.precision(15);
    if (d.find("blue") == d.end()) {
        cout << 0 << "\n";
    } else {
        cout << __exp10(d["blue"]) << "\n";
    }
}
