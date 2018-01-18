//dfs traversal, interval decomposition
//https://open.kattis.com/problems/securitybadge (2017 Mid-Atlantic Regional)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct interval
{
    int left, right;
    bool contains (interval o)
    {
        return left <= o.left and o.right <= right;
    }
};

struct edge
{
    int to;
    interval valid;
};

vector <vector<edge>> graph;
vector <int> visited;
int start, destination;

bool dfs(int curr, interval attempt)
{
    if (visited[curr]) return false;
    visited[curr] = 1;

    if (curr == destination) return true;

    for (edge e: graph[curr])
    {
        int neighbor = e.to;
        interval allowed = e.valid;
        if (!visited[neighbor] and allowed.contains(attempt))
        {
            bool res = dfs(neighbor, attempt);
            if (res) return true;
        }
    }
    return false;
}

int main()
{
    int n, m, b;
    cin>>n>>m>>b;
    cin>>start>>destination;
    --start;
    --destination;

    graph.resize(n);
    visited.resize(n);
    vector <int> endpoints;

    for (int i = 0; i < m; i++)
    {
        int a, b, l, r;
        cin>>a>>b>>l>>r;
        --a;
        --b;

        graph[a].push_back({b, {l, r}});
        endpoints.push_back(l);
        endpoints.push_back(r);
    }
    sort(endpoints.begin(), endpoints.end());
    endpoints.erase(unique(endpoints.begin(), endpoints.end()), endpoints.end());

    vector <interval> attempts;

    for (int i = 0; i < endpoints.size(); i++)
    {
        attempts.push_back({endpoints[i], endpoints[i]});
        if (i + 1 < endpoints.size() and endpoints[i] + 1 <= endpoints[i + 1] - 1)
        {
            attempts.push_back({endpoints[i] + 1, endpoints[i + 1] - 1});
        }
    }

    int res = 0;
    for (interval attempt: attempts)
    {
        fill(visited.begin(), visited.end(), 0);
        if (dfs(start, attempt))
        {
            res += attempt.right - attempt.left + 1;
        }
    }

    cout <<res<<'\n';

    return 0;
}
