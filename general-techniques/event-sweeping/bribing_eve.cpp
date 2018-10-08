// line sweep (converting slope inequalities to events, finding min/max # of inequalities fulfilled)
// https://open.kattis.com/problems/bribingeve
// 2016 Southwest European Regional

#include <bits/stdc++.h>

using namespace std;

const int INF = 1231231234;
const double EPS = 1e-5;

struct segment
{
    double l, r;
};

struct event
{
    double pos;
    bool rmv;

    bool operator < (const event &o) const
    {
        return tie(pos, rmv) < tie(o.pos, o.rmv);
    }
};

pair <int, int> sweep(vector <event> &events)
{
    if (events.size() == 0)
        return {0, 0};

    int curr = 0;
    int mx = -INF, mn = INF;
    for (int i = 0; i < events.size();)
    {
        int add = 0, rmv = 0;
        double position = events[i].pos;
        while (i < events.size() and abs(events[i].pos - position) < EPS)
        {
            rmv += events[i].rmv;
            add += !events[i].rmv;
            i++;
        }
        if (abs(position) != INF)
        {
            mn = min(mn, curr - rmv);
            mx = max(mx, curr + add);
        }
        curr += add - rmv;
    }
    return {mx, mn};
}

pair <int, int> zerocase(vector <int> &vals, int v)
{
    int n = vals.size();
    int best = n - (upper_bound(vals.begin(), vals.end(), v) - vals.begin() - 1);
    int worst = n - (lower_bound(vals.begin(), vals.end(), v) - vals.begin());
    return {best, worst};
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, ma, mb;
    cin >> n >> ma >> mb;

    int numBelow = 0, numAbove = 0, numEqual = 0;
    vector <int> xvals = {ma}, yvals = {mb};
    vector <segment> segments;
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;

        xvals.push_back(a);
        yvals.push_back(b);

        if (a == ma and b == mb)
            numEqual++;
        else if (a >= ma and b >= mb)
            numAbove++;
        else if(a <= ma and b <= mb)
            numBelow++;
        else
        {
            double v = (double) (ma - a) / (b - mb);
            if (b - mb > 0)
                segments.push_back({-INF, v});
            else
                segments.push_back({v, INF});
        }
    }

    vector <event> events;
    for (auto seg: segments)
    {
        events.push_back({seg.l, false});
        events.push_back({seg.r, true});
    }
    sort(events.begin(), events.end());

    auto res = sweep(events);
    int best = n - (res.first + numBelow + numEqual);
    int worst = n - (res.second + numBelow);

    sort(xvals.begin(), xvals.end());
    auto res1 = zerocase(xvals, ma);
    best = min(best, res1.first);
    worst = max(worst, res1.second);

    sort(yvals.begin(), yvals.end());
    auto res2 = zerocase(yvals, mb);
    best = min(best, res2.first);
    worst = max(worst, res2.second);

    cout << best << " " << worst << '\n';
}
