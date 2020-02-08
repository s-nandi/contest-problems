// knapsack, sqrt of sum trick
// https://open.kattis.com/problems/licenserenewal
// 2020 ProgNova

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)

using vi = vector<int>;

const int MAXT = 10005;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, s1, s2;
    cin >> n >> s1 >> s2;
    if (s1 > s2) swap(s1, s2);

    vi t(n);
    rep(i, 0, n) {
        cin >> t[i];
    }

    auto dp = vector(n + 1, vector<int>(MAXT));
    dp[0][0] = true;
    rep(i, 1, n + 1) {
        for (auto j = MAXT - 1; j >= 0; --j) {
            if (dp[i - 1][j]) dp[i][j] = true;
            if (j - t[i - 1] >= 0 and dp[i - 1][j - t[i - 1]]) dp[i][j] = true;
        }
    }

    int best = 0;
    auto sum = 0LL;
    rep(i, 0, n) {
        sum += t[i];
        rep(j, 0, s1 + 1) {
            if (dp[i + 1][j] and sum - j <= s2) {
                best = i + 1;
                break;
            }
        }
    }
    cout << best << '\n';
}
