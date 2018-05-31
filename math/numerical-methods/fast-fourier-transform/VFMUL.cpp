//fast fourier transform (multiplying big integers)
//http://www.spoj.com/problems/VFMUL/

#include <iostream>
#include <vector>
#include <cmath>
#include <complex>

using namespace std;

typedef complex<double> cpx;
typedef vector<int> polynomial;
typedef vector<cpx> cpxPolynomial;

const double PI = 3.14159265;

cpxPolynomial fft(cpxPolynomial &p, bool inv)
{
    int sz = p.size(), hsz = sz / 2;
    if (sz == 1) return p;

    cpxPolynomial evens(hsz), odds(hsz);
    for (int i = 0; i < sz; i += 2)
    {
        evens[i >> 1] = p[i], odds[i >> 1] = p[i + 1];
    }
    cpxPolynomial e = fft(evens, inv), o = fft(odds, inv);

    double theta = 2 * PI / sz * (inv ? -1 : 1);
    cpx w = {1, 0}, wn = {cos(theta), sin(theta)};
    cpxPolynomial res(sz);
    for (int i = 0; i < hsz; i++)
    {
        res[i] = e[i] + w * o[i];
        res[i + hsz] = e[i] - w * o[i];
        if (inv) res[i] /= 2, res[i + hsz] /= 2;
        w *= wn;
    }
    return res;
}

cpxPolynomial operator * (cpxPolynomial &a, cpxPolynomial &b)
{
    cpxPolynomial res(a.size());
    for (int i = 0; i < a.size(); i++)
    {
        res[i] = a[i] * b[i];
    }
    return res;
}

polynomial operator * (polynomial &a, polynomial &b)
{
    int sz = 1;
    while (sz < a.size() + b.size()) sz <<= 1;

    cpxPolynomial cpa(a.begin(), a.end()), cpb(b.begin(), b.end());
    cpa.resize(sz), cpb.resize(sz);

    auto convA = fft(cpa, false), convB = fft(cpb, false), convC = convA * convB;
    convC = fft(convC, true);

    polynomial c(sz);
    for (int i = 0; i < sz; i++)
    {
        c[i] = round(convC[i].real());
    }
    return c;
}

void fix(polynomial &p)
{
    for (int i = 0; i < p.size() - 1; i++)
    {
        p[i + 1] += p[i] / 10;
        p[i] %= 10;
    }
    while(p.size() > 1 and p.rbegin()[0] == 0) p.pop_back();
}

string toString(polynomial &p, bool isNumber)
{
    if (isNumber) fix(p);
    string s = "";
    for (int i = p.size() - 1; i >= 0; i--)
    {
        s += '0' + p[i];
    }
    return s;
}

polynomial toPolynomial(string &s)
{
    polynomial p(s.length());
    for (int i = s.length() - 1; i >= 0; i--)
    {
        p[s.length() - i - 1] = s[i] - '0';
    }
    return p;
}

int main()
{
    ios_base::sync_with_stdio(NULL);
    cin.tie(0);

    int n;
    cin>>n;

    for (int i = 0; i < n; i++)
    {
        string a, b;
        cin>>a>>b;
        polynomial pa = toPolynomial(a), pb = toPolynomial(b), pc = pa * pb;
        cout<<toString(pc, true)<<'\n';
    }

    return 0;
}
