//dp on trees, finding diameter
//http://www.spoj.com/problems/PT07Z/

#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> graph;

vector <int> dp[2];

int dfs(graph &g, int curr, int prev)
{
    pair <int, int> best = {-1, -1};
    int diameter = 0;
    for (int neighbor: g[curr]) if (neighbor != prev)
    {
        diameter = max(diameter, dfs(g, neighbor, curr));

        if (dp[0][neighbor] > best.first)
        {
            best.second = best.first;
            best.first = dp[0][neighbor];
        }
        else if(dp[0][neighbor] > best.second)
        {
            best.second = dp[0][neighbor];
        }
    }
    if (best.second != -1) dp[1][curr] = best.first + best.second + 2;
    if (best.first != -1) dp[0][curr] = best.first + 1;

    diameter = max(diameter, dp[0][curr]);
    diameter = max(diameter, dp[1][curr]);

    return diameter;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin>>n;

    graph g(n);
    dp[0].resize(n), dp[1].resize(n);

    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin>>a>>b;
        --a, --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    cout<<dfs(g, 0, -1)<<'\n';

    return 0;
}
