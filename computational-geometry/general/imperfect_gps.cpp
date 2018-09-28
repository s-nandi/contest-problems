// simulation, point interpolation (vector geometry)
// https://open.kattis.com/problems/imperfectgps
// 2017 North American Qualifier

#include <bits/stdc++.h>

using namespace std;

typedef double ptT;
struct pt
{
    ptT x, y;

    pt operator + (const pt &o) const {return {x + o.x, y + o.y};}
    pt operator - (const pt &o) const {return {x - o.x, y - o.y};}

    pt operator * (ptT k) const {return {k * x, k * y};}

    ptT operator * (const pt &o) const {return x * o.x + y * o.y;}
    ptT norm2() {return *this * *this;}
};

pt interpolate(pt a, pt b, int ta, int tb, int t)
{
    double k = double (t - ta) / (tb - ta);
    return (b - a) * k + a;
}

double dist(vector <pt> &points)
{
    double len = 0.0;
    for (int i = 1; i < points.size(); i++)
        len += sqrt((points[i] - points[i - 1]).norm2());
    return len;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, rate;
    cin >> n >> rate;

    vector <pt> points(n);
    vector <int> times(n);

    for (int i = 0; i < n; i++)
    {
        cin >> points[i].x >> points[i].y >> times[i];
    }

    vector <pt> interpolated = {points[0]};

    int it = 0;
    for (int t = rate; t < times[n - 1]; t += rate)
    {
        while (it < times.size() and times[it] < t)
            it++;

        pt p = interpolate(points[it - 1], points[it], times[it - 1], times[it], t);
        interpolated.push_back(p);
    }
    interpolated.push_back(points.back());

    double actual_dist = dist(points);
    double gps_dist = dist(interpolated);

    cout << fixed << setprecision(11) << 100.0 * (actual_dist - gps_dist) / actual_dist << '\n';
}
