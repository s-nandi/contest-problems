//finding number of connected components in undirected graph
//http://codeforces.com/problemset/problem/939/D

#include <iostream>
#include <vector>

using namespace std;

struct edge
{
    int i, j;
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
    int n;
    string ss, tt;
    cin>>n>>ss>>tt;

    vector <int> s(n), t(n);

    for (int i = 0; i < n; i++)
    {
        s[i] = ss[i] - 'a';
        t[i] = tt[i] - 'a';
    }

    vector <edge> edges;

    for (int i = 0; i < n; i++)
    {
        edges.push_back({s[i], t[i]});
    }

    disjointSetUnion dsu(26);
    vector <edge> needed;

    for (edge e: edges)
    {
        if (dsu.findRoot(e.i) != dsu.findRoot(e.j))
        {
            dsu.unionElements(e.i, e.j);
            needed.push_back({e.i, e.j});
        }
    }

    cout<<needed.size()<<'\n';
    for (int i = 0; i < needed.size(); i++)
    {
        cout<<char(needed[i].i + 'a')<<" "<<char(needed[i].j +  'a')<<'\n';
    }

    return 0;
}
