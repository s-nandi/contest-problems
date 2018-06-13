//randomization (visualize updates as height changes), 2d segment tree (range update, point query)
//http://codeforces.com/contest/869/problem/E

#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <ctime>

using namespace std;

typedef pair< pair<int, int>, pair<int, int> > rectangle;

struct node
{
    int xr = 0;

    void modify(int v)
    {
        xr ^= v;
    }

    node combine(const node &o)
    {
        node res;
        res.xr = xr ^ o.xr;
        return res;
    }
};

struct segmentTree2D
{
    int sz, sz2;
    vector <vector<node>> elements;

    segmentTree2D(int s1, int s2)
    {
        sz = s1, sz2 = s2;
        elements.resize(2 * sz, vector<node>(2 * sz2));
    }

    void modify(int x, int y1, int y2, int v)
    {
        for (y1 += sz2, y2 += sz2; y1 <= y2; ++y1 >>= 1, --y2 >>= 1)
        {
            if (y1 & 1) elements[x][y1].modify(v);
            if (!(y2 & 1)) elements[x][y2].modify(v);
        }
    }

    void modify(int x1, int y1, int x2, int y2, int v)
    {
        for (x1 += sz, x2 += sz; x1 <= x2; ++x1 >>= 1, --x2 >>= 1)
        {
            if (x1 & 1)
                modify(x1, y1, y2, v);
            if (!(x2 & 1))
                modify(x2, y1, y2, v);
        }
    }

    node subquery(int x, int y)
    {
        node acc;
        for (; y >= 1; y >>= 1)
        {
            acc = acc.combine(elements[x][y]);
        }
        return acc;
    }

    int query(int x, int y)
    {
        x += sz, y += sz2;
        node acc;
        for (; x >= 1; x >>= 1)
        {
            acc = acc.combine(subquery(x, y));
        }
        return acc.xr;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    mt19937 gen(time(0));

    int n, m, q;
    cin>>n>>m>>q;

    segmentTree2D st(n, m);
    map <rectangle, int> mapping;

    for (int i = 0; i < q; i++)
    {
        int t;
        cin>>t;

        int r1, r2, c1, c2;
        cin>>r1>>c1>>r2>>c2;
        --r1, --c1, --r2, --c2;

        if (t == 1)
        {
            int rng = gen();
            mapping[{{r1, c1}, {r2, c2}}] = rng;
            st.modify(r1, c1, r2, c2, rng);
        }
        else if(t == 2)
        {
            int rng = mapping[{{r1, c1}, {r2, c2}}];
            st.modify(r1, c1, r2, c2, rng);
        }
        else
        {
            auto v1 = st.query(r1, c1), v2 = st.query(r2, c2);
            if (v1 == v2)
                cout<<"Yes"<<'\n';
            else
                cout<<"No"<<'\n';
        }
    }

    return 0;
}
