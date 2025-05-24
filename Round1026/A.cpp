#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tests;
    cin >> tests;
    while (tests--) {
        int size;
        cin >> size;
        vector<int> arr(size);
        for (int &x : arr) 
            cin >> x;

        sort(arr.begin(), arr.end());

        int maxKeep = 1;  
        for (int p = 0; p < 2; p++) {
            int start = -1, end = -1;
            for (int i = 0; i < size; i++) {
                if ((arr[i] & 1) == p) {
                    if (start == -1) 
                        start = i;
                    end = i;
                }
            }
            if (start != -1) 
                maxKeep = max(maxKeep, end - start + 1);
        }

        cout << (size - maxKeep) << "\n";
    }

    return 0;
}
