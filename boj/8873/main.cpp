#include <cstdio>
#include <string>
#include <vector>

using namespace std;

int main() {
    int h, w, s = 0;
    vector<vector<int>> im[3];

    scanf("%d%d", &h, &w);

    for (int c = 0; c < 3; c++) {
        im[c].resize(h);
        for (int i = 0; i < h; i++) {
            im[c][i].resize(w);
            for (int j = 0; j < w; j++) {
                scanf("%d", &im[c][i][j]);
            }
        }
    }

    for (int c = 0; c < 3; c++) {
        for (int i = 0; i < h - 1; i++) {
            for (int j = 0; j < w - 1; j++) {
                s += abs(im[c][i][j + 1] - im[c][i][j]);
                s += abs(im[c][i + 1][j] - im[c][i][j]);
            }
        }
    }

    s /= (h * w);

    if (s < 18) printf("4\n");
    else if (s < 45) printf("1\n");
    else if (s < 108) printf("2\n");
    else printf("3\n");
}