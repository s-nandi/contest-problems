//lowest common ancestor (binary lift)
//http://www.spoj.com/problems/LCA/

#include <iostream>
#include <vector>

using namespace std;

vector <vector<int>> graph;

struct binaryLift
{
    int sz, h = 0;
    vector <vector<int>> table;
    vector <int> depth;

    binaryLift(vector <vector<int>> &graph)
    {
        sz = graph.size();
        while (1 << h < sz) h++;
        table.resize(sz, vector<int>(h, -1)), depth.resize(sz);

        buildLift(graph, 0);
    }

    void buildLift(vector <vector<int>> &graph, int curr)
    {
        for (int i = 1; i < h; i++)
        {
            table[curr][i] = table[curr][i - 1] != -1 ? table[table[curr][i - 1]][i - 1] : -1;
        }
        for (int i: graph[curr]) if (i != table[curr][0])
        {
            table[i][0] = curr;
            depth[i] = depth[curr] + 1;
            buildLift(graph, i);
        }
    }

    int lowestCommonAncestor(int l, int r)
    {
        if (depth[l] > depth[r]) swap(l, r);
        int diff = depth[r] - depth[l];

        for (int i = h - 1; i >= 0; i--)
        {
            if (1 << i & diff)
            {
                r = table[r][i];
            }
        }
        if (l == r) return l;

        for (int i = h - 1; i >= 0; i--)
        {
            if (table[l][i] != table[r][i])
            {
                l = table[l][i], r = table[r][i];
            }
        }
        return table[l][0];
    }
};


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tests;
    cin>>tests;
    for (int test = 1; test <= tests; test++)
    {
        int n;
        cin>>n;

        graph.clear(); graph.resize(n);

        for (int a = 0; a < n; a++)
        {
            int m;
            cin>>m;
            for (int j = 0; j < m; j++)
            {
                int b;
                cin>>b;
                --b;
                graph[a].push_back(b);
                graph[b].push_back(a);
            }
        }
        binaryLift bl(graph);

        cout<<"Case "<<test<<":"<<'\n';

        int q;
        cin>>q;

        for (int i = 0; i < q; i++)
        {
            int a, b;
            cin>>a>>b;
            cout<<bl.lowestCommonAncestor(--a, --b) + 1<<'\n';
        }
    }

    return 0;
}
