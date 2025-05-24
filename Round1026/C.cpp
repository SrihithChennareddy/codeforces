#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int obsCount;
        cin >> obsCount;

        vector<int> delta(obsCount);
        vector<int> lowerB(obsCount), upperB(obsCount);
        for (int i = 0; i < obsCount; ++i) cin >> delta[i];
        for (int i = 0; i < obsCount; ++i) cin >> lowerB[i] >> upperB[i];

        vector<int> minH(obsCount + 1), maxH(obsCount + 1);
        vector<int> stayMin(obsCount + 1), stayMax(obsCount + 1);
        vector<int> riseMin(obsCount + 1), riseMax(obsCount + 1);

        minH[0] = 0;
        maxH[0] = 0;
        bool ok = true;

        for (int i = 1; i <= obsCount; ++i) {
            int lo = lowerB[i - 1];
            int hi = upperB[i - 1];

            stayMin[i] = 1;
            stayMax[i] = 0;
            riseMin[i] = 1;
            riseMax[i] = 0;

            if (delta[i - 1] == 0) {
                stayMin[i] = max(minH[i - 1], lo);
                stayMax[i] = min(maxH[i - 1], hi);
                if (stayMin[i] > stayMax[i]) { ok = false; break; }
                minH[i] = stayMin[i];
                maxH[i] = stayMax[i];

            } else if (delta[i - 1] == 1) {
                riseMin[i] = max(minH[i - 1], lo - 1);
                riseMax[i] = min(maxH[i - 1], hi - 1);
                if (riseMin[i] > riseMax[i]) { ok = false; break; }
                minH[i] = riseMin[i] + 1;
                maxH[i] = riseMax[i] + 1;

            } else {
                stayMin[i] = max(minH[i - 1], lo);
                stayMax[i] = min(maxH[i - 1], hi);
                riseMin[i] = max(minH[i - 1], lo - 1);
                riseMax[i] = min(maxH[i - 1], hi - 1);

                int lowNew = INT_MAX;
                int highNew = INT_MIN;
                if (stayMin[i] <= stayMax[i]) {
                    lowNew = min(lowNew, stayMin[i]);
                    highNew = max(highNew, stayMax[i]);
                }
                if (riseMin[i] <= riseMax[i]) {
                    lowNew = min(lowNew, riseMin[i] + 1);
                    highNew = max(highNew, riseMax[i] + 1);
                }
                if (lowNew > highNew) { ok = false; break; }
                minH[i] = lowNew;
                maxH[i] = highNew;
            }
        }

        if (!ok) {
            cout << -1 << '\n';
            continue;
        }

        vector<int> result(obsCount);
        vector<int> height(obsCount + 1);
        height[obsCount] = minH[obsCount];

        for (int i = obsCount; i >= 1; --i) {
            if (delta[i - 1] == 0) {
                result[i - 1] = 0;
                height[i - 1] = height[i];

            } else if (delta[i - 1] == 1) {
                result[i - 1] = 1;
                height[i - 1] = height[i] - 1;

            } else {
                if (height[i] >= stayMin[i] && height[i] <= stayMax[i]) {
                    result[i - 1] = 0;
                    height[i - 1] = height[i];
                } else {
                    result[i - 1] = 1;
                    height[i - 1] = height[i] - 1;
                }
            }
        }

        for (int i = 0; i < obsCount; ++i) {
            if (i + 1 < obsCount) {
                cout << result[i] << ' ';
            } else {
                cout << result[i] << '\n';
            }
        }
    }
    return 0;
}
