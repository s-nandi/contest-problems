//dynamic programming (postorder processing / storing previous sibling)
//https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3788

#include <iostream>
#include <vector>

using namespace std;

const int INF = 1031231234;

typedef vector<vector<int>> graph;

vector <int> wealth, dp;

void dfs(graph &g, int curr)
{
    vector <int> old(dp);
    for (int neighbor: g[curr])
    {
        dfs(g, neighbor);
    }
    for (int i = 1; i < dp.size(); i++)
    {
        dp[i] = max(dp[i], old[i - 1] + wealth[curr]);
    }
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

        graph g(n);
        wealth.assign(n, 0), dp.assign(k + 1, -INF);
        dp[0] = 0;

        int root;
        for (int i = 0; i < n; i++)
        {
            int p;
            cin>>p>>wealth[i];
            if (p == 0) root = i;
            else g[--p].push_back(i);
        }
        dfs(g, root);

        cout<<max(0, dp[k])<<'\n';
    }

    return 0;
}
