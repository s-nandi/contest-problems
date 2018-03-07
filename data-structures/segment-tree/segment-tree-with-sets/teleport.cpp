//segment tree with set, disjoint set union, manhattan distance trick
//https://www.codechef.com/problems/TELEPORT/

#include <iostream>
#include <vector>
#include <set>

using namespace std;

typedef pair<int, int> ii;

const int MAXN = 200005;

struct disjointSetUnion
{
    vector <int> par;
    disjointSetUnion(int n)
    {
        par.resize(n);
        for (int i = 0; i < n; i++) par[i] = i;
    }
    int findRoot(int i)
    {
        return par[i] == i ? i : (par[i] = findRoot(par[i]));
    }
    void unionElements(int i, int j)
    {
        par[findRoot(i)] = findRoot(j);
    }
};

struct pt
{
    int x, y, index;

    pt(int _x, int _y, int i)
    {
        x = _x + _y, y = _x - _y, index = i;
    }
};

struct node : set<ii>
{
    int inRange(int a, int b)
    {
        auto it = lower_bound({a, -1});
        if (it != end() and it -> first <= b)
        {
            return it -> second;
        }
        else return -1;
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

    void add(pt p)
    {
        int x = p.x;
        x += sz;
        while (x >= 1)
        {
            elements[x].insert({p.y, p.index});
            x >>= 1;
        }
    }

    int query(int x1, int y1, int x2, int y2)
    {
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);

        x1 = min(max(0, x1), sz - 1);
        x2 = min(max(0, x2), sz - 1);

        x1 += sz, x2 += sz;
        while (x1 <= x2)
        {
            if (x1 & 1)
            {
                int res = elements[x1].inRange(y1, y2);
                if (res != -1) return res;
                x1++;
            }
            if(!(x2 & 1))
            {
                int res = elements[x2].inRange(y1, y2);
                if (res != -1) return res;
                x2--;
            }
            x1 >>= 1;
            x2 >>= 1;
        }
        return -1;
    }
};

int main()
{
    int q, r;
    cin>>q>>r;

    vector <int> dx = {-2 * r, -2 * r, 2 * r, 2 * r};
    vector <int> dy = {-2 * r, 2 * r, -2 * r, 2 * r};

    disjointSetUnion dsu(q);
    segmentTree st(MAXN);

    for (int i = 0; i < q; i++)
    {
        char type;
        cin>>type;

        if (type == '+')
        {
            int x, y;
            cin>>x>>y;
            pt p = {x, y, i};
            for (int k = 0; k < 4; k++)
            {
                int j = st.query(p.x, p.y, p.x + dx[k], p.y + dy[k]);
                if (j != -1)
                {
                    dsu.unionElements(i, j);
                }
            }
            st.add(p);
        }
        else
        {
            int a, b;
            cin>>a>>b;
            if (dsu.findRoot(--a) == dsu.findRoot(--b))
            {
                cout<<"DA"<<'\n';
            }
            else
            {
                cout<<"NET"<<'\n';
            }
        }
    }

    return 0;
}
