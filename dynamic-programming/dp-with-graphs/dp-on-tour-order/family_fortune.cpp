// tour ordering, dynamic programming (on trees - skipping subtrees, space saving, forward propagating)
// https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3788
// 2011 Southeast USA Regional

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int INF = 1031231234;
const int MAXN = 100001;

typedef vector<int> graph[MAXN];

graph g;
int wealth[MAXN], ordered[MAXN], jump[MAXN], dp[2][MAXN];
bool newPossible;

int timer;
void tour(graph &g, int curr, int prev = -1)
{
    int st = timer++;
    ordered[st] = curr;
    for (int neighbor: g[curr]) if (neighbor != prev)
    {
        tour(g, neighbor, curr);
    }
    jump[st] = timer;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    while(true)
    {
        cin>>n>>k;
        if (n == 0 and k == 0) break;

        int root;
        for (int i = 0; i < n; i++)
        {
            int p;
            cin>>p>>wealth[i];
            if (p == 0) root = i;
            else
            {
                g[--p].push_back(i);
            }
        }

        timer = 0;
        tour(g, root);

        memset(dp[0], 0, sizeof(dp[0]));
        memset(dp[1], -INF, sizeof(dp[1]));

        for (int j = 0; j < k; j++)
        {
            newPossible = false;
            for (int i = 0; i < n; i++) if (dp[0][i] != -INF)
            {
                dp[0][i + 1] = max(dp[0][i + 1], dp[0][i]);
                dp[1][jump[i]] = max(dp[1][jump[i]], dp[0][i] + wealth[ordered[i]]);
                newPossible = true;
            }
            for (int i = 0; i <= n; i++)
            {
                dp[0][i] = dp[1][i];
                dp[1][i] = -INF;
            }
            if (!newPossible) break;
        }

        int sol = 0;
        for (int i = 0; i <= n; i++)
        {
            sol = max(sol, dp[0][i]);
            g[i].clear();
        }
        cout<<sol<<'\n';
    }

    return 0;
}
