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

int ln = 0;
vector <vector<int>> binaryLift;
vector <int> values, results, prefixSums; vector <ll> distances;

void buildLift(int curr, ll currDistance = 0)
{
    distances[curr] = currDistance;
    for (int i = 1; i < ln; i++)
    {
        binaryLift[curr][i] = binaryLift[curr][i - 1] != -1 ? binaryLift[binaryLift[curr][i - 1]][i - 1] : -1;
    }
    for (edge e: graph[curr])
    {
        binaryLift[e.to][0] = curr;
        buildLift(e.to, currDistance + e.weight);
    }
}

int push(int curr)
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
    for (int node = 0; node < graph.size(); node++)
    {
        int curr = node;
        for (int i = ln - 1; i >= 0; i--)
        {
            if (binaryLift[curr][i] != -1 and distances[binaryLift[curr][i]] >= distances[node] - values[node])
            {
                curr = binaryLift[curr][i];
            }
        }
        prefixSums[curr]--;
        prefixSums[node]++;
    }
    push(0);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin>>n;
    while (1 << ln < n) ln++;

    graph.resize(n);
    binaryLift.resize(n, vector<int>(ln, -1));
    distances.resize(n), values.resize(n), results.resize(n), prefixSums.resize(n);

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
    buildLift(0);

    solve();
    for (int res: results)
    {
        cout<<res<<' ';
    }
    cout<<'\n';

    return 0;
}
