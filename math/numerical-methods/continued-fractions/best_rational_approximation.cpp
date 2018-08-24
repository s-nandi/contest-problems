// fraction class, closest rational to float (continued fractions), gcd/lcm
// https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=6314
// 2017 Greater NY Regional

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long long fracT;

ll gcd(ll a, ll b)
{
    while (b != 0)
        tie(a, b) = make_tuple(b, a % b);
    return a;
}

ll lcm(ll a, ll b)
{
    return a / gcd(a, b) * b;
}

struct fraction
{
    fracT num = 0, denom = 1;

    fraction(){}
    fraction(fracT a, fracT b, bool simplify = true)
    {
        if (b < 0)
            a = -a, b = -b;
        fracT g = simplify ? gcd(abs(a), abs(b)) : 1;
        num = a / g, denom = b / g;
    }

    fraction(long double d)
    {
        long double whole, temp;
        d = modf(d, &whole);
        fracT p = 0, q = 1;
        for (int i = 0; i < 18 and d != 0; i++, d = modf(d, &temp))
        {
            d *= 10;
            p = p * 10 + (int) d;
            q *= 10;
        }
        *this =  fraction(p, q) + fraction(whole, 1);
    }

    long double eval() const {return (long double) num / denom;}

    pair <fraction, fraction> common(const fraction &o) const
    {
        fracT l = lcm(denom, o.denom);
        return {{l / denom * num, l, false}, {l / o.denom * o.num, l, false}};
    }

    bool operator < (const fraction &o) const
    {
        fraction a, b;
        tie(a, b) = common(o);
        return a.num < b.num;
    }

    fraction operator - (const fraction &o) const
    {
        fraction a, b;
        tie(a, b) = common(o);
        return {a.num - b.num, a.denom};
    }

    fraction operator + (const fraction &o) const
    {
        fraction a, b;
        tie(a, b) = common(o);
        return {a.num + b.num, a.denom};
    }
};

fraction reciprocal(const fraction &f){return {f.denom, f.num};}
fraction operator * (const fraction &a, const fraction &b){return {a.num * b.num, a.denom * b.denom};}
fraction operator / (const fraction &a, const fraction &b){return a * reciprocal(b);}

fraction operator * (fracT k, const fraction &f){return {k * f.num, f.denom};}
fraction operator / (const fraction &f, fracT k){return {f.num, k * f.denom};}

fraction closest(const fraction &f, int maxDenom)
{
    fracT p0 = 0, q0 = 1, p1 = 1, q1 = 0, n = f.num, d = f.denom;
    while (d != 0)
    {
        fracT a = n / d, q2 = q0 + a * q1;
        if (q2 > maxDenom)
            break;
        tie(p0, q0, p1, q1, n, d) = make_tuple(p1, q1, p0 + a * p1, q2, d, n - a * d);
    }
    fracT k = (maxDenom - q0) / q1;
    fraction f1(p0 + k * p1, q0 + k * q1);
    fraction f2(p1, q1);
    return abs(f1.eval() - f.eval()) < abs(f2.eval() - f.eval()) ? f1 : f2;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin>>T;
    while (T--)
    {
        int k, m;
        double long x;
        cin>>k>>m>>x;

        fraction f(x);
        f = closest(f, m);
        cout<<k<<" "<<f.num<<"/"<<f.denom<<'\n';
    }

    return 0;
}
