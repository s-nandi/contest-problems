//dp (maximum partitioning), greedy, bitmask
//http://codeforces.com/contest/981/problem/D

#include <iostream>
#include <vector>

using namespace std;

#define ll long long

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int k, n;
    cin>>n>>k;

    ll a[n], sums[n + 1][n + 1];

    for (int i = 0; i < n; i++)
    {
        cin>>a[i];
    }

    for (int i = 1; i <= n; i++)
    {
        sums[i][i] = a[i - 1];
        for (int j = i + 1; j <= n; j++)
        {
            sums[i][j] = sums[i][j - 1] + a[j - 1];
        }
    }

    ll curr = 0;
    for (int pos = 55; pos >= 0; pos--)
    {
        ll attempt = curr + (1LL << pos);

        bool possible[n + 1][n + 1];
        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j <= n; j++)
            {
                possible[i][j] = ((sums[i][j] & attempt) == attempt);
            }
        }

        int dp[n + 1][k + 1];
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;

        for (int i = 1; i <= n; i++)
        {
            for (int p = 1; p <= k; p++)
            {
                for (int j = 1; j <= i; j++)
                {
                    dp[i][p] = max(dp[i][p], dp[i - j][p - 1] & possible[i - j + 1][i]);
                }
            }
        }

        if (dp[n][k])
            curr = attempt;
    }

    cout<<curr<<'\n';

    return 0;
}
