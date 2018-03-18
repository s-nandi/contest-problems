//minimum spanning tree
//https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=975

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

typedef double edgeT;

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
    edgeT d;
    bool operator < (const edge &o) const {return d < o.d;}
};

struct disjointSetUnion
{
    int sz;
    vector <int> par;

    disjointSetUnion(int s)
    {
        sz = s;
        par.resize(sz);
        for (int i = 0; i < sz; i++) par[i] = i;
    }

    int findRoot(int i)
    {
        return par[i] == i ? i : (par[i] = findRoot(par[i]));
    }

    void unionElements(int i, int j)
    {
        par[findRoot(i)] = findRoot(j);
    }

    bool sameComponent(int i, int j) {return findRoot(i) == findRoot(j);}
};

edgeT kruskal(vector <edge> &edges, int n)
{
    sort(edges.begin(), edges.end());
    disjointSetUnion dsu(n);
    edgeT cost = 0;
    int numEdges = 0;
    for (const edge &e: edges) if (!dsu.sameComponent(e.i, e.j))
    {
        dsu.unionElements(e.i, e.j);
        cost += e.d;
        if (++numEdges == n - 1) break;
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
        cout<<setprecision(2)<<fixed<<kruskal(edges, n)<<'\n';
        if (T) cout<<'\n';
    }

    return 0;
}
