//segment trees, non-commutative operator, prefix/suffix sums, max contiguous subsegment queries
//http://www.spoj.com/problems/GSS3/

#include <iostream>
#include <vector>

using namespace std;

#define INF 1231231234
#define ll long long

struct node
{
    ll entireSum, prefixSum, suffixSum, maxSum;

    node(ll val = -INF)
    {
        entireSum = val, prefixSum = val, suffixSum = val, maxSum = val;
    }

    node combine(node &o)
    {
        node res;
        res.entireSum = entireSum + o.entireSum;
        res.prefixSum = max(prefixSum, entireSum + o.prefixSum);
        res.suffixSum = max(suffixSum + o.entireSum, o.suffixSum);
        res.maxSum = max(max(maxSum, o.maxSum), suffixSum + o.prefixSum);
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

    void modify(int p, ll val)
    {
        p += sz;
        elements[p] = node(val);
        p >>= 1;
        while (p >= 1)
        {
            elements[p] = elements[p << 1].combine(elements[p << 1 | 1]);
            p >>= 1;
        }
    }

    ll query(int l, int r)
    {
        node lacc, racc;
        l += sz, r += sz;
        while (l <= r)
        {
            if (l & 1)
            {
                lacc = lacc.combine(elements[l]);
                l++;
            }
            if (!(r & 1))
            {
                racc = elements[r].combine(racc);
                r--;
            }
            l >>= 1;
            r >>= 1;
        }
        node res = lacc.combine(racc);
        return res.maxSum;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin>>n;

    segmentTree st(n);

    for (int i = 0; i < n; i++)
    {
        ll a;
        cin>>a;
        st[i] = node(a);
    }
    st.build();

    int m;
    cin>>m;

    for (int i = 0; i < m; i++)
    {
        int type;
        cin>>type;
        if (type == 0)
        {
            int i; ll v;
            cin>>i>>v;
            st.modify(--i, v);
        }
        else
        {
            int l, r;
            cin>>l>>r;
            cout<<st.query(--l, --r)<<'\n';
        }
    }

    return 0;
}
