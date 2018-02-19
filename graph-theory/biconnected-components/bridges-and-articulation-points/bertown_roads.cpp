//bridge detection, converting undirected graph into strongly connected directed graph
//http://codeforces.com/contest/118/problem/E

#include <iostream>
#include <vector>

using namespace std;

struct edge
{
    int to, id;
};

typedef vector<vector<edge>> graph;
typedef pair<int, int> edgeObject;

struct node
{
    int depth = -1;
    int lowlink = -1;
};

bool hasBridge;
bool dfs(graph &g, int curr, int prev, int prevEdge, vector <node> &nodes, vector <edgeObject> &edges)
{
    if (nodes[curr].depth != -1)
    {
        nodes[prev].lowlink = min(nodes[prev].lowlink, nodes[curr].depth);
        return false;
    }

    nodes[curr].depth = prev != -1 ? nodes[prev].depth + 1 : 0;
    nodes[curr].lowlink = nodes[curr].depth;

    for (edge &e: g[curr]) if (e.id != prevEdge)
    {
        if (dfs(g, e.to, curr, e.id, nodes, edges))
        {
            nodes[curr].lowlink = min(nodes[curr].lowlink, nodes[e.to].lowlink);
            if (nodes[e.to].lowlink == nodes[e.to].depth)
            {
                hasBridge = true;
            }
            if (edges[e.id].first != curr) swap(edges[e.id].first, edges[e.id].second);
        }
        else
        {
            if (edges[e.id].first != e.to) swap(edges[e.id].first, edges[e.id].second);
        }
    }

    return true;
}

void correctEdges(graph &g, int n, vector <edgeObject> &edges)
{
    vector <node> nodes(n);

    bool hasBridge = false;
    dfs(g, 0, -1, -1, nodes, edges);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin>>n>>m;

    graph g(n);
    vector <edgeObject> edges(m);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin>>a>>b;
        --a; --b;
        g[a].push_back({b, i});
        g[b].push_back({a, i});
        edges[i] = {a, b};
    }

    correctEdges(g, n, edges);

    if (hasBridge) cout<<0<<'\n';
    else
    {
        for (const edgeObject &e: edges)
        {
            cout<<e.first + 1<<" "<<e.second + 1<<'\n';
        }
    }

    return 0;
}
