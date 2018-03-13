//binary lifting (finding highest node with property), prefix sums on tree
//http://codeforces.com/problemset/problem/739/B

#include <iostream>
#include <vector>

using namespace std;

#define ll long long

struct edge
{
    int to, w;
};
typedef vector<vector<edge>> graph;

vector <int> values;
struct binaryLift
{
    int sz, h = 0;
    graph g;
    vector <vector<int>> table;

    vector <int> sol, prefixSums; vector <ll> distances;

    binaryLift(graph &gr)
    {
        g = gr, sz = g.size(), calcHeight(), table.resize(sz, vector<int>(h, -1));
        sol.resize(sz), prefixSums.resize(sz), distances.resize(sz);
        build(0);
        solve();
    }

    void calcHeight(){while (1 << h < sz) h++;}

    void build(int curr, ll dist = 0)
    {
        distances[curr] = dist;
        for (int i = 1; i < h; i++) if (table[curr][i - 1] != -1)
        {
            table[curr][i] = table[table[curr][i - 1]][i - 1];
        }
        for (edge e: g[curr])
        {
            table[e.to][0] = curr;
            build(e.to, dist + e.w);
        }
    }

    void solve()
    {
        for (int node = 0; node < sz; node++)
        {
            int curr = node;
            for (int i = h - 1; i >= 0; i--)
            {
                if (table[curr][i] != -1 and distances[table[curr][i]] >= distances[node] - values[node])
                {
                    curr = table[curr][i];
                }
            }
            prefixSums[curr]--;
            prefixSums[node]++;
        }
        push(0);
    }

    int push(int curr)
    {
        sol[curr] = 0;
        for (edge e: g[curr])
        {
            sol[curr] += push(e.to);
        }
        return sol[curr] + prefixSums[curr];
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin>>n;

    graph g(n);
    values.resize(n);

    for (int i = 0; i < n; i++)
    {
        cin>>values[i];
    }
    for (int i = 1; i < n; i++)
    {
        int p, w;
        cin>>p>>w;
        g[--p].push_back({i, w});
    }
    binaryLift bl(g);

    for (int res: bl.sol)
    {
        cout<<res<<' ';
    }
    cout<<'\n';

    return 0;
}
