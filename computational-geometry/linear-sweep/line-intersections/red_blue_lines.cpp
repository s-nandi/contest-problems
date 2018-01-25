//counting line intersections (axis-alligned), line sweep, fenwick tree, coordinate compression
//http://www.spoj.com/problems/CS345A1/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define ll long long
#define MAXN 1000000000

struct fenwickTree
{
	vector <int> elements;

    fenwickTree(int s)
    {
        elements.resize(s + 1);
    }

	void modify(int i, int v)
	{
		for (; i < elements.size(); i += i&(-i)) elements[i] += v;
	}

	int query(int i)
	{
		int ans = 0;
		for (; i > 0; i -= i&(-i)) ans += elements[i];
		return ans;
	}
};

struct line
{
    int same, diff1, diff2;
    bool operator < (line o) const { return same != o.same ? same < o.same : make_pair(diff1, diff2) < make_pair(o.diff1, o.diff2); }
};

struct event
{
    int type, pos, lower, upper;
    bool operator < (event o) const { return pos != o.pos ? pos < o.pos : type < o.type; }
};

vector <int> sorted;
int mapping(int i)
{
    return lower_bound(sorted.begin(), sorted.end(), i) - sorted.begin() + 1;
}

ll lineIntersections(vector <line> &h, vector <line> &v)
{
    sort(h.begin(), h.end());
    sort(v.begin(), v.end());

    vector <event> events;
    fenwickTree ft(sorted.size() + 1);
    for (line segment: h)
    {
        events.push_back({0, segment.diff1, mapping(segment.same), -1});
        events.push_back({2, segment.diff2, mapping(segment.same), -1});
    }
    for (line segment: v)
    {
        events.push_back({1, segment.same, mapping(segment.diff1), mapping(segment.diff2)});
    }
    sort(events.begin(), events.end());
    ll intersections = 0;
    for (event e: events)
    {
        if (e.type == 0) ft.modify(e.lower, 1);
        else if(e.type == 2) ft.modify(e.lower, -1);
        else intersections += ft.query(e.upper) - ft.query(e.lower - 1);
    }
    return intersections;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin>>n;

    vector <line> horizontal, vertical;
    for (int i = 0; i < n; i++)
    {
        double x1, x2, y;
        cin>>x1>>x2>>y;
        x1 *= MAXN, x2 *= MAXN, y *= MAXN;
        horizontal.push_back({int(y), int(min(x1, x2)), int(max(x1, x2))});
        sorted.push_back(y);
    }
    for (int i = 0; i < n; i++)
    {
        double y1, y2, x;
        cin>>y1>>y2>>x;
        y1 *= MAXN, y2 *= MAXN, x *= MAXN;
        vertical.push_back({int(x), int(min(y1, y2)), int(max(y1, y2))});
        sorted.push_back(y1), sorted.push_back(y2);
    }
    sort(sorted.begin(), sorted.end());

    cout<<lineIntersections(horizontal, vertical)<<'\n';

    return 0;
}
