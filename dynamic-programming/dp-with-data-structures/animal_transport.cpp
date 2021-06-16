//dynamic programming with segment tree, lazy propagation, range maximum query, range increment update, binary search
//https://www.hackerrank.com/contests/world-codesprint-12/challenges/animal-transport/problem

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define INF 1231231234

struct segment
{
    int type;
    int start;
    int destination;
    bool operator < (segment o) const
    {
        return destination < o.destination;
    }
};

struct segmentTree
{
    int sz, h = 0;
    vector <int> elements, lazy;

    segmentTree(int s)
    {
        sz = s;
        while (1 << h < sz) h++;
        elements.resize(2 * sz), lazy.resize(sz);
    }

    void apply(int p, int v)
    {
        elements[p] += v;
        if (p < sz)
        {
            lazy[p] += v;
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
        p >>= 1;
        while (p >= 1)
        {
            elements[p] = max(elements[p << 1], elements[p << 1 | 1]) + lazy[p];
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
        siftUp(lSave), siftUp(rSave);
    }

    int query(int l, int r)
    {
        l += sz;
        r += sz;
        siftDown(l), siftDown(r);
        int acc = -INF;
        while (l <= r)
        {
            if (l & 1)
            {
                acc = max(acc, elements[l]);
                l++;
            }
            if (!(r & 1))
            {
                acc = max(acc, elements[r]);
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
    int tests;
    cin>>tests;

    while (tests--)
    {
        int n, m;
        cin>>m>>n;

        vector <segment> segments(n);
        for (int i = 0; i < n; i++)
        {
            char c;
            cin>>c;
            segments[i].type = (c == 'D' or c == 'M') ? 0 : 1;
        }
        for (int i = 0; i < n; i++)
        {
            cin>>segments[i].start;
        }
        for (int i = 0; i < n; i++)
        {
            cin>>segments[i].destination;
            --segments[i].start; --segments[i].destination;
        }
        sort(segments.begin(), segments.end());

        vector <segmentTree> st(2, segmentTree(m));
        vector <int> dp(m);

        int curr = 0;
        for (int i = 0; i < m; i++)
        {
            while (segments[curr].destination == i and curr < segments.size())
            {
                segment s = segments[curr++];
                if (s.destination < s.start) continue;
                st[s.type].modify(0, s.start, 1);
            }
            dp[i] = max(st[0].query(0, i), st[1].query(0, i));
            st[0].modify(i, i, dp[i]);
            st[1].modify(i, i, dp[i]);
        }

        for (int i = 1; i <= n; i++)
        {
            int pos = lower_bound(dp.begin(), dp.end(), i) - dp.begin() + 1;
            if (pos <= m)
            {
                cout<<pos<<" ";
            }
            else
            {
                cout<<-1<<" ";
            }
        }
        cout<<'\n';
    }

    return 0;
}
