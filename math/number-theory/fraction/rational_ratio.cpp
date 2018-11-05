// convert string to fraction (w/ last few digits being repeated)
// https://open.kattis.com/problems/rationalratio
// 2018 North Central NA Regional

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

template <typename T> T gcd(T a, T b)
{
    while (b != 0)
        tie(a, b) = make_pair(b, a % b);
    return a;
}

template <typename T> T stot(const string &s)
{
    T res;
    istringstream iss(s);
    iss >> res;
    return res;
}

typedef long long fracT;
struct fraction
{
    fracT num = 0, denom = 1;

    fraction() {}
    fraction(fracT a, fracT b)
    {
        fracT g = gcd(a, b);
        num = a / g, denom = b / g;
        if (denom < 0)
            num = -num, denom = -denom;
    }
    fraction(const string &s, int numRepeating = 0)
    {
        auto it = s.find('.');
        if (it == string::npos)
            *this = fraction(stot<fracT>(s), 1);
        else
        {
            auto whole = s.substr(0, it);
            auto dec = s.substr(it + 1, s.length() - it - numRepeating - 1);
            auto rep = s.substr(s.length() - numRepeating, numRepeating);

            fracT pow10 = 1, nines = 0;
            for (int i = 0; i < dec.length(); i++)
                pow10 *= 10;
            for (int i = 0; i < rep.length(); i++)
                nines = nines * 10 + 9;
            *this = (!whole.empty() ? fraction(stot<fracT>(whole), 1) : fraction()) +
                    (!dec.empty() ? fraction(stot<fracT>(dec), pow10) : fraction()) +
                    (!rep.empty() ? fraction(stot<fracT>(rep), nines * pow10) : fraction());
        }
    }

    fraction operator + (const fraction &o) const {return {num * o.denom + o.num * denom, denom * o.denom};}
};

ostream& operator << (ostream &os, const fraction &f)
{
    return os << f.num << "/" << f.denom;
}

int main()
{
    string s;
    cin >> s;

    int n;
    cin >> n;

    cout << fraction(s, n) << '\n';
}
