#include <iostream>
#include <vector>
#include <string>
#include <tuple>

using namespace std;

const int READ = 0;
const int WRITE = 1;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    vector<tuple<int, string, string>> ins;
    while (true) {
        string s;
        cin >> s;
        if (s == "READ") {
            string arg_1;
            cin >> arg_1;
            ins.push_back({ READ, arg_1, "" });
        } else if (s == "WRITE") {
            string arg_1, tmp, arg_2;
            cin >> arg_1 >> tmp >> arg_2;
            ins.push_back({ WRITE, arg_1, arg_2 });
        } else {
            break;
        }
    }
    int sz = ins.size();
    vector<int> ans(sz);

    for (int i = 1; i < sz; i++) {
        int flag = 0;
        for (int j = i - 1; j >= 0; j--) {
            if (ans[j]) { break; }
            
            auto &[ ins_j, arg_j_1, arg_j_2 ] = ins[j];
            auto &[ ins_i, arg_i_1, arg_i_2 ] = ins[i];

            if (ins_i == READ) {
                if (ins_j == WRITE && arg_j_2 == arg_i_1) { flag = 1; break; }
            } else if (ins_i == WRITE) {
                if (ins_j == READ && arg_i_2 == arg_j_1) { flag = 1; break; }
                if (ins_j == WRITE && arg_j_2 == arg_i_1) { flag = 1; break; }
                if (ins_j == WRITE && arg_j_2 == arg_i_2) { flag = 1; break; }
                if (ins_j == WRITE && arg_j_1 == arg_i_2) { flag = 1; break; }
            }
        }

        ans[i - 1] = flag;
    }

    for (int i = 0; i < sz; i++) {
        auto &[ s, arg_1, arg_2 ] = ins[i];
        if (s == READ) {
            cout << "READ " << arg_1 << "\n";
        } else if (s == WRITE) {
            cout << "WRITE " << arg_1 << " TO " << arg_2 << "\n";
        }
        if (ans[i]) { cout << "WAIT\n"; }
    }
    cout << "EXIT\n";
}