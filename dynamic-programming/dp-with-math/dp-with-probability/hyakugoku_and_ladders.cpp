// dp with probabilities (take best of two choices), EV of geometric dist.
// https://codeforces.com/contest/1245/problem/E

#include <bits/stdc++.h>
using namespace std;

constexpr auto INF = 1231231234;
using ld = long double;

ld expected_repeat(int dist) {
    ld prob_fail = (6 - dist) / 6.0;
    ld prob_success = dist / 6.0;
    return prob_fail / prob_success;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 10;
    auto grid = vector(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    int it = 0;
    auto indices = vector(n, vector<int>(n));
    map<int, pair<int, int>> mapping;
    for (int i = n - 1; i >= 0; i -= 2) {
        for (int j = 0; j < n; j++) {
            indices[i][j] = it;
            mapping[it] = {i, j};
            it++;
        }
        if (i < 1) continue;
        for (int j = n - 1; j >= 0; j--) {
            indices[i - 1][j] = it;
            mapping[it] = {i - 1, j};
            it++;
        }
    }

    auto dp = vector(n * n, vector<ld>(2, INF));  // dp[i][t] = ev at position i, must take ladder at pos i if (t == 1)
    int target = dp.size() - 1;
    dp[target][0] = 0.0;
    for (int i = target - 1; i >= 0; i--) {
        auto dist = target - i;
        ld stuck = dist <= 5 ? expected_repeat(dist) : 0.0;

        ld ev = 0.0;
        ld denom = min(6, dist);
        for (int roll = 1; roll <= 6; roll++) {
            if (roll > dist) continue;
            auto best = min(dp[i + roll][0], dp[i + roll][1]);
            ev += 1.0 / denom * (best + 1);
        }

        dp[i][0] = stuck + ev;
        auto [x, y] = mapping[i];
        if (grid[x][y] > 0) {
            auto pos = indices[x - grid[x][y]][y];
            dp[i][1] = dp[pos][0];
        }
    }
    auto sol = dp[0][0];
    cout << setprecision(11) << fixed << sol << '\n';
}
