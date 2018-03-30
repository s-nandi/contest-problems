//two pointer method
//http://codeforces.com/problemset/problem/957/C

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

const double EPS = 1e-9;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, u;
    cin>>n>>u;

    vector <int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin>>a[i];
    }

    double sol = 0.0;
    for (int l = 0, r = 0; l < n; l++)
    {
        while (r + 1 < n and a[l] >= a[r + 1] - u) r++;
        if (r - l >= 2)
        {
            sol = max(sol, double(a[r] - a[l + 1]) / (a[r] - a[l]));
        }
    }
    if (sol > EPS) cout<<fixed<<setprecision(11)<<sol<<'\n';
    else cout<<-1<<'\n';

    return 0;
}
