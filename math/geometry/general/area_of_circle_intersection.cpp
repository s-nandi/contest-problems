// circle-circle intersection
// https://codeforces.com/problemset/problem/600/D

#include <bits/stdc++.h>

using namespace std;

typedef long double ld;
const ld EPS = 1e-9;
const ld PI = acos(-1);

typedef ld ptT;
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

// given triangle side lengths a, b, c, returns angle between the sides with lengths a and b
ld angle_LOC(ld a, ld b, ld c)
{
    auto t = (a * a + b * b - c * c) / (2 * a * b);
    return acos(t);
}

// given triangle side lengths a and b and angle theta between them, returns area of triangle
ld area_SAS(ld a, ld b, ld theta)
{
    return a * b * sin(theta) / 2.0;
}

struct circle
{
    pt c; ptT r;
    ld area() const {return PI * r * r;}
};

ld intersectionArea(circle a, circle b)
{
    auto r1 = a.r, r2 = b.r, d = sqrt(a.c.dist2(b.c));
    if (a.c.dist2(b.c) + EPS >= (r1 + r2) * (r1 + r2))
        return 0;
    if (a.c.dist2(b.c) <= (r2 - r1) * (r2 - r1) + EPS)
        return PI * min(r1, r2) * min(r1, r2);

    auto alpha = 2 * angle_LOC(r1, d, r2);
    auto beta = 2 * angle_LOC(r2, d, r1);
    auto res = alpha * r1 * r1 / 2.0 - area_SAS(r1, r1, alpha)
             + beta * r2 * r2 / 2.0 - area_SAS(r2, r2, beta);
    return res;
}

int main()
{
    vector <circle> circles(2);
    for (int i = 0; i < 2; i++)
        cin >> circles[i].c.x >> circles[i].c.y >> circles[i].r;
    cout << fixed << setprecision(10) << intersectionArea(circles[0], circles[1]) << '\n';
}
