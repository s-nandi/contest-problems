//binary lifting, partial sum on tree
//http://codeforces.com/problemset/problem/739/B

#include <iostream>
#include <vector>

using namespace std;

#define ll long long

struct edge
{
    int i;
    ll w;
};

vector <ll> values, distances;
vector <vector<edge>> graph;
vector <vector<int>> binaryLift;

vector <int> prefixSum;
vector <int> result;

int ln;

int logn(int n)
{
    int counter = 0;
    while (n > 0)
    {
        n >>= 1;
        counter++;
    }
    return counter;
}

void construct(int curr, ll dist, int currDepth)
{
    distances[curr] = dist;

    for (int i = 1; (1 << i) <= currDepth; i++)
    {
        binaryLift[curr][i] = binaryLift[binaryLift[curr][i - 1]][i - 1];
    }

    for (edge e: graph[curr])
    {
        int neighbor = e.i;
        ll weight = e.w;
        construct(neighbor, dist + weight, currDepth + 1);
    }
}

void solve(int node)
{
    ll lowerBound = distances[node] - values[node];

    int curr = node;
    for (int i = ln - 1; i >= 0; i--)
    {
        if (binaryLift[curr][i] != -1 and distances[binaryLift[curr][i]] >= lowerBound)
        {
            curr = binaryLift[curr][i];
        }
    }

    if (distances[curr] >= lowerBound)
    {
        prefixSum[curr]--;
        prefixSum[node]++;
    }
}

int push(int curr)
{
    int neighborSum = 0;

    for (edge e: graph[curr])
    {
        int neighbor = e.i;
        neighborSum += push(neighbor);
    }
    result[curr] = neighborSum;

    return result[curr] + prefixSum[curr];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin>>n;

    values.resize(n);
    distances.resize(n);
    graph.resize(n);

    ln = logn(n) + 2;

    binaryLift.resize(n, vector <int>(ln, -1));

    for (int i = 0; i < n; i++)
    {
        cin>>values[i];
    }

    for (int i = 1; i < n; i++)
    {
        int p;
        ll w;
        cin>>p>>w;
        --p;

        graph[p].push_back({i, w});
        binaryLift[i][0] = p;
    }

    construct(0, 0, 0);

    prefixSum.resize(n);
    result.resize(n);

    for (int i = 0; i < n; i++)
    {
        solve(i);
    }

    push(0);

    for (int res: result)
    {
        cout<<res<<" ";
    }
    cout<<'\n';

    return 0;
}
