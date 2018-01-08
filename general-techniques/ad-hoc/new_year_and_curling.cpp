//basic geometry, simulation
//http://codeforces.com/problemset/problem/908/C

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

#define EPS .000001

struct pt
{
    int x;
    double y;
};

double calcY(pt placedCircle, int xVal, int r)
{
    double dx = placedCircle.x - xVal;

    if (abs(dx) >= 2 * r + EPS)
        return (double) r;
    else
        return placedCircle.y + sqrt(4 * r * r - dx * dx);
}


int main()
{
    int n;
    double r;
    cin>>n>>r;
    setprecision(9);

    vector <pt> circles;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin>>x;
        if (i == 0)
        {
            circles.push_back({x, r});
            cout<<r<<" ";
        }
        else
        {
            double maxY = -1;
            for (int j = 0; j < i; j++)
            {
                maxY = max(maxY, calcY(circles[j], x, r));
            }
            cout<<fixed<<maxY<<" ";
            circles.push_back({x, maxY});
        }
    }
    cout<<'\n';
}
