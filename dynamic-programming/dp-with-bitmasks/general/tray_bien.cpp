// dp w/ bitmask (calculating transition from column to column w/ some already filled squares)
// https://open.kattis.com/problems/tray
// 2015 East Central NA Regional

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector <int> pieces = {1 << 0, 1 << 0 | 1 << 3, 1 << 0 | 1 << 1};

ll dfs(int mask, int goal, int i) // returns # of ways to fill the left column while placing piece at row i: "mask" is already filled, "goal" is your target
{
    if (i == 3 and mask == goal)
        return 1;
    else if (mask & (1 << i)) // if i-th row of left column is filled, go to next row
        return dfs(mask, goal, i + 1);

    ll res = 0;
    for (int piece: pieces)
    {
        int skip = piece == 3 ? 2 : 1;
        if (i + skip > 3) // make sure that piece doesn't go off the bottom of grid
            continue;

        int lifted = piece << i;
        if (lifted & mask) // make sure that piece isn't placed on filled square
            continue;

        int added = mask | lifted;
        if ((added & goal) != added) // make sure that mask is submask of goal
            continue;

        auto delta = dfs(added, goal, i + skip);
        res += delta;
    }
    return res;
}

ll getTransitions(int left, int right, int preexisting)
{
    int mask = left | (preexisting << 3);
    int goal = 7 | (right << 3);
    return dfs(mask, goal, 0);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> m >> n;

    int col[m + 1];
    memset(col, 0, sizeof(col));
    for (int i = 0; i < n; i++)
    {
        double x, y;
        cin >> x >> y;
        col[int(x)] |= (1 << int(y));
    }

    vector <vector<ll>> dp(m + 1, vector<ll>(1 << 3, 0)); // dp[i][mask] = # of placing pieces to fill grid up to column i-1 with i-th column filled w/ mask
    dp[0][col[0]] = 1;
    for (int i = 0; i < m; i++)
    {
        for (int bm = 0; bm < 8; bm++) if (dp[i][bm] > 0)
        {
            for (int bm2 = 0; bm2 < 8; bm2++)
            {
                dp[i + 1][bm2] += dp[i][bm] * getTransitions(bm, bm2, col[i + 1]);
            }
        }
    }
    cout << dp[m][0] << '\n';
}
