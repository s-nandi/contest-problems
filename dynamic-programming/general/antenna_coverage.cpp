// dp (pick best of n choices), optimal way to extend intervals in order to cover an entire range
// https://codeforces.com/contest/1253/problem/E

#include <bits/stdc++.h>
using namespace std;

using interval = pair<int, int>;

constexpr auto INF = 1231231234;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<interval> intervals(n);
    vector<int> street(m + 1, -1);
    for (int i = 0; i < n; i++) {
        int x, s;
        cin >> x >> s;
        intervals[i] = {clamp(x - s, 1, m), clamp(x + s, 1, m)};
        for (int j = intervals[i].first; j <= intervals[i].second; j++) {
            street[j] = i;
        }
    }

    vector<int> dp(m + 1, INF);
    dp[0] = 0;
    for (int j = 1; j <= m; j++) {
        if (street[j] != -1) {
            dp[j] = dp[j - 1];
        } else {
            dp[j] = dp[j - 1] + 1;
            for (int i = 0; i < n; i++) {
                auto dist = j - intervals[i].second;
                if (dist >= 0) {
                    auto prev = max(0, intervals[i].first - dist - 1);
                    auto possible = dp[prev] + dist;
                    dp[j] = min(dp[j], possible);
                }
            }
        }
    }
    cout << dp[m] << '\n';
}
