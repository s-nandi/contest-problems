//dynamic programming, prefix sum
//http://codeforces.com/contest/909/problem/C

#include <iostream>
#include <vector>

using namespace std;

#define MOD 1000000007

int main()
{
    int n;
    cin>>n;

    vector <char> com(n);

    for (int i = 0; i < n; i++)
    {
        char c;
        cin>>com[i];
    }

    int dp[n][n];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            dp[i][j] = 0;
        }
    }

    dp[0][0] = 1;

    for (int i = 1; i < n; i++)
    {
        if (com[i - 1] == 's')
        {
            for (int j = n - 1; j >= 0; j--)
            {
                dp[i][j] = (dp[i][j] + dp[i - 1][j]) % MOD;

                if (j + 1 < n)
                {
                    dp[i][j] = (dp[i][j] + dp[i][j + 1]) % MOD;
                }
            }
        }

        else
        {
            for (int j = 1; j < n; j++)
            {
                dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % MOD;
            }
        }
    }

    int sol = 0;
    for (int j = 0; j < n; j++)
    {
        sol = (sol + dp[n - 1][j]) % MOD;
    }
    cout<<sol<<'\n';

    return 0;
}
