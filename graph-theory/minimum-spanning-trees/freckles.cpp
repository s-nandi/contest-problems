//minimum spanning tree (kruskal), disjoint set union
//https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=975

#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <algorithm>

using namespace std;

struct pt
{
    double x, y;
    double distance(pt o)
    {
        return sqrt((x - o.x) * (x - o.x) + (y - o.y) * (y - o.y));
    }
};

struct edge
{
    int i, j;
    double d;
    bool operator < (edge o) const
    {
        if (d != o.d) return d < o.d;
        if (i != o.i) return i < o.i;
        return j < o.j;
    }
};

struct disjointSetUnion
{
    vector <int> par;
    disjointSetUnion(int n)
    {
        par.resize(n);
        for (int i = 0; i < n; i++)
        {
            par[i] = i;
        }
    }
    int findRoot(int i)
    {
        int parent = (par[i] == i ? i : findRoot(par[i]));
        return parent;
    }
    void unionElements(int i, int j)
    {
        par[findRoot(i)] = findRoot(j);
    }
};

int main()
{
    int T;
    cin>>T;

    while(T)
    {
        int n;
        cin>>n;

        vector <pt> points(n);
        vector <edge> edges;

        for (int i = 0; i < n; i++)
        {
            double x, y;
            cin>>x>>y;
            points[i] = {x, y};
            for (int j = 0; j < i; j++)
            {
                edges.push_back({i, j, points[i].distance(points[j])});
            }
        }
        sort(edges.begin(), edges.end());

        disjointSetUnion dsu(n);
        double cost = 0.0;
        int numEdges = 0;

        for (edge e: edges)
        {
            if (dsu.findRoot(e.i) != dsu.findRoot(e.j))
            {
                dsu.unionElements(e.i, e.j);
                cost += e.d;
                numEdges++;
                if (numEdges == n - 1)
                    break;
            }
        }

        cout<<setprecision(2)<<fixed<<cost<<'\n';
        if (--T)
        {
            cout<<'\n';
        }
    }

    return 0;
}
