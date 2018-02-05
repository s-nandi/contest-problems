//finding bridges
//http://www.spoj.com/problems/EC_P/

#include <iostream>
#include <vector>
#include <algorithm>

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

bool dfs(graph &g, int curr, int prev, int prevEdge, vector <node> &nodes, vector <bool> &bridge)
{
    if (nodes[curr].depth != -1)
    {
        nodes[prev].lowlink = min(nodes[prev].lowlink, nodes[curr].depth);
        return false;
    }

    nodes[curr].depth = prev != -1 ? nodes[prev].depth + 1 : 0;
    nodes[curr].lowlink = nodes[curr].depth;

    for (edge e: g[curr]) if (e.id != prevEdge)
    {
        if (dfs(g, e.to, curr, e.id, nodes, bridge))
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

vector <bool> cutEdges(graph &g, int numEdges)
{
    vector <node> nodes(g.size());
    vector <bool> bridge(numEdges);

    dfs(g, 0, -1, -1, nodes, bridge);

    return bridge;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin>>T;

    for (int test = 1; test <= T; test++)
    {
        int n, m;
        cin>>n>>m;

        graph g(n);
        vector <edgeObject> edges;

        for (int i = 0; i < m; i++)
        {
            int a, b;
            cin>>a>>b;
            --a; --b;
            g[a].push_back({b, i});
            g[b].push_back({a, i});
            edges.push_back({a, b});
        }

        auto bridge = cutEdges(g, m);
        vector <edgeObject> sol;

        for (int i = 0; i < m; i++) if (bridge[i])
        {
            if (edges[i].first > edges[i].second) swap(edges[i].first, edges[i].second);

            sol.push_back({edges[i].first, edges[i].second});
        }
        sort(sol.begin(), sol.end());

        cout<<"Caso #"<<test<<'\n';

        if (sol.size() == 0) cout<<"Sin bloqueos"<<'\n';
        else
        {
            cout<<sol.size()<<'\n';
            for (auto elem: sol)
            {
                cout<<elem.first + 1<<" "<<elem.second + 1<<'\n';
            }
        }
    }

    return 0;
}
