//k-th order tree, segment tree, line sweep
//http://codeforces.com/contest/754/problem/D

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

#define INF 12341234

struct event
{
    int pos;
    int type; //even -> Left, odd -> Right

    bool operator < (event o) const
    {
        if (pos == o.pos)
        {
            if (type % 2 == o.type % 2)
            {
                return type < o.type;
            }
            else
            {
                return type % 2 == 0;
            }
        }
        else
        {
            return pos < o.pos;
        }
    }
};


struct segment
{
    int l;
    int r;

    int ind;

    bool operator < (segment o) const
    {
        return r - l < o.r - o.l;
    }
};

struct kthOrder
{
    int sz;
    int sizeOfSet;
    vector <int> elem;
    map <event, int> mapping;
    vector <event> events;

    kthOrder(vector <event> &v)
    {
        sz = v.size();
        events = v;

        sizeOfSet = 0;

        elem.resize(2 * sz, 0);

        for (int i = 0; i < sz; i++)
        {
            event elem = {v[i].pos, v[i].type / 2};
            mapping[elem] = i;
        }
    }


    void update(int p, int v)
    {
        p += sz;
        elem[p] += v;

        while (p >= 2)
        {
            elem[p >> 1] = elem[p]+ elem[p ^ 1];
            p >>= 1;
        }
    }


    void addElem(event n)
    {
        if (mapping.count(n) == 1)
        {
            update(mapping[n], 1);
            sizeOfSet++;
        }
    }

    void removeElem(event n)
    {
        if (mapping.count(n) == 1)
        {
            update(mapping[n], -1);
            sizeOfSet--;
        }
    }

    int getSize()
    {
        return sizeOfSet;
    }


    int query(int l, int r)
    {
        int acc = 0;
        l += sz;
        r += sz;
        while (l <= r)
        {
            if (l & 1) //if l is odd
            {
                acc = acc + elem[l];
                l++;
            }
            if (!(r & 1)) //if r is even
            {
                acc = acc + elem[r];
                r--;
            }
            l >>= 1;
            r >>= 1;
        }

        return acc;
    }

    event findKthGreatest(int k) //k is 0-indexed, assumes set has k-elements, returns INF if k out of bounds
    {
        if (k >= getSize())
        {
            return {INF, INF};
        }
        k++;

        int left = 0;
        int right = sz - 1;

        while (left < right)
        {
            int mid = (left + right) / 2;
            int amtInLeft = query(left, mid);
            if (amtInLeft >= k)
            {
                right = mid;
            }
            else
            {
                k = k - amtInLeft;
                left = mid + 1;
            }
        }
        return events[left];
    }

    int orderOfN(event n) //find 0-indexed position in the set of n-th element in original list (returns -1 if not in set)
    {
        int p = mapping[n];
        if (elem[p + sz] == 0)
        {
            return -1;
        }
        return query(0, p - 1);
    }

};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin>>n>>k;
    vector <event> events;
    int l, r;
    map <event, event> removeEvents;
    vector <segment> segments(n);

    for (int i = 0; i < n; i++)
    {
        cin>>l>>r;
        segments[i] = {l, r, i};
        events.push_back({l, 2*i});
        events.push_back({r, 2*i + 1});
        removeEvents[{r, 2*i + 1}] = {l, 2*i};
    }
    sort(events.begin(), events.end());

    int sol = 0;
    int lbound = 0;
    int rbound = 0;

    kthOrder tree(events);

    for (event e: events)
    {
        if (e.type % 2 == 0)
        {
            event elem = {e.pos, e.type / 2};
            tree.addElem(elem);
        }
        else
        {
            if (tree.getSize() >= k)
            {
                event kthGreatest = tree.findKthGreatest(k - 1);
                if (e.pos - kthGreatest.pos + 1 > sol)
                {
                    sol = e.pos - kthGreatest.pos + 1;
                    lbound = kthGreatest.pos;
                    rbound = e.pos;
                }

            }
            event removePair = removeEvents[e];
            event elem = {removePair.pos, removePair.type / 2};

            tree.removeElem(elem);
        }
    }

    cout<<sol<<'\n';
    if (sol == 0)
    {
        for (int i = 0; i < k; i++)
        {
            cout<<i+1<<" ";
        }
        cout<<'\n';
    }

    else
    {
        vector <int> sols;
        sort(segments.begin(), segments.end());
        int printed = 0;
        for (segment s: segments)
        {
            if (s.l <= lbound and s.r >= rbound)
            {
                sols.push_back(s.ind + 1);
                printed++;
            }

            if (printed == k)
            {
                break;
            }

        }

        sort(sols.begin(), sols.end());
        for (int s: sols)
        {
            cout<<s<<" ";
        }
        cout<<'\n';

    }

    return 0;
}
