#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main() {
    int n, m;
    vector<string> v;
    map<char, char> cmap;

    cmap['.'] = '.';
    cmap['O'] = 'O';
    cmap['-'] = '|';
    cmap['|'] = '-';
    cmap['/'] = '\\';
    cmap['\\'] = '/';
    cmap['^'] = '<';
    cmap['<'] = 'v';
    cmap['v'] = '>';
    cmap['>'] = '^';

    cin >> n >> m;
    v.resize(n);

    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << cmap[v[j][m - 1 - i]];
        }
        cout << "\n";
    }

    return 0;
}
