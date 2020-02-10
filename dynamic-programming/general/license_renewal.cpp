// knapsack
// https://open.kattis.com/problems/licenserenewal
// 2020 ProgNova

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define all(a) begin(a),end(a)

using ll = long long;
using vi = vector<int>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, s1, s2;
    cin >> n >> s1 >> s2;
    if (s1 > s2) swap(s1, s2);

    vi t(n);
    trav(i, t) cin >> i;

    // dp[i][j] = can fit some of first i elements s.t. partition has j weight
    auto dp = vector(n + 1, vector<int>(s1 + 1));
    // maxs[i] = max s s.t. dp[i][j] = true (s <= s1)
    auto maxs = vector<int>(n + 1);

    dp[0][0] = true;
    rep(i, 1, n + 1) {
        rep (j, 0, s1 + 1) {
            if (j >= t[i - 1])
                dp[i][j] = dp[i - 1][j] or dp[i - 1][j - t[i - 1]];
            else
                dp[i][j] = dp[i - 1][j];
            
            if (dp[i][j]) maxs[i] = j;
        }
    }

    auto psums = vector<ll>(n);
    partial_sum(all(t), begin(psums));

    int sol = 0;
    rep(i, 0, n) {
        auto rem = psums[i] - maxs[i];
        if (rem <= s2) sol = i + 1;
    }
    cout << sol << '\n';
}
