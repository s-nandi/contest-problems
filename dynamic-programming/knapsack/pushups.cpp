// dp (knapsack style)
// https://codeforces.com/gym/100827
// 2014 Pacific Northwest Regional

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MAXN = 5000;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin>>T;
    while(T--)
    {
        int n, m;
        cin>>n>>m;

        vector <int> scores(m);
        for (int i = 0; i < m; i++)
        {
            cin>>scores[i];
        }

        // dp[score][pushups]
        bool dp[MAXN + 1][MAXN + 1];
        memset(dp, false, sizeof(dp));
        dp[0][0] = true;

        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j <= n; j++)
            {
                for (int v: scores)
                {
                    if (v + i > n or v + i + j > n)
                        continue;
                    dp[v + i][v + i + j] |= dp[i][j];
                }
            }
        }

        int sol = -1;
        for (int i = 0; i <= n; i++)
        {
            if (dp[i][n])
                sol = i;
        }
        cout<<sol<<'\n';
    }
}
