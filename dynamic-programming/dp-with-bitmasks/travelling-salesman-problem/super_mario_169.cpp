// tsp (tsp solutions used as cost matrix for nested tsp)
// https://open.kattis.com/problems/supermario169
// 2014 NAIPC

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

const double INF = 123123123123123;
const int MAXN = 13;

struct pt
{
    int x, y, z;

    long long sq(int v){return (long long) v * v;}
    double dist(pt &o)
    {
        return sqrt(sq(x - o.x) + sq(y - o.y) + sq(z - o.z));
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    pt start;
    cin>>n>>start.x>>start.y>>start.z;

    vector <pt> switches(n);
    vector <vector<pt>> coins(n);

    for (int i = 0; i < n; i++)
    {
        int k, sx, sy, sz;
        cin>>k>>sx>>sy>>sz;
        switches[i] = {sx, sy, sz};

        coins[i].resize(k);
        for (int j = 0; j < k; j++)
        {
            int cx, cy, cz;
            cin>>cx>>cy>>cz;
            coins[i][j] = {cx, cy, cz};
        }
    }

    // dp[i][j] = cost of getting all coins belonging to switch i starting at the switch and ending at coin j
    double dp[MAXN][MAXN];

    for (int it = 0; it < n; it++)
    {
        int numCoins = coins[it].size();

        double tsp_coins[1 << MAXN][MAXN];
        for (int i = 0; i < (1 << MAXN); i++)
            for (int j = 0; j < MAXN; j++)
                tsp_coins[i][j] = INF;

        for (int i = 0; i < numCoins; i++)
            tsp_coins[1 << i][i] = switches[it].dist(coins[it][i]);

        for (int bm = 1; bm < (1 << numCoins); bm++)
        {
            for (int i = 0; i < numCoins; i++) if (bm & (1 << i))
            {
                int sm = bm ^ (1 << i);
                for (int j = 0; j < numCoins; j++) if (sm & (1 << j))
                {
                    double possible = tsp_coins[sm][j] + coins[it][i].dist(coins[it][j]);
                    tsp_coins[bm][i] = min(tsp_coins[bm][i], possible);
                }
            }
        }

        int FULL_COIN = (1 << numCoins) - 1;
        for (int i = 0; i < numCoins; i++)
        {
            dp[it][i] = tsp_coins[FULL_COIN][i];
        }
    }

    // tsp_switches[mask][i] = minimum cost of getting coins belonging to on-bit switches and ending at switch i
    // switch i's coins are NOT grabbed yet
    double tsp_switches[1 << MAXN][MAXN];
    for (int i = 0; i < (1 << MAXN); i++)
        for (int j = 0; j < MAXN; j++)
            tsp_switches[i][j] = INF;

    for (int i = 0; i < n; i++)
        tsp_switches[1 << i][i] = start.dist(switches[i]);

    for (int bm = 1; bm < (1 << n); bm++)
    {
        for (int i = 0; i < n; i++) if (bm & (1 << i))
        {
            int sm = bm ^ (1 << i);
            for (int j = 0; j < n; j++) if (sm & (1 << j))
            {
                for (int k = 0; k < coins[j].size(); k++)
                {
                    double possible = tsp_switches[sm][j] + dp[j][k] + coins[j][k].dist(switches[i]);
                    if (tsp_switches[bm][i] == -1)
                        tsp_switches[bm][i] = possible;
                    else
                        tsp_switches[bm][i] = min(tsp_switches[bm][i], possible);
                }
            }
        }
    }
    int FULL_SWITCH = (1 << n) - 1;
    double sol = INF;
    for (int i = 0; i < n; i++)
    {
        double complete_last = INF;
        for (int j = 0; j < coins[i].size(); j++)
            complete_last = min(complete_last, dp[i][j]); // cost to grab coins of last switch needs to be added
        tsp_switches[FULL_SWITCH][i] += complete_last;

        sol = min(sol, tsp_switches[FULL_SWITCH][i]);
    }
    cout<<fixed<<sol<<'\n';

    return 0;
}
