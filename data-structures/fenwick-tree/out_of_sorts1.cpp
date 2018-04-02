//fenwick tree, finding # of elements greater than k query, coordinate compression
//http://www.usaco.org/index.php?page=viewproblem2&cpid=834
//2018 USACO US Open Silver

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

struct fenwickTree
{
    vector <int> elements;

    fenwickTree(int s)
    {
        elements.resize(s + 1);
    }

    void modify(int i, int v)
    {
        for (i++; i < elements.size(); i += i & (-i)) elements[i] += v;
    }

    int query(int i)
    {
        int ans = 0;
        for (i++; i > 0; i -= i & (-i)) ans += elements[i];
        return ans;
    }

    int query(int l, int r) {return query(r) - query(l - 1);}
};

vector <int> compression;
int compressed(int i)
{
    return lower_bound(compression.begin(), compression.end(), i) - compression.begin();
}

int main()
{
    //freopen("sort.in","r",stdin);
    //freopen("sort.out","w",stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin>>n;
    vector <int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin>>a[i];
    }
    compression = a;
    sort(compression.begin(), compression.end());

    fenwickTree ft(n);

    int sol = 0;
    for (int i = 0; i < n; i++)
    {
        int ind = compressed(a[i]);
        int greaterThan = ft.query(ind + 1, n - 1);
        ft.modify(ind, 1);
        sol = max(sol, greaterThan);
    }
    cout<<sol + 1<<'\n';

    return 0;
}
