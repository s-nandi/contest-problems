// ternary search
// https://open.kattis.com/problems/reconnaissance
// 2014 NAIPC

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

const double EPS = 1e-5;

struct vehicle
{
    double init, velocity;

    double position(double time)
    {
        return init + time * velocity;
    }
};

double f(vector <vehicle> &v, double t)
{
    double mn, mx;
    mn = mx = v[0].position(t);
    for (int i = 1; i < v.size(); i++)
    {
        double pos = v[i].position(t);
        mn = min(mn, pos);
        mx = max(mx, pos);
    }
    return mx - mn;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    vector <vehicle> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i].init >> a[i].velocity;
    }

    double l = 0.0, r = 1.0;
    while (f(a, r) < f(a, l))
        r *= 2.0;

    while(r - l > EPS)
    {
        double lt = l + (r - l) / 3;
        double rt = r - (r - l) / 3;
        if (f(a, lt) > f(a, rt))
            l = lt;
        else
            r = rt;
    }
    double sol = f(a, l);
    cout<<fixed<<setprecision(9)<<sol<<'\n';

    return 0;
}
