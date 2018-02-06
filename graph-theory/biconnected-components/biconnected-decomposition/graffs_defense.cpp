//edge biconnected components (tarjan), combonatorics
//http://www.spoj.com/problems/GRAFFDEF/

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

#define ll long long

struct edge
{
    int to, id;
};

typedef vector<vector<edge>> graph;

struct node
{
    int depth = -1;
    int lowlink = -1;
};

bool dfs(graph &g, int curr, int prev, vector <node> &nodes, vector <bool> &bridge)
{
    if (nodes[curr].depth != -1)
    {
        nodes[prev].lowlink = min(nodes[prev].lowlink, nodes[curr].depth);
        return false;
    }

    nodes[curr].depth = prev != -1 ? nodes[prev].depth + 1 : 0;
    nodes[curr].lowlink = nodes[curr].depth;

    for (edge &e: g[curr]) if (e.to != prev)
    {
        if (dfs(g, e.to, curr, nodes, bridge))
        {
            nodes[curr].lowlink = min(nodes[curr].lowlink, nodes[e.to].lowlink);
            if (nodes[e.to].lowlink == nodes[e.to].depth)
            {
                bridge[e.id] = true;
            }
        }
    }

    return true;
}

void categorize(graph &g, int curr, vector <bool> &bridge, vector <bool> &visited, vector <vector<int>> &components)
{
    if (visited[curr]) return;
    visited[curr] = true;

    components.rbegin() -> push_back(curr);

    for (edge e: g[curr]) if (!visited[e.to] and !bridge[e.id])
    {
        categorize(g, e.to, bridge, visited, components);
    }
}

vector <vector<int>> tarjanEdgeBCC(graph &g)
{
    int n = g.size(), m = 0;
    for (int i = 0; i < n; i++)
    {
        m += g[i].size();
    }
    m /= 2;

    vector <node> nodes(n);
    vector <bool> bridge(m);

    for (int i = 0; i < n; i++) if (nodes[i].depth == -1)
    {
        dfs(g, i, -1, nodes, bridge);
    }

    vector <bool> visited(n);
    vector <vector<int>> components;

    for (int i = 0; i < n; i++) if (!visited[i])
    {
        components.push_back({});
        categorize(g, i, bridge, visited, components);
    }

    return components;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    setprecision(5);

    int n, m;
    cin>>n>>m;

    graph g(n);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin>>a>>b;
        --a; --b;
        g[a].push_back({b, i});
        g[b].push_back({a, i});
    }

    auto components = tarjanEdgeBCC(g);

    ll totalChoices = ((ll) n * (n - 1)) / 2;
    ll badChoices = 0;

    for (vector <int> &v: components)
    {
        badChoices += (ll) v.size() * (n - v.size());
    }
    badChoices /= 2;

    cout<<fixed<<(double) badChoices / totalChoices<<'\n';

    return 0;
}
