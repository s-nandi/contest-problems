// dsu (cycle detection)
// http://codeforces.com/gym/101174/attachments (problem K)
// 2016 Southwest European Regional

#include <bits/stdc++.h>

using namespace std;

struct disjointSetUnion
{
    int sz;

    vector <int> par, sizes;

    disjointSetUnion(int s)
    {
        sz = s;
        par.resize(sz), sizes.resize(sz);

        for (int i = 0; i < sz; i ++) {par[i] = i, sizes[i] = 1;}
    }

    int findRoot(int i)
    {
        return par[i] == i ? i : (par[i] = findRoot(par[i]));
    }

    void unionElements(int i, int j)
    {
        sizes[findRoot(j)] += sizes[findRoot(i)];
        par[findRoot(i)] = findRoot(j);
    }

    bool sameComponent(int i, int j){return findRoot(i) == findRoot(j);}
};

struct pt
{
    int x, y, z;

    bool operator < (const pt &o) const
    {
        return tie(x, y, z) < tie(o.x, o.y, o.z);
    }
};

int getIndex(map <pt, int> &indices, pt p)
{
    int sz = indices.size();
    if (!indices.count(p))
        return (indices[p] = sz);
    else
        return indices[p];
}

bool hasCycle(vector <pair<pt, pt>> &edges)
{
    map <pt, int> indices;
    set <pair<int, int>> ind_edges;
    for (auto e: edges)
    {
        int i1 = getIndex(indices, e.first);
        int i2 = getIndex(indices, e.second);

        if (i2 > i1)
            swap(i1, i2);
        ind_edges.insert({i1, i2});
    }

    disjointSetUnion dsu(indices.size());
    for (auto e: ind_edges) if (e.first != e.second)
    {
        if (dsu.findRoot(e.first) == dsu.findRoot(e.second))
            return true;
        dsu.unionElements(e.first, e.second);
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    vector <pair<pt, pt>> edges(n);
    for (int i = 0; i < n; i++)
    {
        int x1, y1, z1, x2, y2, z2;
        cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
        edges[i] = {{x1, y1, z1}, {x2, y2, z2}};
    }

    bool trueChain = hasCycle(edges);

    for (auto &elem: edges)
        elem.first.z = elem.second.z = 0;

    bool floorChain = hasCycle(edges);

    if (trueChain)
        cout << "True closed chains" << '\n';
    else
        cout<< "No true closed chains" << '\n';
    if (floorChain)
        cout << "Floor closed chains" << '\n';
    else
        cout << "No floor closed chains" << '\n';
}
