// convex hull optimization
// 2018 North American Qualifier
// https://naq18.kattis.com/problems/longestlife

#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
const ld EPS = 1e-9;

bool chtQuery;
struct equation
{
    mutable ld a, b;
    mutable ld nxt = 0;
    ld slope() const {return a;}
    ld constant() const {return b;}

    ld y(ld x0) const {return a * x0 + b;}
    ld intersect(equation o) const {return ld(o.b - b) / (a - o.a);}

    bool operator < (const equation &o) const
    {
        return chtQuery ? nxt < o.nxt : slope() < o.slope();
    }
};

const ld oo = 1e20;
struct convexHullTrick : multiset<equation>
{
    bool setNext(iterator x, iterator y)
    {
        if (y == end())
        {
            x -> nxt = oo;
            return false;
        }
        if (abs(x -> slope() - y -> slope()) < EPS)
        {
            x -> nxt = x -> constant() > y -> constant() ? oo : -oo;
        }
        else
            x -> nxt = x -> intersect(*y);
        return x -> nxt >= y -> nxt;
    }

    void addEquation(equation e)
    {
        e.nxt = 0;
        auto it = insert(e), nit = next(it);
        while (setNext(it, nit))
        {
            nit = erase(nit);
        }
        if (it == begin())
            return;
        auto pit = it;
        if (setNext(--pit, it))
        {
            setNext(pit, it = erase(it));

        }
        while (pit != begin())
        {
            it = pit;
            pit = prev(pit);
            if (it != begin() and pit -> nxt >= it -> nxt)
            {
                setNext(pit, erase(it));
            }
            else break;
        }
    }

    ld getMax(ld x0)
    {
        if (empty())
            return 0;
        chtQuery = true;
        auto l = *lower_bound({0, 0, x0});
        chtQuery = false;
        return l.y(x0);
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ld n, c;
    int p;
    cin >> n >> p >> c;

    convexHullTrick cht;
    cht.addEquation({-1, n});
    for (int i = 0; i < p; i++)
    {
        ld t, x, y;
        cin >> t >> x >> y;
        auto best = cht.getMax(t) - c;
        if (best >= 0)
            cht.addEquation({-y / x, best + y / x * t});
    }
    ld sol = n;
    for (auto e: cht)
    {
        auto possible = -e.b / e.a;
        sol = max(sol, possible);
    }
    cout << fixed << setprecision(10) << sol << '\n';
}
