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
vector <int> values;

struct binaryLift
{
    int sz, h = 0;
    vector <vector<int>> table;
    vector <int> results, prefixSums; vector <ll> distances;

    binaryLift(vector <vector<edge>> &graph)
    {
        sz = graph.size();
        while (1 << h < sz) h++;
        table.resize(sz, vector<int>(h, -1)), values.resize(sz), results.resize(sz), prefixSums.resize(sz), distances.resize(sz);

        build(graph, 0);
    }

    void build(vector <vector<edge>> &graph, int curr, ll currDistance = 0)
    {
        distances[curr] = currDistance;
        for (int i = 1; i < h; i++)
        {
            table[curr][i] = table[curr][i - 1] != -1 ? table[table[curr][i - 1]][i - 1] : -1;
        }
        for (edge e: graph[curr])
        {
            table[e.to][0] = curr;
            build(graph, e.to, currDistance + e.weight);
        }
    }

    void solve(vector <vector<edge>> &graph)
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
        push(graph, 0);
    }

    int push(vector <vector<edge>> &graph, int curr)
    {
        results[curr] = 0;
        for (edge e: graph[curr])
        {
            results[curr] += push(graph, e.to);
        }
        return results[curr] + prefixSums[curr];
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin>>n;

    graph.resize(n);
    values.resize(n);

    for (int i = 0; i < n; i++)
    {
        cin>>values[i];
    }
    for (int i = 1; i < n; i++)
    {
        int p; ll w;
        cin>>p>>w;
        graph[--p].push_back({i, w});
    }
    binaryLift bl(graph);
    bl.solve(graph);

    for (int res: bl.results)
    {
        cout<<res<<' ';
    }
    cout<<'\n';

    return 0;
}
