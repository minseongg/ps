#include <stdio.h>

const int N = 1 << 17;

int inmap[N], post[N];

inline void solve(int is, int ie, int ps, int pe) {
    if (ie == is) { return; }

    int f = post[pe - 1];
    printf("%d ", f);

    if (ie == is + 1) {
        return;
    }

    int t = inmap[f], d = t - is;
    solve(is, t, ps, ps + d);
    solve(t + 1, ie, ps + d, pe - 1);
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) { int x; scanf("%d", &x); inmap[x] = i; }
    for (int i = 0; i < n; i++) { scanf("%d", &post[i]); }

    solve(0, n, 0, n);
    printf("\n");
}
