//line sweeping, kth order (end-only modification)
//http://codeforces.com/contest/754/problem/D

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

struct event
{
    int position;
    bool addEvent;
    int index;
    bool operator < (event o) const
    {
        if (position != o.position) return position < o.position;
        if (addEvent != o.addEvent) return addEvent;
        return index < o.index;
    }
};

struct segment
{
    int left;
    int right;
};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin>>n>>k;

    vector <event> events(2 * n);
    vector <segment> coupons(n);
    vector <int> ithAddEvent(n);

    for (int i = 0; i < n; i++)
    {
        int l, r;
        cin>>l>>r;;
        events[2 * i] = {l, true, i};
        events[2 * i + 1] = {r, false, i};
        ithAddEvent[i] = l;
        coupons[i] = {l, r};
    }

    sort(events.begin(), events.end());

    set <event> frontSet, backSet;
    int sol = 0;
    int lbound = -1, rbound = -1;

    for (event e: events)
    {
        if (e.addEvent)
        {
            if (frontSet.size() == k)
            {
                backSet.insert(e);
            }
            else
            {
                frontSet.insert(e);
            }
        }
        else
        {
            if (frontSet.size() == k)
            {
                event kthEvent = *(--frontSet.end());
                if (e.position - kthEvent.position + 1 > sol)
                {
                    sol = e.position - kthEvent.position + 1;
                    lbound = kthEvent.position;
                    rbound = e.position;
                }
            }

            event removedEvent = {ithAddEvent[e.index], true, e.index};
            if (frontSet.count(removedEvent) == 1)
            {
                frontSet.erase(removedEvent);
                if (backSet.size() > 0)
                {
                    event top = *backSet.begin();
                    frontSet.insert(top);
                    backSet.erase(top);
                }
            }
            else
            {
                backSet.erase(removedEvent);
            }
        }
    }

    cout<<sol<<'\n';

    if (sol == 0)
    {
        for (int i = 1; i <= k; i++)
        {
            cout<<i<<" ";
        }
        cout<<'\n';
    }
    else
    {
        int numPrinted = 0;
        for (int i = 0; i < n; i++)
        {
            segment s = coupons[i];

            if (s.left <= lbound and s.right >= rbound)
            {
                cout<<i + 1<<" ";
                if (++numPrinted == k) break;
            }
        }
        cout<<'\n';
    }

    return 0;
}
