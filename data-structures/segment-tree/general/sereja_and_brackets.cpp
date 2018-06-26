//segment tree (longest valid bracket expression subsequence queries), non-commutative operator
//https://codeforces.com/contest/380/problem/C

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

struct node
{
    int contained = 0, excess = 0, needed = 0;

    void init(char c)
    {
        if (c == '(') excess = 1;
        else needed = 1;
    }

    node combine(const node &o)
    {
        node res;
        res.contained = contained + o.contained + min(excess, o.needed);
        res.excess = excess - min(excess, o.needed) + o.excess;
        res.needed = needed + o.needed - min(excess, o.needed);
        return res;
    }
};

struct segmentTree
{
    int sz;
    vector <node> elements;
    string s;

    segmentTree(string &str)
    {
        s = str, sz = s.length();
        elements.resize(2 * sz);
        build();
    }

    void build()
    {
        for (int i = 0; i < sz; i++) elements[i + sz].init(s[i]);
        for (int i = sz - 1; i >= 1; i--)
        {
            elements[i] = elements[i << 1].combine(elements[i << 1 | 1]);
        }
    }

    int query(int l, int r)
    {
        node lacc, racc;
        for (l += sz, r += sz; l <= r; ++l >>= 1, --r >>= 1)
        {
            if (l & 1) lacc = lacc.combine(elements[l]);
            if (!(r & 1)) racc = elements[r].combine(racc);
        }
        return 2 * lacc.combine(racc).contained;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    string s;
    cin>>s;

    int q;
    cin>>q;

    segmentTree st(s);
    for (int i = 0; i < q; i++)
    {
        int l, r;
        cin>>l>>r;
        cout<<st.query(--l, --r)<<'\n';
    }

    return 0;
}
