//dynamic programming (bitmask)
//https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&page=show_problem&problem=5374
//2015 Mid-Central Regional

#include <iostream>
#include <vector>

using namespace std;

#define INF 1231231234

int dp[1 << 10][10];
int cost[10][10];

int quickChange(string a, string b)
{
    int acc = 0;
    for (char c: a)
    {
        int pos = b.find_first_of(c);
        acc += pos != string::npos ? 1 : 0;
    }
    return acc;
}

int main()
{
    int n;
    while (cin>>n)
    {
        vector <string> dances(n);
        for (int i = 0; i < n; i++)
        {
            cin>>dances[i];
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                cost[i][j] = quickChange(dances[i], dances[j]);
                cost[j][i] = cost[i][j];
            }
        }

        for (int mask = 1; mask < 1 << n; mask++)
        {
            for (int i = 0; i < n; i++)
            {
                dp[mask][i] = INF;

                if (!(mask & (1 << i))) continue;

                int best = INF;
                for (int j = 0; j < n; j++)
                {
                    int exclude = mask ^ (1 << i);

                    if (exclude == 0)
                    {
                        best = 0;
                        break;
                    }
                    else
                    {
                        best = min(best, dp[exclude][j] + cost[j][i]);
                    }
                }

                dp[mask][i] = best;
            }
        }

        int sol = INF;
        for (int i = 0; i < n; i++)
        {
            sol = min(sol, dp[(1 << n) - 1][i]);
        }
        cout<<sol<<'\n';
    }

    return 0;
}
