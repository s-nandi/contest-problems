// dynamic programming (coin change style)
// https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&category=704&page=show_problem&problem=5387
// 2015 Greater NY Regional

#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin>>T;
    while (T--)
    {
        int k, n, a, b;
        cin>>k>>n>>a>>b;

        vector <int> isGood(n + 1, true);
        vector <int> good;
        for (int i = 0; i <= n; i++)
        {
            int seq = a + i * b;
            if (seq > n) break;
            isGood[seq] = false;
        }

        for (int i = 1; i <= n; i++)
        {
            if (isGood[i])
                good.push_back(i);
        }

        vector <int> dp(n + 1);
        dp[0] = 1;
        for (int i = 0; i <= n; i++)
        {
            for (int g: good)
            {
                if (i - g < 0) continue;
                dp[i] += dp[i - g];
            }
        }
        cout<<k<<" "<<dp[n]<<'\n';
    }

    return 0;
}
