//segment tree with set, disjoint set union, manhattan distance trick
//https://www.codechef.com/problems/TELEPORT/

#include <iostream>
#include <vector>
#include <map>

using namespace std;

const int MAXX = 200005;

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

struct node : map<int, int>
{
    int findPoint(int l, int r)
    {
        auto it = lower_bound(l);
        if (it != end() and it -> first <= r)
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

    void addPoint(int x, int y, int ind)
    {
        for(x += sz; x >= 1; x >>= 1)
        {
            elements[x][y] = ind;
        }
    }

    int query(int x1, int y1, int x2, int y2)
    {
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
        x1 = min(max(0, x1), sz - 1);
        x2 = min(max(0, x2), sz - 1);
        
        for (x1 += sz, x2 += sz; x1 <= x2; ++x1 >>= 1, --x2 >>= 1)
        {
            if (x1 & 1)
            {
                int res = elements[x1].findPoint(y1, y2);
                if (res != -1) return res;
            }
            if(!(x2 & 1))
            {
                int res = elements[x2].findPoint(y1, y2);
                if (res != -1) return res;
            }
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
    segmentTree st(MAXX);

    for (int i = 0; i < q; i++)
    {
        char type;
        cin>>type;

        if (type == '+')
        {
            int ex, ey, x, y;
            cin>>ex>>ey;

            x = ex + ey, y = ex - ey;
            for (int k = 0; k < 4; k++)
            {
                int j = st.query(x, y, x + dx[k], y + dy[k]);
                if (j != -1)
                {
                    dsu.unionElements(i, j);
                }
            }
            st.addPoint(x, y, i);
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
