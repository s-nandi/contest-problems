// dp on digits (# of palindromes with given subsequence)
// https://open.kattis.com/problems/makingpalindromes
// 2018 Singapore Preiminary

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

typedef long long ll;

const int MAXN = 200;
const int MOD = 1000000007;

int dp[MAXN + 5][MAXN + 5][MAXN + 5];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin>>n;

    string s;
    cin>>s;

    memset(dp, 0, sizeof(dp));
    dp[0][0][0] = 1;

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            for (int k = 0; k <= n; k++)
            {
                for (unsigned char c = 'A'; c <= 'Z'; c++)
                {
                    bool fr = j < n and c == s[j];
                    bool bk = n - 1 - k >= 0 and c == s[n - 1 - k];

                    if (fr and bk)
                        dp[i + 1][j + 1][k + 1] = (dp[i + 1][j + 1][k + 1] + dp[i][j][k]) % MOD;
                    else if (fr)
                        dp[i + 1][j + 1][k] = (dp[i + 1][j + 1][k] + dp[i][j][k]) % MOD;
                    else if (bk)
                        dp[i + 1][j][k + 1] = (dp[i + 1][j][k + 1] + dp[i][j][k]) % MOD;
                    else
                        dp[i + 1][j][k] = (dp[i + 1][j][k] + dp[i][j][k]) % MOD;
                }
            }
        }
    }

    int sol = 0;
    for (int i = 0; i <= n; i++)
    {
        for (int j = n - i; j <= n; j++)
        {
            sol = (sol + dp[n][i][j]) % MOD;
        }
    }

    cout<<sol<<'\n';
    return 0;
}
