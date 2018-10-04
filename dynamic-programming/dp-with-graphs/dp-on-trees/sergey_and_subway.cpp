// dp on trees (postorder, finding total length of all paths in tree, finding # of odd length paths in tree), shrinking diameter by merging common-neighbor nodes
// http://codeforces.com/contest/1060/problem/E

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct edge{int to;};
typedef vector<vector<edge>> graph;

const int MAXN = 200000;

vector <int> sizes;
int getSizes(graph &g, int curr, int prev = -1)
{
    sizes[curr] = 1;
    for (edge e: g[curr]) if (e.to != prev)
        sizes[curr] += getSizes(g, e.to, curr);
    return sizes[curr];
}

vector <vector<ll>> dp;
ll totalOdd = 0;
void getOdd(graph &g, int curr, int prev = -1)
{
    dp[curr][1] = 0, dp[curr][0] = 1;
    for (edge e: g[curr]) if (e.to != prev)
    {
        getOdd(g, e.to, curr);
        totalOdd += dp[curr][0] * dp[e.to][0]; // child's even length paths turn into odd length paths
                                               // multiply this by current # of even length paths to get # of odd length paths using this edge
        totalOdd += dp[curr][1] * dp[e.to][1]; // ditto for child odd length and current od length paths
        dp[curr][1] += dp[e.to][0];
        dp[curr][0] += dp[e.to][1];
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    graph g(n);
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g[a].push_back({b});
        g[b].push_back({a});
    }

    sizes.resize(n);
    getSizes(g, 0);

    ll totalPaths = 0;
    for (int i = 0; i < n; i++)
    {
        for (edge e: g[i]) if (sizes[i] > sizes[e.to]) // make sure e.to is the lower node in rooted tree
            totalPaths += (ll) sizes[e.to] * (n - sizes[e.to]); // edge shows up each time path crosses it = (# nodes in left subtree) * (# nodes in right subtree)
    }

    dp.resize(n, vector <ll>(2));
    getOdd(g, 0);

    ll sol = (totalPaths + totalOdd) / 2; // even length paths get halved, odd length paths turn into (d + 1) / 2 distance
    cout << sol << '\n';
}
