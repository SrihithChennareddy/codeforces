#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int testCount;
    cin >> testCount;

    while (testCount--) {
        string sequence;
        cin >> sequence;

        int balance = 0;
        bool canBreak = false;

        for (size_t i = 0; i + 1 < sequence.size(); ++i) {
            if (sequence[i] == '(') {
                ++balance;
            } else {
                --balance;
            }

            if (balance == 0) {
                canBreak = true;
                break;
            }
        }

        if (canBreak) {
            cout << "YES" << '\n';
        } else {
            cout << "NO" << '\n';
        }
    }

    return 0;
}
