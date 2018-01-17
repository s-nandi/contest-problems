//segment trees, non-commutative operator, prefix/suffix sums, max contiguous subsegment queries
//http://www.spoj.com/problems/GSS3/

#include <iostream>
#include <vector>

using namespace std;

#define INF 1231231234
#define ll long long

struct node
{
    ll entireSum;
    ll prefixSum;
    ll suffixSum;
    ll maxSum;

    node(ll val = -INF)
    {
        entireSum = val; prefixSum = val; suffixSum = val; maxSum = val;
    }
};

node combine(node &a, node &b)
{
    node res;
    res.entireSum = a.entireSum + b.entireSum;
    res.prefixSum = max(a.entireSum + b.prefixSum, a.prefixSum);
    res.suffixSum = max(a.suffixSum + b.entireSum, b.suffixSum);
    res.maxSum = max(max(a.maxSum, b.maxSum), a.suffixSum + b.prefixSum);

    return res;
}

struct segmentTree
{
    int sz;
    vector <node> elements;

    segmentTree(int s)
    {
        sz = s;
        elements.resize(2 * sz);
    }

    void initVal(int p, ll val)
    {
        elements[p + sz] = node(val);
    }

    void build()
    {
        for (int i = sz - 1; i >= 1; i--)
        {
            elements[i] = combine(elements[i << 1], elements[i << 1 | 1]);
        }
    }

    void modify(int p, ll val)
    {
        p += sz;
        elements[p] = node(val);

        while (p >= 2)
        {
            elements[p >> 1] = combine(elements[(p >> 1) << 1], elements[(p >> 1) << 1 | 1]);
            p >>= 1;
        }
    }

    ll query(int l, int r)
    {
        node lacc;
        node racc;

        l += sz;
        r += sz;
        while (l <= r)
        {
            if (l & 1)
            {
                lacc = combine(lacc, elements[l]);
                l++;
            }
            if (!(r & 1))
            {
                racc = combine(elements[r], racc);
                r--;
            }
            l >>= 1;
            r >>= 1;
        }
        node res = combine(lacc, racc);
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
        st.initVal(i, a);
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
            --i;
            st.modify(i, v);
        }
        else
        {
            int l, r;
            cin>>l>>r;
            --l; --r;
            cout<<st.query(l, r)<<'\n';
        }
    }

    return 0;
}
