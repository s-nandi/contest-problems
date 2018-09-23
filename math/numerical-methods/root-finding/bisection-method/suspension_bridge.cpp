// bisection method (find zero of monotonic function), determining bracketing from closed form equation
// https://open.kattis.com/problems/suspensionbridges
// 2017 North American Qualifier

#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

const ld EPS = 1e-9;

ld f(ld a, ld s, ld d)
{
    return a * cosh(d / (2 * a)) - a - s;
}

ld binarysearch(ld s, ld d)
{
    ld l = EPS, r = 1e12;

    bool init = f(l, s, d) < 0;
    while (r - l > EPS)
    {
        ld m = (l + r) / 2.0;
        ld res = f(m, s, d);

        if ((res < 0) == init)
            l = m;
        else
            r = m;
    }
    return l;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ld d, s;
    cin >> d >> s;

    ld a = binarysearch(s, d);
    ld len = 2 * a * sinh(d / (2 * a));

    cout << fixed << setprecision(11) << len << '\n';

    return 0;
}
