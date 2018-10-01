// greedy (exchange argument), dp (knapsack after using comparator, reconstructing solution)
// http://codeforces.com/gym/101623 (problem I)
// 2017 Northwest European Regional

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500;
const int MAXC = 10000;

struct app
{
    int download, storage, index;

    bool operator < (const app &o) const
    {
        return (download - storage) > (o.download - o.storage);
    }
};

int dp[MAXN + 5][MAXC + 5];
bool use[MAXN + 5][MAXC + 5];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, c;
    cin >> n >> c;

    vector <app> apps(n);
    for (int i = 0; i < n; i++)
    {
        int d, s;
        cin >> d >> s;
        apps[i] = {d, s, i + 1};
    }
    sort(apps.begin(), apps.end());

    memset(dp, 0, sizeof(dp));
    memset(use, false, sizeof(use));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= c; j++)
        {
            if (dp[i][j] >= dp[i + 1][j])
            {
                dp[i + 1][j] = dp[i][j];
                use[i + 1][j] = false;
            }

            int take = j + apps[i].storage;
            if (j + max(apps[i].storage, apps[i].download) <= c and dp[i][j] + 1 >= dp[i + 1][take])
            {
                dp[i + 1][take] = dp[i][j] + 1;
                use[i + 1][take] = true;
            }
        }
    }

    int best = 0;
    for (int i = 0; i <= c; i++)
    {
        if (dp[n][i] >= dp[n][best])
            best = i;
    }

    vector <int> sol;
    int curr = best;
    for (int i = n; i > 0; i--)
    {
        if (use[i][curr])
        {
            sol.push_back(apps[i - 1].index);
            curr -= apps[i - 1].storage;
        }
    }
    reverse(sol.begin(), sol.end());

    cout << dp[n][best] << '\n';
    if (!sol.empty())
    {
        for (int i: sol)
            cout << i << " ";
        cout << '\n';
    }
}
