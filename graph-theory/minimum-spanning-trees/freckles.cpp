#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>

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
        else return make_pair(i, j) < make_pair(o.i, o.j);
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

double kruskal(vector <edge> &edges, int n)
{
    sort(edges.begin(), edges.end());

    disjointSetUnion dsu(n);
    double cost = 0.0;
    int numEdges = 0;

    for (const edge &e: edges)
    {
        if (dsu.findRoot(e.i) != dsu.findRoot(e.j))
        {
            dsu.unionElements(e.i, e.j);
            cost += e.d;
            if (++numEdges == n - 1) break;
        }
    }

    return cost;
}

int main()
{
    int T;
    cin>>T;

    while(T--)
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

        double cost = kruskal(edges, n);

        cout<<setprecision(2)<<fixed<<cost<<'\n';
        if (T) cout<<'\n';
    }

    return 0;
}
