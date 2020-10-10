#include <iostream>

using namespace std;

int g(int ph, int pa, int eh, int ea) {
    int c = eh / pa + (eh % pa ? 1 : 0);

    if ((c - 1) * ea >= ph) return 1e5;
    return c;
}

int f(int ph, int pa, int eh, int ea) {
    int c = 0, tmp = 1e5;
    
    if (eh <= 0) return 0;

    while (1) {
        int k = g(ph, pa, eh, ea);

        tmp = min(tmp, c+k);

        if (pa / 5 == 0 || k == 1) break;

        ph -= ea * 3;
        pa += pa / 5;

        if (ph <= 0) break;

        c++;
    }

    return tmp;
}

int solve(int ph, int pa, int eh, int ea) {
    int c = 0, ans = 1e5;

    while (1) {
        int k = f(ph, pa, eh, ea);

        ans = min(ans, c+k);

        if (eh < 0) break;

        eh -= ea;
        ph += ph / 10;
        c++;
    }

    return ans;
}

int main() {
    int a, b, x, y;

    cin >> a >> b >> x >> y;
    cout << solve(a, b, x, y) << endl;
}