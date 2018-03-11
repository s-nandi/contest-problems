//fenwick tree (offline processing), coordinate compression, # of unique elements in range queries
//https://www.hackerrank.com/contests/university-codesprint-4/challenges/unique-art/problem

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct query
{
    int l, r, index;

    bool operator < (query o) const
    {
        if (r != o.r) return r < o.r;
        else return make_pair(l, index) < make_pair(o.l, o.index);
    }
};

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
int compress(int i)
{
    return lower_bound(compression.begin(), compression.end(), i) - compression.begin();
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin>>n;

    vector <int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin>>a[i];
        compression.push_back(a[i]);
    }
    sort(compression.begin(), compression.end());

    int q;
    cin>>q;

    vector <query> queries(q);

    for (int i = 0; i < q; i++)
    {
        int a, b;
        cin>>a>>b;
        queries[i] = {--a, --b, i};
    }
    sort(queries.begin(), queries.end());

    fenwickTree ft(n);
    vector <int> latest(n, -1), later(n, -1);
    vector <int> sol(q, -1);

    int curr = 0;
    for (int i = 0; i < n; i++)
    {
        int old = latest[compress(a[i])];
        if(old != -1)
        {
            int older = later[compress(a[i])];
            if (older != -1)
            {
                ft.modify(older, 1);
            }
            later[compress(a[i])] = old;
            ft.modify(old, -2);
        }
        latest[compress(a[i])] = i;
        ft.modify(i, 1);

        while (queries[curr].r == i)
        {
            sol[queries[curr].index] = ft.query(queries[curr].l, queries[curr].r);
            curr++;
        }
    }

    for (int i = 0; i < q; i++)
    {
        cout<<sol[i]<<'\n';
    }

    return 0;
}
