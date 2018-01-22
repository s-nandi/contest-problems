//binary lifting (finding highest node with property), prefix sums on tree
//http://codeforces.com/problemset/problem/739/B

#include <iostream>
#include <vector>

using namespace std;

#define ll long long

struct edge
{
    int to; ll weight;
};

vector <vector<edge>> graph;

struct binaryLift
{
    int sz, ln;
    vector <vector<int>> table;
    vector <int> values, results, prefixSums; vector <ll> distances;

    binaryLift(int s)
    {
        sz = s;
        ln = 0;
        while (1 << ln < sz) ln++;
        table.resize(sz, vector<int>(ln, -1));
        distances.resize(sz); values.resize(sz); results.resize(sz); prefixSums.resize(sz);
    }

    void build(int curr, ll currDistance = 0)
    {
        distances[curr] = currDistance;

        for (int i = 1; i < ln; i++)
        {
            table[curr][i] = table[curr][i - 1] != -1 ? table[table[curr][i - 1]][i - 1] : -1;
        }
        for (edge e: graph[curr])
        {
            table[e.to][0] = curr;
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
            for (int i = ln - 1; i >= 0; i--)
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
    graph.resize(n);

    for (int i = 0; i < n; i++)
    {
        cin>>bl.values[i];
    }

    for (int i = 1; i < n; i++)
    {
        int p; ll w;
        cin>>p>>w;
        graph[--p].push_back({i, w});
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
