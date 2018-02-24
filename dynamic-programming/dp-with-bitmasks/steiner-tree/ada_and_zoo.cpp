//steiner tree, sum of steiner tree cost for all subsets of steiner points
//http://www.spoj.com/problems/ADAZOO/

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

#define INF 1031231234

int dx[4] = {0, -1, 0, 1};
int dy[4] = {-1, 0, 1, 0};

int mapping(int i, int j, int m)
{
    return i * m + j;
}

int absval(int i)
{
    return i > 0 ? i : -i;
}

int steinerTree(vector <vector<int>> &costs, vector <int> &terminals, int n, int t)
{
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++)
        {
            costs[i][j] = min(costs[i][j], costs[i][k] + costs[k][j]);
        }
    }

    int dp[1 << t][n];
    memset(dp, INF, sizeof(dp));

    for (int i = 0; i < t; i++)
    {
        dp[1 << i][terminals[i]] = 0;
    }

    int sol = 0;
    for (int mask = 1; mask < (1 << t); mask++)
    {
        int best = INF;
        for (int i = 0; i < n; i++)
        {
            for (int submask = mask; submask > (mask ^ submask); submask = (submask - 1) & mask)
            {
                dp[mask][i] = min(dp[mask][i], dp[submask][i] + dp[mask ^ submask][i]);
            }

            if (dp[mask][i] == INF) continue;

            for (int j = 0; j < n; j++)
            {
                dp[mask][j] = min(dp[mask][j], dp[mask][i] + costs[i][j]);
            }

            best = min(best, dp[mask][i]);
        }
        sol += best;
    }

    return sol;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin>>T;
    while (T--)
    {
        int n;
        cin>>n;

        vector <int> heights(n * n);

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin>>heights[mapping(i, j, n)];
            }
        }

        vector <vector<int>> costs(n * n, vector<int>(n * n, INF));

        for (int i = 0; i < n * n; i++)
        {
            costs[i][i] = 0;
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                for (int dir = 0; dir < 4; dir++)
                {
                    int nx = i + dx[dir], ny = j + dy[dir], p = mapping(i, j, n);

                    if (nx >= 0 and ny >= 0 and nx < n and ny < n)
                    {
                        int q = mapping(nx, ny, n);
                        costs[p][q] = absval(heights[p] - heights[q]);
                        costs[q][p] = costs[p][q];
                    }
                }
            }
        }

        int q;
        cin>>q;

        vector <int> terminals(q);

        for (int i = 0; i < q; i++)
        {
            int x, y;
            cin>>x>>y;
            terminals[i] = mapping(x, y, n);
        }

        cout<<steinerTree(costs, terminals, n * n, q)<<'\n';
    }

    return 0;
}
