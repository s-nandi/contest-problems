//bridges (tarjan)
//http://www.spoj.com/problems/EC_P/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<vector<int>> graph;

struct node
{
    int depth = -1;
    int lowlink = -1;
};

int timer;
bool dfs(graph &g, int curr, int prev, vector <node> &nodes, vector <pair<int, int>> &bridges)
{
    if (nodes[curr].depth != -1)
    {
        nodes[prev].lowlink = min(nodes[prev].lowlink, nodes[curr].depth);
        return false;
    }

    nodes[curr].depth = prev != -1 ? nodes[prev].depth + 1 : 0;
    nodes[curr].lowlink = nodes[curr].depth;

    for (int neighbor: g[curr]) if (neighbor != prev)
    {
        if (dfs(g, neighbor, curr, nodes, bridges))
        {
            nodes[curr].lowlink = min(nodes[curr].lowlink, nodes[neighbor].lowlink);
            if (nodes[neighbor].lowlink == nodes[neighbor].depth)
            {
                bridges.push_back({min(curr, neighbor), max(curr, neighbor)});
            }
        }
    }

    return true;
}

vector <pair<int, int>> cutEdges(graph &g)
{
    vector <node> nodes(g.size());
    vector <pair<int, int>> bridges;
    timer = 0;

    dfs(g, 0, -1, nodes, bridges);

    return bridges;
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

        for (int i = 0; i < m; i++)
        {
            int a, b;
            cin>>a>>b;
            --a; --b;
            g[a].push_back(b);
            g[b].push_back(a);
        }

        auto bridges = cutEdges(g);
        sort(bridges.begin(), bridges.end());

        cout<<"Caso #"<<test<<'\n';

        if (bridges.size() == 0) cout<<"Sin bloqueos"<<'\n';
        else
        {
            cout<<bridges.size()<<'\n';
            for (auto elem: bridges)
            {
                cout<<elem.first + 1<<" "<<elem.second + 1<<'\n';
            }
        }
    }

    return 0;
}
