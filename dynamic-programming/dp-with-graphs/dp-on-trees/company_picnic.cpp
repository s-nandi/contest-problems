// dp on tree (postorder)
// https://open.kattis.com/problems/companypicnic
// 2017 North American Qualifier

#include <bits/stdc++.h>

using namespace std;

struct edge{int to;};
typedef vector <vector<edge>> graph;

map <string, int> mapping;
vector <string> invmapping;
int getIndex(string &s)
{
    if (mapping.count(s))
        return mapping[s];
    else
    {
        invmapping.push_back(s);
        int sz = mapping.size();
        return mapping[s] = sz;
    }
}

struct state
{
    double totalSpeed = 0.0;
    int numPairs = 0;

    bool operator < (const state &o) const
    {
        return tie(numPairs, totalSpeed) < tie(o.numPairs, o.totalSpeed);
    }

    state operator + (const state &o) const
    {
        return {totalSpeed + o.totalSpeed, numPairs + o.numPairs};
    }

    state operator - (const state &o) const
    {
        return {totalSpeed - o.totalSpeed, numPairs - o.numPairs};
    }
};

void solve(graph &g, int curr, vector <vector<state>> &dp, vector <double> &speeds)
{
    for (edge e: g[curr])
    {
        solve(g, e.to, dp, speeds);
        dp[curr][0] = dp[curr][0] + dp[e.to][1];
    }

    dp[curr][1] = dp[curr][0];
    for (edge e: g[curr])
    {
        state exclude = dp[curr][0] - dp[e.to][1];
        state added = {min(speeds[curr], speeds[e.to]), 1};

        dp[curr][1] = max(dp[curr][1], exclude + dp[e.to][0] + added);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    int root = -1;
    graph g(n);
    vector <double> speeds(n);
    for (int i = 0; i < n; i++)
    {
        string s, t;
        double speed;
        cin >> s >> speed >> t;

        int a = getIndex(s);
        speeds[a] = speed;
        if (t == "CEO")
            root = a;
        else
        {
            int b = getIndex(t);
            g[b].push_back({a});
        }
    }

    vector <vector<state>> dp(n + 1, vector <state>(2));
    solve(g, root, dp, speeds);

    double totalSpeed = dp[root][1].totalSpeed;
    int numPairs = dp[root][1].numPairs;
    cout << fixed << setprecision(6) << numPairs << " " << totalSpeed / numPairs << '\n';
}
