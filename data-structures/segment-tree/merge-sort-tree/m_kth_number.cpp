//merge sort tree, binary search on answer, coordinate compression
//http://www.spoj.com/problems/MKTHNUM/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct node
{
    vector <int> values;

    node combine(node &o)
    {
        node res;
        res.values.resize(values.size() + o.values.size());
        merge(values.begin(), values.end(), o.values.begin(), o.values.end(), res.values.begin());
        return res;
    }
};

struct segmentTree
{
    int sz;
    vector <node> elements;

    segmentTree(int s)
    {
        sz = s;
        elements.resize(2 * sz);
    }

    node& operator [] (int i)
    {
        return elements[i + sz];
    }

    void build()
    {
        for (int i = sz - 1; i >= 1; i--)
        {
            elements[i] = elements[i << 1].combine(elements[i << 1 | 1]);
        }
    }

    int numLess(vector <int> &v, int k)
    {
        return lower_bound(v.begin(), v.end(), k) - v.begin();
    }

    int query(int l, int r, int k)
    {
        int acc = 0;
        l += sz;
        r += sz;
        while (l <= r)
        {
            if (l & 1)
            {
                acc += numLess(elements[l].values, k);
                l++;
            }
            if (!(r & 1))
            {
                acc += numLess(elements[r].values, k);
                r--;
            }
            l >>= 1;
            r >>= 1;
        }

        return acc;
    }
};

vector <int> sorted;

int mapping(int i)
{
    return lower_bound(sorted.begin(), sorted.end(), i) - sorted.begin();
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin>>n>>q;

    vector <int> a(n);
    segmentTree st(n);

    for (int i = 0; i < n; i++)
    {
        cin>>a[i];
    }

    sorted = a;
    sort(sorted.begin(), sorted.end());

    for (int i = 0; i < n; i++)
    {
        st[i] = {{mapping(a[i])}};
    }
    st.build();

    for (int i = 0; i < q; i++)
    {
        int lb, rb, k;
        cin>>lb>>rb>>k;
        --lb; --rb; --k;

        int l = 0;
        int r = n -1;

        while (l < r)
        {
            int m = (l + r + 1) / 2;

            if (st.query(lb, rb, m) <= k)
            {
                l = m;
            }
            else
            {
                r = m - 1;
            }
        }

        cout<<sorted[l]<<'\n';
    }

    return 0;
}
