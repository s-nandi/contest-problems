// circumcenter w/ barycentric (checking if point is contained in circle determined by 3 other points),
// https://www.codechef.com/problems/CIRKILL

#include <bits/stdc++.h>

using namespace std;

typedef long double ld;
const long double EPS = 1e-9;

typedef long double ptT;
struct pt
{
    ptT x, y;

    pt operator + (const pt &o) const {return {x + o.x, y + o.y};}
    pt operator - (const pt &o) const {return {x - o.x, y - o.y};}
    pt operator * (ptT k) const {return {k * x, k * y};}
    pt operator / (ptT k) const {return {x / k, y / k};}

    ptT operator ^ (const pt &o) const {return x * o.y - y * o.x;}
    ptT operator * (const pt &o) const {return x * o.x + y * o.y;}

    ptT norm2() const {return *this * *this;}
    ptT dist2(const pt &o) const {return (o - *this).norm2();}
};

int orientation(const pt &o, const pt &a, const pt &b)
{
    ptT cp = (b - o) ^ (a - o);
    return cp > EPS ? 1 : (cp < -EPS ? -1 : 0);
} //cw: 1, ccw: -1, col: 0

pt toCartesian(const pt &A, const pt &B, const pt &C, double a, double b, double c)
{
    return (A * a + B * b + C * c) / (a + b + c);
}

pt circumcenter(const pt &A, const pt &B, const pt &C)
{
    auto a = B.dist2(C), b = C.dist2(A), c = A.dist2(B);
    return toCartesian(A, B, C, a * (b + c - a), b * (c + a - b), c * (a + b - c));
}

struct circle
{
    pt center; ptT r;
};

int pointInCircle(circle &c, const pt &p)
{
    auto d = sqrt(c.center.dist2(p));
    return d > c.r + EPS ? 1 : (d < c.r - EPS ? -1 : 0);
} //inside: -1, outside: 1, on: 0

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    while(T--)
    {
        int n;
        cin >> n;

        vector <pt> points(n);
        for (int i = 0; i < n; i++)
        {
            cin >> points[i].x >> points[i].y;
        }

        int num = 0;
        int denom = (n * (n - 1) * (n - 2) / (3 * 2 * 1)) * (n - 3);
        for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) for (int k = j + 1; k < n; k++)
        {
            if (orientation(points[i], points[j], points[k]) == 0)
                continue;

            pt center = circumcenter(points[i], points[j], points[k]);
            ptT radius = sqrt(points[i].dist2(center));
            circle c = {center, radius};
            for (int h = 0; h < n; h++) if (h != i and h != j and h != k)
            {
                if (pointInCircle(c, points[h]) != 1)
                    num++;
            }
        }
        auto sol = (ld) num / denom;
        cout << fixed << setprecision(10) << sol << '\n';
    }
}
