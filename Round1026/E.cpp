#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i] >> b[i];
        }

        if (n == 1) {
            cout << "YES\n1\n";
            continue;
        }

        vector<int> ua = a, ub = b;
        sort(ua.begin(), ua.end());
        ua.erase(unique(ua.begin(), ua.end()), ua.end());

        sort(ub.begin(), ub.end());
        ub.erase(unique(ub.begin(), ub.end()), ub.end());

        int A = ua.size(), B = ub.size(), V = A + B;

        vector<vector<pair<int, int>>> g(V);
        vector<int> deg(V);

        for (int i = 0; i < n; i++) {
            int u = lower_bound(ua.begin(), ua.end(), a[i]) - ua.begin();
            int v = lower_bound(ub.begin(), ub.end(), b[i]) - ub.begin() + A;
            g[u].emplace_back(v, i);
            g[v].emplace_back(u, i);
            deg[u]++;
            deg[v]++;
        }

        int odd = 0, s = 0;
        for (int i = 0; i < V; i++) {
            if (deg[i] % 2) {
                odd++;
                s = i;
            }
        }

        if (odd > 2) {
            cout << "NO\n";
            continue;
        }

        if (odd == 0) {
            for (int i = 0; i < V; i++) {
                if (deg[i]) {
                    s = i;
                    break;
                }
            }
        }

        vector<bool> used(n);
        vector<int> ptr(V);
        vector<int> trail;
        trail.reserve(n);
        vector<pair<int, int>> stk;
        stk.reserve(n + 1);
        stk.emplace_back(s, -1);

        while (!stk.empty()) {
            auto [u, ei] = stk.back();

            while (ptr[u] < (int)g[u].size() && used[g[u][ptr[u]].second]) ptr[u]++;

            if (ptr[u] == (int)g[u].size()) {
                stk.pop_back();
                if (ei != -1) trail.push_back(ei);
            } else {
                auto [v, idx] = g[u][ptr[u]++];
                used[idx] = true;
                stk.emplace_back(v, idx);
            }
        }

        if ((int)trail.size() != n) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
            for (int i = n - 1; i >= 0; i--) {
                cout << trail[i] + 1 << (i ? ' ' : '\n');
            }
        }
    }

    return 0;
}
