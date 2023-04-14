// dp with bitmasks (tsp style), find cycle of nodes s.t. every node is at most 1 distance away from some node in the cycle
// https://codeforces.com/contest/1804/problem/E

#include <bits/stdc++.h>
using namespace std;

using graph = vector<vector<int>>;

int highest(int i) {
    if (i == 0) return -1;
    return 31 - __builtin_clz(i);
}

int main() {
    int n, m;
    cin >> n >> m;
    graph g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int FULL = (1 << n) - 1;
    auto good = vector(1 << n, false);
    for (int bm = 0; bm < (1 << n); bm++) {
        int canreach = bm;
        for (int i = 0; i < n; i++) {
            if (!((1 << i) & bm)) continue;
            for (auto to : g[i]) {
                canreach |= 1 << to;
            }
        }
        good[bm] = canreach == FULL;
    }

    int cyclemask = -1;
    int lastnode = -1;
    // dp[mask][i], implicitly start at highest-bit of mask
    auto dp = vector(1 << n, vector<optional<int>>(n, nullopt));
    for (int i = 0; i < n; i++) {
        dp[1 << i][i] = -1;
    }
    for (int bm = 1; bm < (1 << n); bm++) {
        for (int last = 0; last < n; last++) {
            if (dp[bm][last] == nullopt) continue;

            for (int next : g[last]) {
                if (bm & (1 << next)) {
                    if (good[bm] and highest(bm) == next) {
                        cyclemask = bm;
                        lastnode = last;
                        goto done;
                    } else {
                        continue;
                    }
                }
                // maintain invariant that the starting node of the cycle (mask) is the highest bit
                // otherwise we get false positives
                if (next > highest(bm)) continue;
                int nbm = bm | (1 << next);
                dp[nbm][next] = last;
            }
        }
    }
done:
    if (cyclemask == -1) {
        cout << "No" << '\n';
        exit(0);
    }

    auto pairing = vector<int>(n, -1);
    vector<int> cycle;
    for (int mask = cyclemask, curr = lastnode; mask; mask -= 1 << cycle.back()) {
        cycle.push_back(curr);
        curr = *dp[mask][curr];
    }

    for (int i = 0; i < cycle.size(); i++) {
        int j = (i + 1) % cycle.size();
        pairing[cycle[i]] = cycle[j];
    }
    for (int i = 0; i < n; i++) {
        if (pairing[i] != -1) continue;
        for (int to : g[i]) {
            if (cyclemask & (1 << to)) {
                pairing[i] = to;
            }
        }
    }
    cout << "Yes" << '\n';
    for (auto i : pairing) {
        cout << (i + 1) << ' ';
    }
    cout << '\n';
}
