//binary lifting (finding highest node with property), prefix sums on tree
//http://codeforces.com/problemset/problem/739/B

#include <iostream>
#include <vector>

using namespace std;

#define ll long long
#define LN 20

struct edge
{
    int to; ll weight;
};

struct binaryLift
{
    int sz;
    vector <vector<int>> table;
    vector <vector<edge>> graph;

    vector <int> values, results, prefixSums; vector <ll> distances;

    binaryLift(int s)
    {
        sz = s;
        table.resize(sz, vector<int>(LN, -1));
        graph.resize(s);

        distances.resize(sz); values.resize(sz); results.resize(sz); prefixSums.resize(sz);
    }

    void add_edge(int a, int b, ll w)
    {
        graph[a].push_back({b, w});
        table[b][0] = a;
    }

    void build(int curr, ll currDistance = 0)
    {
        distances[curr] = currDistance;
        for (int i = 1; i < LN; i++)
        {
            table[curr][i] = table[curr][i - 1] != -1 ? table[table[curr][i - 1]][i - 1] : -1;
        }
        for (edge e: graph[curr])
        {
            build(e.to, currDistance + e.weight);
        }
    }

    int push(int curr = 0)
    {
        results[curr] = 0;
        for (edge e: graph[curr])
        {
            results[curr] += push(e.to);
        }
        return results[curr] + prefixSums[curr];
    }

    void solve()
    {
        for (int node = 0; node < sz; node++)
        {
            int curr = node;
            for (int i = LN - 1; i >= 0; i--)
            {
                if (table[curr][i] != -1 and distances[table[curr][i]] >= distances[node] - values[node])
                {
                    curr = table[curr][i];
                }
            }
            prefixSums[curr]--;
            prefixSums[node]++;
        }
        push();
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin>>n;

    binaryLift bl(n);

    for (int i = 0; i < n; i++)
    {
        cin>>bl.values[i];
    }

    for (int i = 1; i < n; i++)
    {
        int p; ll w;
        cin>>p>>w;
        bl.add_edge(--p, i, w);
    }
    bl.build(0);
    bl.solve();
    for (int res: bl.results)
    {
        cout<<res<<' ';
    }
    cout<<'\n';

    return 0;
}
