//finding cut vertices, string processing
//https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=251

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

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

bool dfs(graph &g, int curr, int prev, int prevEdge, vector <node> &nodes, vector <bool> &cutVertex)
{
    if (nodes[curr].depth != -1)
    {
        nodes[prev].lowlink = min(nodes[prev].lowlink, nodes[curr].depth);
        return false;
    }

    nodes[curr].depth = prev != -1 ? nodes[prev].depth + 1 : 0;
    nodes[curr].lowlink = nodes[curr].depth;

    int outEdge = 0;
    for (edge e: g[curr]) if (e.id != prevEdge)
    {
        if (dfs(g, e.to, curr, e.id, nodes, cutVertex))
        {
            nodes[curr].lowlink = min(nodes[curr].lowlink, nodes[e.to].lowlink);
            outEdge++;

            if (prev != -1 ? nodes[e.to].lowlink >= nodes[curr].depth : outEdge > 1)
            {
                cutVertex[curr] = true;
            }
        }
    }

    return true;
}

vector <int> cutVertices(graph &g)
{
    int n = g.size();
    vector <node> nodes(n);
    vector <bool> cutVertex(n);

    for (int i = 0; i < n; i++) if (nodes[i].depth == -1)
    {
        dfs(g, i, -1, -1, nodes, cutVertex);
    }

    vector <int> result;

    for (int i = 0; i < n; i++)
    {
        if (cutVertex[i])
        {
            result.push_back(i);
        }
    }

    return result;
}

int main()
{
    int n;
    while(cin >> n)
    {
        if (n == 0) break;
        cin.ignore();

        graph g(n);
        int index = 0;
        while (true)
        {
            string s;
            getline(cin, s);
            if (s[0] ==  '0') break;

            istringstream iss(s);
            int a, b;
            iss>>a; --a;
            while(iss >> b)
            {
                --b;
                g[a].push_back({b, index});
                g[b].push_back({a, index});
                index++;
            }
        }

        auto res = cutVertices(g);
        cout<<res.size()<<'\n';
    }

    return 0;
}
