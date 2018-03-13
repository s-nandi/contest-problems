//lowest common ancestor (binary lift)
//http://www.spoj.com/problems/LCA/

#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> graph;

struct binaryLift
{
    int sz, h;
    graph g;
    vector <vector<int>> table;

    vector <int> depths;

    binaryLift(graph &gr)
    {
        g = gr, sz = g.size(), h = 0, calcHeight(), table.resize(sz, vector<int>(h, -1));
        depths.resize(sz);
        build(0);
    }
    void calcHeight(){while (1 << h < sz) h++;}

    void build(int curr, int depth = 0)
    {
        depths[curr] = depth;
        for (int i = 1; i < h; i++) if (table[curr][i - 1] != -1)
        {
            table[curr][i] = table[table[curr][i - 1]][i - 1];
        }
        for (int neighbor: g[curr]) if (neighbor != table[curr][0])
        {
            table[neighbor][0] = curr;
            build(neighbor, depth + 1);
        }
    }

    int lowestCommonAncestor(int l, int r)
    {
        if (depths[l] > depths[r]) swap(l, r);
        for (int i = h - 1; i >= 0; i--)
        {
            if ((1 << i) & (depths[r] - depths[l]))
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

    int T;
    cin>>T;
    for (int test = 1; test <= T; test++)
    {
        int n;
        cin>>n;

        graph g(n);

        for (int a = 0; a < n; a++)
        {
            int m;
            cin>>m;
            for (int j = 0; j < m; j++)
            {
                int b;
                cin>>b;
                --b;
                g[a].push_back(b);
                g[b].push_back(a);
            }
        }
        binaryLift bl(g);

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
