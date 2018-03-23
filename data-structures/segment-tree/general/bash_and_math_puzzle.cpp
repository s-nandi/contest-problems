//segment tree (branching), gcd
//http://codeforces.com/problemset/problem/914/D

#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

int gcd(int a, int b)
{
    while (b > 0)
    {
        tie(a, b) = make_tuple(b, a % b);
    }
    return a;
}

struct segmentTree
{
    int sz;
    vector <int> elements;

    segmentTree(int s)
    {
        sz = s;
        elements.resize(2 * sz);
    }

    int& operator [] (int i)
    {
        return elements[i + sz];
    }

    void build()
    {
        for (int i = sz - 1; i >= 1; i--)
        {
            elements[i] = gcd(elements[i << 1], elements[i << 1 | 1]);
        }
    }

    void modify(int p, int v)
    {
        p += sz;
        elements[p] = v;

        while (p >= 2)
        {
            elements[p >> 1] = gcd(elements[p], elements[p ^ 1]);
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
                acc = gcd(acc, elements[l]);
                l++;
            }
            if (!(r & 1))
            {
                acc = gcd(acc, elements[r]);
                r--;
            }
            l >>= 1;
            r >>= 1;
        }
        return acc;
    }

    bool check(int l, int r, int k)
    {
        if (query(l, r) % k == 0)
        {
            return true;
        }
        while (l < r)
        {
            int m = (l + r) / 2;

            bool leftCheck = query(l, m) % k == 0;
            bool rightCheck = query(m + 1, r) % k == 0;

            if (!leftCheck and !rightCheck)
            {
                return false;
            }

            if (!rightCheck)
            {
                l = m + 1;
            }
            else
            {
                r = m;
            }
        }
        return true;
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
        cin>>st[i];
    }
    st.build();

    int q;
    cin>>q;

    for (int i = 0; i < q; i++)
    {
        int type;
        cin>>type;
        if (type == 1)
        {
            int l, r, x;
            cin>>l>>r>>x;
            --l; --r;
            if (st.check(l, r, x))
            {
                cout<<"YES"<<'\n';
            }
            else
            {
                cout<<"NO"<<'\n';
            }
        }
        else
        {
            int pos, y;
            cin>>pos>>y;
            --pos;
            st.modify(pos, y);
        }
    }

    return 0;
}
