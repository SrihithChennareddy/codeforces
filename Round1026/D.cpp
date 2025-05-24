#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;
using ll = long long;
using Edge = pair<int,ll>;

bool check(int N, const vector<ll>& cap, const vector<vector<Edge>>& adj, ll X) {
    vector<ll> dp(N+1, numeric_limits<ll>::min());
    dp[1] = 0;
    for (int u = 1; u <= N; ++u) {
        if (dp[u] < 0) continue;
        ll cur = min(dp[u] + cap[u-1], X);
        for (auto &e : adj[u]) {
            int v = e.first;
            ll w = e.second;
            if (w > X) continue;
            if (cur < w) continue;
            dp[v] = max(dp[v], cur);
        }
    }
    return dp[N] >= 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N, M;
        cin >> N >> M;
        vector<ll> cap(N);
        for (int i = 0; i < N; ++i) cin >> cap[i];

        vector<vector<Edge>> adj(N+1);
        vector<ll> W;
        W.reserve(M);
        for (int i = 0; i < M; ++i) {
            int u, v;
            ll w;
            cin >> u >> v >> w;
            adj[u].emplace_back(v, w);
            W.push_back(w);
        }

        if (M == 0) {
            cout << (N == 1 ? 0 : -1) << "\n";
            continue;
        }

        sort(W.begin(), W.end());
        W.erase(unique(W.begin(), W.end()), W.end());

        ll answer = -1;
        int lo = 0, hi = (int)W.size() - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (check(N, cap, adj, W[mid])) {
                answer = W[mid];
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        cout << answer << "\n";
    }

    return 0;
}
