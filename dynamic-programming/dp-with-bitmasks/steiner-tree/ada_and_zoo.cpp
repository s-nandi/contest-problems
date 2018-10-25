//steiner tree, sum of steiner tree cost for all subsets of steiner points
//http://www.spoj.com/problems/ADAZOO/

#include <bits/stdc++.h>
using namespace std;

const int INF = 1031231234;

int dx[4] = {0, -1, 0, 1};
int dy[4] = {-1, 0, 1, 0};

int mapping(int i, int j, int m){return i * m + j;}

vector <vector<int>> steinerTree(vector <vector<int>> &costs, vector <int> &terminals, int n, int t)
{
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                costs[i][j] = min(costs[i][j], costs[i][k] + costs[k][j]);

    vector <vector<int>> dp(1 << t, vector <int>(n, INF));
    for (int i = 0; i < t; i++)
        dp[1 << i][terminals[i]] = 0;
    for (int bm = 1; bm < (1 << t); bm++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int sm = bm; sm > (sm ^ bm); sm = (sm - 1) & bm)
                dp[bm][i] = min(dp[bm][i], dp[sm][i] + dp[bm ^ sm][i]);
            if (dp[bm][i] == INF)
                continue;
            for (int j = 0; j < n; j++)
                dp[bm][j] = min(dp[bm][j], dp[bm][i] + costs[i][j]);
        }
    }
    return dp;
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
                cin >> heights[mapping(i, j, n)];
            }
        }

        int sz = n * n;
        vector <vector<int>> costs(n * n, vector<int>(sz, INF));
        for (int i = 0; i < n * n; i++)
            costs[i][i] = 0;
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
                        costs[p][q] = costs[q][p] = abs(heights[p] - heights[q]);
                    }
                }
            }
        }

        int q;
        cin >> q;
        vector <int> terminals(q);
        for (int i = 0; i < q; i++)
        {
            int x, y;
            cin >> x >> y;
            terminals[i] = mapping(x, y, n);
        }

        int sol = 0;
        auto st = steinerTree(costs, terminals, sz, q);
        for (int bm = 1; bm < (1 << q); bm++)
        {
            int best = INF;
            for (int i: st[bm])
                best = min(best, i);
            sol += best;
        }
        cout << sol << '\n';
    }
}
