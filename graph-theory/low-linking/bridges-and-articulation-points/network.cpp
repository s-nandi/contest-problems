//articulation points (tarjan), string processing
//https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=251

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

typedef vector<vector<int>> graph;

struct node
{
    int depth = -1;
    int lowlink = -1;
};

bool dfs(graph &g, int curr, int prev, vector <node> &nodes, vector <bool> &cutVertex)
{
    if (nodes[curr].depth != -1)
    {
        nodes[prev].lowlink = min(nodes[prev].lowlink, nodes[curr].depth);
        return false;
    }

    nodes[curr].depth = prev != -1 ? nodes[prev].depth + 1 : 0;
    nodes[curr].lowlink = nodes[curr].depth;

    int outEdge = 0;
    for (int neighbor: g[curr]) if (neighbor != prev)
    {
        if (dfs(g, neighbor, curr, nodes, cutVertex))
        {
            nodes[curr].lowlink = min(nodes[curr].lowlink, nodes[neighbor].lowlink);
            outEdge++;

            if (prev != -1 ? nodes[neighbor].lowlink >= nodes[curr].depth : outEdge > 1)
            {
                cutVertex[curr] = true;
            }
        }
    }

    return true;
}

vector <int> cutVertices(graph &g)
{
    vector <node> nodes(g.size());
    vector <bool> cutVertex(g.size());

    dfs(g, 0, -1, nodes, cutVertex);

    vector <int> result;

    for (int i = 0; i < g.size(); i++)
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
        while (true)
        {
            string s;
            getline(cin, s);
            if (s[0] ==  '0') break;

            istringstream iss(s);
            int i, j;
            iss>>i; --i;
            while(iss >> j)
            {
                --j;
                g[i].push_back(j);
                g[j].push_back(i);
            }
        }

        auto res = cutVertices(g);
        cout<<res.size()<<'\n';
    }

    return 0;
}
