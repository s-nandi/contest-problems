// numerical integration (adaptive simpson), integral of polynomial rotated around x-axis, binary search to find longest interval below threshold volume
// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3893

#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

const ld EPS = 1e-9;
const ld PI = acos(-1);
const int NUM_MARKS = 8;

inline ld fast_simpson(ld fl, ld fr, ld fm, ld l, ld r) {return (fl + fr + 4.0 * fm) * (r - l) / 6.0;}

template <class Function>
ld fast_rsimpson(Function f, ld slr, ld fl, ld fr, ld fm, ld l, ld r, ld eps)
{
	ld m = (l + r) / 2.0;
	auto fml = f((l + m) / 2.0), fmr = f((m + r) / 2.0);
	auto slm = fast_simpson(fl, fm, fml, l, m), smr = fast_simpson(fm, fr, fmr, m, r);
	if(abs(slr - slm - smr) < EPS) return slm + smr;
	return fast_rsimpson(f, slm, fl, fm, fml, l, m, eps) + fast_rsimpson(f, smr, fm, fr, fmr, m, r, eps);
}

template <class Function>
ld fast_integrate(Function f, ld l, ld r, ld eps = EPS)
{
	auto m = (l + r) / 2.0;
	auto fl = f(l), fr = f(r), fm = f(m);
	return fast_rsimpson(f, fast_simpson(fl, fr, fm, l, r), fl, fr, fm, l, r, eps);
}

struct rotated_polynomial
{
    int sz;
    vector <ld> poly;

    rotated_polynomial(int s): sz(s), poly(sz) {}

    ld operator()(ld x) // y-value of polynomial at given x-coordinate
    {
        ld res = 0.0, xpow = 1.0;
        for (int i = 0; i < sz; i++)
        {
            res += poly[i] * xpow;
            xpow *= x;
        }
        return PI * res * res;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(2);

    int n;
    for (int test = 1; cin >> n; test++)
    {
        rotated_polynomial p(n + 1);
        for (int i = 0; i <= n; i++)
            cin >> p.poly[i];

        ld lo, hi, step;
        cin >> lo >> hi >> step;

        auto volume = fast_integrate(p, lo, hi);
        cout << "Case " << test << ": " << volume << '\n';

        if (volume + EPS < step)
            cout << "insufficient volume" << '\n';
        else
        {
            vector <ld> marks;
            ld prevMark = lo, prevVolume = 0.0;
            while (volume - prevVolume + EPS > step and marks.size() < NUM_MARKS)
            {
                ld l = prevMark, r = hi;
                while (r - l > EPS)
                {
                    auto m = (l + r) / 2.0;
                    auto vol = fast_integrate(p, prevMark, m);
                    if (vol > step + EPS)
                        r = m;
                    else
                        l = m;
                }
                marks.push_back(l);
                prevMark = l, prevVolume = fast_integrate(p, lo, prevMark);
            }
            for (int i = 0; i < marks.size(); i++)
            {
                cout << marks[i] - lo;
                if (i + 1 < marks.size())
                    cout << " ";
            }
            cout << '\n';
        }
    }
}
