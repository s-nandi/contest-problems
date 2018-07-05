//fenwick tree, line sweep (maintaining points inside rectangle along sweep line)
//https://csacademy.com/contest/round-83/task/rectangle-fit/statement/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXX = 1000001;
const int MAXY = 1000001;

struct pt
{
    int x, y;

    bool operator < (const pt &o) const
    {
        return x != o.x ? x < o.x : y < o.y;
    }
};

struct fenwickTree
{
    vector <int> elements;

    fenwickTree(int s)
    {
        elements.resize(s + 1);
    }

    void modify(int i, int v)
    {
        for (i++; i < elements.size(); i += i & (-i)) elements[i] += v;
    }

    int query(int i)
    {
        int ans = 0;
        for (i++; i > 0; i -= i & (-i)) ans += elements[i];
        return ans;
    }

    int query(int l, int r) {return query(r) - query(l - 1);}
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, a;
    cin>>n>>a;

    vector <pt> points(n);

    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin>>x>>y;
        points[i] = {x, y};
    }
    sort(points.begin(), points.end());

    int sol = 0;

    fenwickTree ft(MAXY);
    int it = 0;
    for (int x = 1; x <= MAXX; x++)
    {
        while (it < points.size() and points[it].x == x)
        {
            ft.modify(points[it].y, 1);
            it++;
        }
        int possible = ft.query(0, min(MAXY, a / x));
        sol = max(sol, possible);
    }
    cout<<sol<<'\n';

    return 0;
}
