//binary search on doubles, simulation
//http://codeforces.com/contest/1011/problem/C

#include <bits/stdc++.h>

using namespace std;

const int INF = 1000000001;
const double EPS = 1e-6;

bool feasible(double fuel, double cargo, vector <int> &a, vector <int> &b)
{
    int n = a.size();
    double curr = fuel;
    for (int i = 0; i < n; i++)
    {
        int inext = (i + 1) % n;
        curr -= (curr + cargo) / a[i];
        if (curr < 0) return false;
        curr -= (curr + cargo) / b[inext];
        if (curr < 0) return false;
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    int w;
    cin>>n>>w;

    vector <int> a(n), b(n);
    for (int i = 0; i < n;i++)
    {
        cin>>a[i];
    }
    for (int i = 0; i < n;i++)
    {
        cin>>b[i];
    }

    bool isFeasible = false;
    double l = 0, r = INF;
    while (r - l > EPS)
    {
        double m = (l + r) / 2;
        if (feasible(m, w, a, b))
        {
            r = m;
            isFeasible = true;
        }
        else
        {
            l = m;
        }
    }

    if (isFeasible)
        cout<<fixed<<setprecision(9)<<l<<'\n';
    else
        cout<<-1<<'\n';

    return 0;
}
