//dynamic programming (trees)
//http://codeforces.com/contest/462/problem/D

#include <iostream>
#include <vector>

using namespace std;

#define MOD 1000000007
#define ll long long

vector <vector<int>> graph;
vector <int> isBlack;
vector <ll> dp[2];
ll previous[2];

void dfs(int curr)
{
    dp[0][curr] = 1 - isBlack[curr];
    dp[1][curr] = isBlack[curr];

    for (int child: graph[curr])
    {
        dfs(child);

        previous[0] = dp[0][curr];
        previous[1] = dp[1][curr];
        dp[0][curr] = 0;
        dp[1][curr] = 0;

        dp[1][curr] = (previous[1] * (dp[0][child] + dp[1][child]) % MOD) % MOD;
        if(isBlack[curr] == 0)
        {
            dp[0][curr] = (previous[0] * (dp[0][child] + dp[1][child]) % MOD) % MOD;
            dp[1][curr] = (dp[1][curr] + (previous[0] * dp[1][child]) % MOD) % MOD;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin>>n;

    graph.resize(n);
    isBlack.resize(n);
    dp[1].resize(n);
    dp[0].resize(n);

    for (int i = 0; i < n - 1; i++)
    {
        int p;
        cin>>p;
        graph[p].push_back(i + 1);
    }

    for (int i = 0; i < n; i++)
    {
        cin>>isBlack[i];
    }

    dfs(0);

    cout<<dp[1][0]<<'\n';

    return 0;
}
