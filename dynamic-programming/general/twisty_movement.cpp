//dynamic programming, longest increasing subsequence with reversal
//http://codeforces.com/contest/934/problem/C

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin>>n;

    vector <int> a(n);

    for (int i = 0; i < n; i++)
    {
        cin>>a[i];
    }

    int dp[2][n + 1][n + 1];
    memset(dp, 0, sizeof(dp));

    for (int i = 0; i < n; i++)
    {
        int oneTwos = 0, ones = 0;
        for (int j = i; j < n; j++)
        {
            if (a[j] == 1)
            {
                ones++;
            }
            else
            {
                oneTwos = max(oneTwos + 1, ones + 1);
            }
            dp[0][i][j] = max(oneTwos, ones);
        }
    }

    for (int i = n - 1; i >= 0; i--)
    {
        int oneTwos = 0, ones = 0;
        for (int j = i; j >= 0; j--)
        {
            if (a[j] == 1)
            {
                ones++;
            }
            else
            {
                oneTwos = max(oneTwos + 1, ones + 1);
            }
            dp[1][j][i] = max(oneTwos, ones);
        }
    }

    int sol = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            sol = max(sol, dp[0][0][i] + dp[1][i + 1][j] + dp[0][j + 1][n - 1]);
        }
    }

    cout<<sol<<'\n';

    return 0;
}
