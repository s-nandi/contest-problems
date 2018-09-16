// disjoint set union (# of components in graph), implicit graph
// https://open.kattis.com/problems/swaptosort
// 2018 Singapore Qualifier

#include <iostream>
#include <vector>

using namespace std;

struct disjointSetUnion
{
    int sz;
    vector <int> par;

    disjointSetUnion(int s)
    {
        sz = s;
        par.resize(sz);
        for (int i = 0; i < sz; i++) {par[i] = i;}
    }

    int findRoot(int i)
    {
        return par[i] == i ? i : (par[i] = findRoot(par[i]));
    }

    void unionElements(int i, int j)
    {
        par[findRoot(i)] = findRoot(j);
    }

    bool sameComponent(int i, int j) {return findRoot(i) == findRoot(j);} /*PS*/
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    disjointSetUnion dsu(n);

    for (int i = 0; i < k; i++)
    {
        int a, b;
        cin >> a >> b;
        --a, --b;
        dsu.unionElements(a, b);
    }
    bool feasible = true;
    for (int i = 0; i < n; i++)
    {
        int l = i, r = n - i - 1;
        if (!dsu.sameComponent(l, r))
        {
            feasible = false;
        }
    }
    if (feasible)
        cout<<"YES"<<'\n';
    else
        cout<<"NO"<<'\n';
}
