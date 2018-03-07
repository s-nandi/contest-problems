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

    void modify(int p1, int p2, int v)
    {
        p1 += sz1;
        elements[p1].modify(p2, v);

        while (p1 >= 2)
        {
            elements[p1 >> 1].modify(p2, elements[p1][p2] + elements[p1 ^ 1][p2]);
            p1 >>= 1;
        }
    }

    int query(int l1, int l2, int r1, int r2)
    {
        int acc = 0;
        l1 += sz1;
        r1 += sz1;
        while (l1 <= r1)
        {
            if (l1 & 1)
            {
                acc += elements[l1].query(l2, r2);
                l1++;
            }
            if (!(r1 & 1))
            {
                acc += elements[r1].query(l2, r2);
                r1--;
            }
            l1 >>= 1;
            r1 >>= 1;
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
