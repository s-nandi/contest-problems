//newton's method
//http://www.spoj.com/problems/TRIGALGE/

#include <iostream>
#include <cmath>
#include <iomanip>
#include <functional>

using namespace std;

template <typename Operation, typename Operation2>
double newtonMethod(Operation &f, Operation2 &df, double x0, int M = 40, double eps = 1e-6)
{
    double x = x0;
    for (int counter = 0; counter < M; counter++)
    {
        double fx = f(x), dfx = df(x);
        if (abs(dfx) < eps or abs(fx) < eps)
        {
            return x;
        }
        x -= fx / dfx;
    }
    return 0;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin>>T;

    for (int test = 0; test < T; test++)
    {
        int a, b, c;
        cin>>a>>b>>c;

        auto f = [&](double x) -> double {return a * x + b * sin(x) - c;};
        auto df = [&](double x) -> double {return a + b * cos(x);};

        cout<<fixed<<setprecision(6)<<newtonMethod(f, df, c / a)<<'\n';
    }

    return 0;
}


