//dynamic programming, prefix function, precomputing ocmpression of all substrings
//https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1963

#include <iostream>
#include <vector>

using namespace std;

vector <int> prefixFunction(string &s)
{
    int n = s.length();
    vector <int> pf(n);

    for (int i = 1; i < n; i++)
    {
        int j = pf[i - 1];
        while (j > 0 and s[i] != s[j])
        {
            j = pf[j - 1];
        }
        if (s[i] == s[j]) pf[i] = j + 1;
        else pf[i] = 0;
    }

    return pf;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (true)
    {
        string s;
        cin>>s;
        int n = s.length();

        if (n == 1 and s[0] == '*') break;

        vector <vector<int>> compressed(n, vector<int>(n)), dp(n, vector<int>(n));

        for (int i = 0; i < n; i++)
        {
            string currStr = s.substr(i, n - i);
            auto pf = prefixFunction(currStr);

            compressed[i][i] = 1;
            for (int j = 1; i + j < n; j++)
            {
                int len = j + 1 - pf[j];
                if (pf[j] > 0 and (j + 1) % len == 0)
                {
                    compressed[i][i + j] = len;
                }
                else
                {
                    compressed[i][i + j] = j + 1;
                }
            }
        }

        for (int i = 0; i < n; i++)
        {
            dp[i][i] = 1;
        }
        for (int l = 2; l <= n; l++)
        {
            for (int i = 0; i + l - 1 < n; i++)
            {
                int j = i + l - 1;

                if (compressed[i][j] < j - i + 1) dp[i][j] = dp[i][i + compressed[i][j] - 1];
                else dp[i][j] = j - i + 1;

                for (int k = i; k < j; k++)
                {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
                }
            }
        }

        cout<<dp[0][n - 1]<<endl;
    }

    return 0;
}
