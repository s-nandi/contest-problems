// dp on tour ordering (skipping subtrees, forward propagating)
// https://open.kattis.com/problems/redblacktree
// 2018 NAIPC

#include <iostream>
#include <vector>

using namespace std;

struct edge{int to;};
typedef vector <vector<edge>> graph;

const int MOD = 1000000007;

int timer = 0;
vector <int> jump, ordered;
void tour(graph &g, int curr)
{
    ordered[timer] = curr;
    timer++;
    for (edge e: g[curr])
        tour(g, e.to);
    jump[curr] = timer;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    graph g(n);
    for (int i = 0; i < n - 1; i++)
    {
        int p;
        cin >> p;
        g[--p].push_back({i + 1});
    }

    vector <int> red(n);
    for (int i = 0; i < m; i++)
    {
        int r;
        cin >> r;
        red[--r] = 1;
    }

    jump.resize(n), ordered.resize(n);
    tour(g, 0);

    vector <vector<int>> dp(n + 1, vector <int>(m + 1, 0));
    dp[0][0] = 1;

    for (int i = 0; i < n; i++)
    {
        int curr = ordered[i];
        for (int j = 0; j <= m; j++)
        {
            dp[i + 1][j] = (dp[i + 1][j]  + dp[i][j]) % MOD;
            dp[jump[curr]][j + red[curr]] = (dp[jump[curr]][j + red[curr]] + dp[i][j]) % MOD;
        }
    }

    for (int i = 0; i <= m; i++)
    {
        cout << dp[n][i] << '\n';
    }
}
