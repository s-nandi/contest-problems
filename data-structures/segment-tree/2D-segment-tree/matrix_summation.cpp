//2d segment tree, sum over rectangle
//http://www.spoj.com/problems/MATSUM/

#include <iostream>
#include <vector>

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

    int& operator [] (int i)
    {
        return elements[i + sz];
    }

    void modify(int p, int v)
    {
        p += sz;
        elements[p] = v;

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

struct segmentTree2D
{
    int sz1, sz2;
    vector <segmentTree> elements;

    segmentTree2D(int s1, int s2)
    {
        sz1 = s1, sz2 = s2;
        elements.resize(2 * sz1, segmentTree(sz2));
    }

    void modify(int x, int y, int v)
    {
        x += sz1;
        elements[x].modify(y, v);

        while (x >= 2)
        {
            elements[x >> 1].modify(y, elements[x][y] + elements[x ^ 1][y]);
            x >>= 1;
        }
    }

    int query(int x1, int y1, int x2, int y2)
    {
        int acc = 0;
        x1 += sz1;
        x2 += sz1;
        while (x1 <= x2)
        {
            if (x1 & 1)
            {
                acc += elements[x1].query(y1, y2);
                x1++;
            }
            if (!(x2 & 1))
            {
                acc += elements[x2].query(y1, y2);
                x2--;
            }
            x1 >>= 1;
            x2 >>= 1;
        }
        return acc;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin>>T;

    while(T--)
    {
        int n;
        cin>>n;

        segmentTree2D st(n, n);

        while(true)
        {
            string command;
            cin>>command;
            if (command == "SET")
            {
                int x, y, v;
                cin>>x>>y>>v;
                st.modify(x, y, v);
            }
            else if(command == "SUM")
            {
                int x1, y1, x2, y2;
                cin>>x1>>y1>>x2>>y2;
                cout<<st.query(x1, y1, x2, y2)<<'\n';
            }
            else break;
        }
    }
}
