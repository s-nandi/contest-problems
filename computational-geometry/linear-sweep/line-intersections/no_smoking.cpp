// bentley-ottman (intersection detection)
// http://acm.timus.ru/problem.aspx?space=1&num=1469

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;
typedef long double ld;

const ld EPS = 1E-9;

typedef ld ptT;
struct pt
{
    ptT x, y;

    pt operator + (const pt &o) const {return {x + o.x, y + o.y};}
    pt operator - (const pt &o) const {return {x - o.x, y - o.y};}
    pt operator * (ptT k) const {return {k * x, k * y};}

    ptT operator ^ (const pt &o) const {return x * o.y - y * o.x;}
};

int orientation(const pt &o, const pt &a, const pt &b)
{
    ptT cp = (b - o) ^ (a - o);
    return cp > EPS ? 1 : (cp < -EPS ? -1 : 0);
}

struct line
{
    pt a, b, ab;
    int index;

    line(){}
    line(pt p, pt q, int i) : a(p), b(q), ab(q - p), index(i) {}

    line fix() const
    {
        if (tie(a.x, a.y) > tie(b.x, b.y))
            return line(b, a, index);
        else
            return *this;
    }

    ptT y(ptT x) const
    {
        if (abs(ab.x) < EPS)
            return a.y;
        auto scale = (x - a.x) / ab.x;
        return (a + ab * scale).y;
    }

    bool operator < (const line &o) const
    {
        double x = max(a.x, o.a.x);
        return y(x) < o.y(x) - EPS;
    }
};

bool intersect1d(ptT l1, ptT r1, ptT l2, ptT r2)
{
    if (l1 > r1)
        swap(l1, r1);
    if (l2 > r2)
        swap(l2, r2);
    return max(l1, l2) <= min(r1, r2) + EPS;
}

bool intersectionSegment(const line& m, const line& n)
{
    return intersect1d(m.a.x, m.b.x, n.a.x, n.b.x) and
           intersect1d(m.a.y, m.b.y, n.a.y, n.b.y) and
           orientation(m.a, m.b, n.a) * orientation(m.a, m.b, n.b) <= 0 and
           orientation(n.a, n.b, m.a) * orientation(n.a, n.b, m.b) <= 0;
}

struct event
{
    ptT x;
    int type, index;

    bool operator > (const event &o) const
    {
        if (abs(x - o.x) > EPS)
            return x > o.x;
        return type < o.type;
    }
};

ii bentleyOttman(const vector<line> &v)
{
    vector <line> lines;
    priority_queue <event, vector<event>, greater<event>> pq;
    for (const line &l: v)
    {
        auto f = l.fix();
        lines.push_back(f);
        pq.push({f.a.x, 1, l.index});
        pq.push({f.b.x, -1, l.index});
    }
    set <line> sweep;
    map <int, set<line>::iterator> byIndex;
    while (!pq.empty())
    {
        auto curr = pq.top();
        pq.pop();

        int ind = curr.index;
        if (curr.type == 1)
        {
            auto nxt = sweep.lower_bound(lines[ind]);
            auto prv = nxt != sweep.begin() ? prev(nxt) : sweep.end();
            if (nxt != sweep.end() and intersectionSegment(*nxt, lines[ind]))
                return {nxt -> index, ind};
            if (prv != sweep.end() and intersectionSegment(*prv, lines[ind]))
                return {prv -> index, ind};
            byIndex[ind] = sweep.insert(nxt, lines[ind]);
        }
        else
        {
            auto it = byIndex[ind], nxt = next(it);
            auto prv = it != sweep.begin() ? prev(it) : sweep.end();
            if (nxt != sweep.end() and prv != sweep.end() and intersectionSegment(*nxt, *prv))
                return {prv -> index, nxt -> index};
            sweep.erase(prev(nxt));
        }
    }
    return {-1, -1};
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    vector <line> lines(n);
    for (int i = 0; i < n; i++)
    {
        pt a, b;
        cin >> a.x >> a.y >> b.x >> b.y;
        lines[i] = {a, b, i};
    }

    auto res = bentleyOttman(lines);
    if (res.first != -1)
    {
        cout << "YES" << '\n';
        cout << res.first + 1 << " " << res.second + 1 << '\n';
    }
    else
        cout << "NO" << '\n';
}
