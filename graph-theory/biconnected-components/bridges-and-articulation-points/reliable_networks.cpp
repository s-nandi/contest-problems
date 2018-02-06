//bridge detection (edge biconnectivity), bitmasks
//http://www.spoj.com/problems/RELINETS/

#include <iostream>
#include <vector>

using namespace std;

#define INF 1231231234

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

bool dfs(graph &g, int curr, int prev, int prevEdge, vector <node> &nodes, vector <bool> &bridge, vector <bool> &visited, int &mask)
{
    if (nodes[curr].depth != -1)
    {
        nodes[prev].lowlink = min(nodes[prev].lowlink, nodes[curr].depth);
        return false;
    }

    nodes[curr].depth = prev != -1 ? nodes[prev].depth + 1 : 0;
    nodes[curr].lowlink = nodes[curr].depth;
    visited[curr] = true;

    for (edge &e: g[curr]) if (e.id != prevEdge and mask & (1 << e.id))
    {
        if (dfs(g, e.to, curr, e.id, nodes, bridge, visited, mask))
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

bool isEdgeBiconnected(graph &g, int &mask)
{
    int n = g.size(), m = 0;
    for (int i = 0; i < n; i++)
    {
        m += g[i].size();
    }
    m /= 2;

    vector <node> nodes(n);
    vector <bool> bridge(m), visited(n);

    dfs(g, 0, -1, -1, nodes, bridge, visited, mask);

    int numBridges = 0, numVisited = 0;
    for (int i = 0; i < n; i++) if (visited[i])
    {
        numVisited++;
    }
    for (int i = 0; i < m; i++) if (bridge[i])
    {
        numBridges++;
    }

    return numBridges == 0 and numVisited == n;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for (int test = 1;; test++)
    {
        int n, m;
        cin>>n>>m;
        if (n == 0 and m == 0) break;

        graph g(n);
        vector <int> costs(m);

        for (int i = 0; i < m; i++)
        {
            int a, b;
            cin>>a>>b>>costs[i];
            --a; --b;
            g[a].push_back({b, i});
            g[b].push_back({a, i});
        }

        int bestCost = INF;
        for (int mask = 0; mask < (1 << m); mask++)
        {
            int currCost = 0;
            for (int i = 0; i < m; i++)
            {
                if (mask & (1 << i))
                {
                    currCost += costs[i];
                }
            }

            if (isEdgeBiconnected(g, mask))
            {
                bestCost = min(bestCost, currCost);
            }
        }

        if (bestCost == INF)
        {
            cout<<"There is no reliable net possible for test case "<<test<<"."<<'\n';
        }
        else
        {
            cout<<"The minimal cost for test case "<<test<<" is "<<bestCost<<"."<<'\n';
        }
    }

    return 0;
}
