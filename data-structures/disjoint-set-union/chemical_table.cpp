// disjoint set union (finding # of components), implicit connected components (connecting opposite corners fills all 4 corners of grid)
// http://codeforces.com/contest/1013/problem/D

#include <bits/stdc++.h>

using namespace std;

struct disjointSetUnion
{
    int sz;
    vector <int> par;

    disjointSetUnion(int s)
    {
        sz = s;
        par.resize(sz);
        for (int i = 0; i < sz; i++)
            par[i] = i;
    }

    int findRoot(int i)
    {
        return par[i] == i ? i : par[i] = findRoot(par[i]);
    }

    void unionElements(int i, int j)
    {
        par[findRoot(i)] = findRoot(j);
    }

    bool sameComponent(int i, int j) {return findRoot(i) == findRoot(j);}

    int numComponents()
    {
        int res = 0;
        for (int i = 0; i < sz; i++)
        {
            if (i == findRoot(i))
                res++;
        }
        return res;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m, q;
    cin>>n>>m>>q;

    disjointSetUnion dsu_col(m);
    vector <int> hasRow(n, -1);
    int missingRow = n;
    for (int i = 0; i < q; i++)
    {
        int x, y;
        cin>>x>>y;
        --x, --y;

        if (hasRow[x] == -1)
        {
            hasRow[x] = y;
            missingRow--;
        }
        else
            dsu_col.unionElements(y, hasRow[x]);
    }

    int sol = dsu_col.numComponents() - 1 + missingRow;
    cout<<sol<<'\n';

    return 0;
}
