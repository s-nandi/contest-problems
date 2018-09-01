// travelling salesman problem
// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1437

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int INF = 1031231234;

struct position
{
    int i, j;

    int dist(position o)
    {
        return abs(o.i - i) + abs(o.j - j);
    }
};

int tsp(vector <vector<int>> &costs, int n)
{
    int dp[1 << n][n];
    memset(dp, INF, sizeof(dp));

    dp[0][0] = 0;

    for (int mask = 1; mask < (1 << n); mask++)
    {
        for (int i = 0; i < n; i++)
        {
            if (!(mask & (1 << i))) continue;

            int exclude = mask ^ (1 << i);

            for (int j = 0; j < n; j++)
            {
               dp[mask][i] = min(dp[mask][i], dp[exclude][j] + costs[j][i]);
            }
        }
    }

    int sol = INF;
    for (int i = 0; i < n; i++)
    {
        sol = min(sol, dp[(1 << n) - 1][i] + costs[i][0]);
    }

    return sol;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin>>T;

    while(T--)
    {
        int r, c;
        cin>>r>>c;

        vector <position> positions(1);

        cin>>positions[0].i>>positions[0].j;

        int n;
        cin>>n;
        n++;

        positions.resize(n);

        for (int i = 1; i < n; i++)
        {
            cin>>positions[i].i>>positions[i].j;
        }

        vector <vector<int>> costs(n, vector<int>(n));

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                costs[i][j] = positions[i].dist(positions[j]);
            }
        }

        cout<<"The shortest path has length "<<tsp(costs, n)<<'\n';
    }

    return 0;
}
