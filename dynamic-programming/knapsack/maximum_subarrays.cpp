// dp (max k-disjoint subarrays)
// https://open.kattis.com/problems/maximumsubarrays
// 2018 North Central NA Regional

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 5000;
const int MAXK = 5000;
const ll INF = 1e18;

ll dp[MAXN + 5][MAXK + 5][2];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    vector <int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    for (int i = 0; i <= n; i++) for (int j = 0; j <= k; j++) for (int bit = 0; bit < 2; bit++)
        dp[i][j][bit] = -INF; // dp[i][j][bit] = max sum of k-disjoint subarrays using 1 .. i and including i iff (bit = 1)
    dp[0][0][0] = 0;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= k; j++)
        {
            if (j - 1 >= 0)
                dp[i][j][1] = max({dp[i - 1][j - 1][1], dp[i - 1][j - 1][0], dp[i - 1][j][1]}) + a[i];
            dp[i][j][0] = max(dp[i - 1][j][0], dp[i - 1][j][1]);
        }
    }
    cout << max(dp[n][k][0], dp[n][k][1]) << '\n';
}
