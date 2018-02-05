//edge biconnected components (tarjan), combonatorics
//http://www.spoj.com/problems/GRAFFDEF/

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

#define ll long long

struct edge
{
    int to;
    bool isBridge;
};

typedef vector<vector<edge>> graph;

struct node
{
    int depth = -1;
    int lowlink = -1;
};

bool dfs(graph &g, int curr, int prev, vector <node> &nodes)
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
        if (dfs(g, e.to, curr, nodes))
        {
            nodes[curr].lowlink = min(nodes[curr].lowlink, nodes[e.to].lowlink);
            if (nodes[e.to].lowlink == nodes[e.to].depth)
            {
                e.isBridge = true;
            }
        }
    }

    return true;
}

void categorize(graph &g, int curr, vector <int> &visited, vector <vector<int>> &components)
{
    if (visited[curr]) return;
    visited[curr] = 1;

    components.rbegin() -> push_back(curr);

    for (edge e: g[curr]) if (!visited[e.to] and !e.isBridge)
    {
        categorize(g, e.to, visited, components);
    }
}

vector <vector<int>> tarjanEdgeBCC(graph &g)
{
    vector <node> nodes(g.size());

    for (int i = 0; i < g.size(); i++) if (nodes[i].depth == -1)
    {
        dfs(g, i, -1, nodes);
    }

    vector <int> visited(g.size());
    vector <vector<int>> components;

    for (int i = 0; i < g.size(); i++) if (!visited[i])
    {
        components.push_back({});
        categorize(g, i, visited, components);
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
        g[a].push_back({b, false});
        g[b].push_back({a, false});
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
