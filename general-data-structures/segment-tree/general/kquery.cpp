//segment tree, find kth element in interval (offline)
//http://www.spoj.com/problems/KQUERY/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct segmentTree
{
    int sz;
    vector <int> elements;

    segmentTree(int s)
    {
        sz = s;
        elements.resize(2 * sz);
    }

    void modify(int p)
    {
        p += sz;
        elements[p]++;

        while (p >= 2)
        {
            elements[p >> 1] = elements[p] + elements[p ^ 1];
            p >>= 1;
        }
    }

    int query(int l, int r)
    {
        int acc = 0;
        l += sz;
        r += sz;
        while (l <= r)
        {
            if (l & 1)
            {
                acc += elements[l];
                l++;
            }
            if (!(r & 1))
            {
                acc += elements[r];
                r--;
            }
            l >>= 1;
            r >>= 1;
        }
        return acc;
    }
};

struct number
{
    int num;
    int index;
    bool operator < (number o) const
    {
        return make_pair(num, index) > make_pair(o.num, o.index);
    }
};

struct query
{
    int l, r;
    int k;
    int index;
    bool operator < (query o) const
    {
        if (k != o.k) return k > o.k;
        else return make_pair(l, r) < make_pair(o.l, o.r);
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin>>n;

    vector <number> a(n);

    for (int i = 0; i < n; i++)
    {
        int num;
        cin>>num;
        a[i] = {num, i};
    }
    sort(a.begin(), a.end());

    int q;
    cin>>q;

    vector <query> queries(q);

    for (int i = 0; i < q; i++)
    {
        int l, r, k;
        cin>>l>>r>>k;
        queries[i] = {--l, --r, k, i};
    }
    sort(queries.begin(), queries.end());

    vector <int> sol(q);
    segmentTree st(n);

    int currNum = 0;
    for (query qu: queries)
    {
        while (currNum < n and a[currNum].num > qu.k)
        {
            st.modify(a[currNum++].index);
        }
        sol[qu.index] = st.query(qu.l, qu.r);
    }

    for (int i: sol)
    {
        cout<<i<<'\n';
    }

    return 0;
}
