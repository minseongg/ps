#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool isvalid_3x3(int state) {
    int cnt = 0;

    while (state) {
        cnt += state & 1;
        state >>= 1;
    }

    return cnt % 2 ? false : true;
}

void update(int now, int prev_row, int prev_col, int state, vector<int> &new_state) {
    for (int i = 0; i < 9; i++) { new_state[i] = (prev_col >> i) & 1; }
    for (int i = 9; i < 12; i++) { new_state[i] = (prev_row >> (i - 9)) & 1; }

    if (state & (1 << 0)) { new_state[now % 3 * 3] ^= 1; new_state[9] ^= 1; }
    if (state & (1 << 1)) { new_state[now % 3 * 3 + 1] ^= 1; new_state[9] ^= 1; }
    if (state & (1 << 2)) { new_state[now % 3 * 3 + 2] ^= 1; new_state[9] ^= 1; }
    if (state & (1 << 3)) { new_state[now % 3 * 3] ^= 1; new_state[10] ^= 1; }
    if (state & (1 << 4)) { new_state[now % 3 * 3 + 1] ^= 1; new_state[10] ^= 1; }
    if (state & (1 << 5)) { new_state[now % 3 * 3 + 2] ^= 1; new_state[10] ^= 1; }
    if (state & (1 << 6)) { new_state[now % 3 * 3] ^= 1; new_state[11] ^= 1; }
    if (state & (1 << 7)) { new_state[now % 3 * 3 + 1] ^= 1; new_state[11] ^= 1; }
    if (state & (1 << 8)) { new_state[now % 3 * 3 + 2] ^= 1; new_state[11] ^= 1; }
}

int diff(int now, vector<vector<int>> &v, int state) {
    int cnt = 0;

    int offset_i = now - now % 3, offset_j = now % 3 * 3;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (v[offset_i + i][offset_j + j] != (state >> (i * 3 + j) & 1)) { cnt++; }
        }
    }

    return cnt;
}

pair<int, int> cvt(vector<int> &new_state) {
    int col = 0, row = 0;

    for (int i = 0; i < 9; i++) {
        col += (new_state[i] << i);
    }

    for (int i = 9; i < 12; i++) {
        row += (new_state[i] << (i - 9));
    }

    return make_pair(col, row);
}

const int INF = 1e7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string s;
    vector<vector<int>> v;
    vector<vector<vector<int>>> d;

    v.resize(9);

    for (int i = 0; i < 9; i++) {
        cin >> s;

        v[i].resize(9);
        for (int j = 0; j < 9; j++) {
            v[i][j] = (s[j] == '0' ? 0 : 1);
        }
    }

    d.resize(9);

    for (int i = 0; i < 9; i++) {
        d[i].resize(1 << 9);

        for (int j = 0; j < (1 << 9); j++) {
            d[i][j].resize(1 << 3);

            for (int k = 0; k < (1 << 3); k++) {
                d[i][j][k] = INF;
            }
        }
    }

    vector<int> new_state;
    
    new_state.resize(12);

    for (int i = 0; i < 9; i++) {
        for (int state = 0; state < (1 << 9); state++) {
            if (!isvalid_3x3(state)) { continue; }

            int cnt = diff(i, v, state);

            if (i % 3) {
                for (int prev_col = 0; prev_col < (1 << 9); prev_col++) {
                    for (int prev_row = 0; prev_row < (1 << 3); prev_row++) {
                        update(i, prev_row, prev_col, state, new_state);
                        
                        auto p = cvt(new_state);

                        d[i][p.first][p.second] = min(d[i][p.first][p.second], d[i - 1][prev_col][prev_row] + cnt);
                    }
                }
            } else if (i) {
                for (int prev_col = 0; prev_col < (1 << 9); prev_col++) {
                    update(i, 0, prev_col, state, new_state);

                    auto p = cvt(new_state);

                    d[i][p.first][p.second] = min(d[i][p.first][p.second], d[i - 1][prev_col][0] + cnt);
                }
            } else {
                update(i, 0, 0, state, new_state);

                auto p = cvt(new_state);

                d[i][p.first][p.second] = min(d[i][p.first][p.second], cnt);
            }
        }
    }

    cout << d[8][0][0] << "\n";
}