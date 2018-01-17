//segment tree, lazy propagation, finding # of divisible numbers in a range queries, increment updates
//http://www.spoj.com/problems/MULTQ3/

#include <iostream>
#include <vector>

using namespace std;

struct segmentTree
{
    int sz, h;
    vector <vector<int>> elements;
    vector <int> lazy;

    segmentTree(int s)
    {
        sz = s;
        h = 0;
        while (1 << h < sz) h++;
        elements.resize(2 * sz, {1, 0, 0});
        lazy.resize(sz);

        for (int i = sz - 1; i >= 1; i--)
        {
            elements[i][0] = elements[i << 1][0] + elements[i << 1 | 1][0];
        }
    }

    void apply(int p, int v)
    {
        vector <int> save = elements[p];
        for (int i = 0; i < 3; i++)
        {
            elements[p][(i + v) % 3] = save[i];
        }
        if (p < sz)
        {
            lazy[p] = (lazy[p] + v) % 3;
        }
    }

    void siftDown(int p)
    {
        for (int u = h; u >= 1; u--)
        {
            int i = p >> u;
            if (lazy[i] != 0)
            {
                apply(i << 1, lazy[i]);
                apply(i << 1 | 1, lazy[i]);
                lazy[i] = 0;
            }
        }
    }

    void siftUp(int p)
    {
        while (p >= 2)
        {
            for (int i = 0; i < 3; i++)
            {
                elements[p >> 1][(i + lazy[p >> 1]) % 3] = elements[p][i] + elements[p ^ 1][i];
            }
            p >>= 1;
        }
    }

    void modify(int l, int r, int v)
    {
        l += sz;
        r += sz;
        int lSave = l, rSave = r;

        while (l <= r)
        {
            if (l & 1)
            {
                apply(l, v);
                l++;
            }
            if (!(r & 1))
            {
                apply(r, v);
                r--;
            }
            l >>= 1;
            r >>= 1;
        }

        siftUp(lSave);
        siftUp(rSave);
    }

    int query(int l, int r)
    {
        l += sz;
        r += sz;
        siftDown(l);
        siftDown(r);

        int acc = 0;
        while (l <= r)
        {
            if (l & 1)
            {
                acc += elements[l][0];
                l++;
            }
            if (!(r & 1))
            {
                acc += elements[r][0];
                r--;
            }
            l >>= 1;
            r >>= 1;
        }
        return acc;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin>>n>>m;

    segmentTree st(n);

    for (int i = 0; i < m; i++)
    {
        int type, l, r;
        cin>>type>>l>>r;

        if (type == 0)
        {
            st.modify(l, r, 1);
        }
        else
        {
            cout<<st.query(l, r)<<'\n';
        }
    }

    return 0;
}
