#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string s;
    int rem = 0;

    while (true) {
        getline(cin, s);
        if (s == "고무오리 디버깅 끝") { break; }
        if (s == "고무오리") {
            if (rem) {
                rem--;
            } else {
                rem += 2;
            }
        } else if (s == "문제") {
            rem++;
        }
    }

    cout << (rem ? "힝구" : "고무오리야 사랑해") << "\n";
}
