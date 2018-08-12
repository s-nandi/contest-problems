// 2d point and line (segment, ray) geometry
// https://codeforces.com/gym/100168

#include <iostream>
#include <vector>
#include <tuple>
#include <cmath>
#include <iomanip>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
const double EPS = 1e-9;
const double PI = 3.1415926;

typedef long double ptT;
struct pt
{
    ptT x, y;

    bool operator < (const pt &o) const {return make_pair(y, x) < make_pair(o.y, o.x);}
    bool operator == (const pt &o) const {return abs(x - o.x) < EPS and abs(y - o.y) < EPS;}

    pt operator + (const pt &o) const {return {x + o.x, y + o.y};}
    pt operator - (const pt &o) const {return {x - o.x, y - o.y};}
    pt operator * (ptT k) const {return {k * x, k * y};}
    pt operator / (ptT k) const {return {x / k, y / k};}

    ptT operator ^ (const pt &o) const {return x * o.y - y * o.x;}
    ptT operator * (const pt &o) const {return x * o.x + y * o.y;}

    pt rotateCw(double theta) {return {cos(theta) * x + sin(theta) * y, - sin(theta) * x + cos(theta) * y};} // Caution!! Only use with doubles
    pt rotateCcw(double theta) {return {cos(theta) * x - sin(theta) * y, sin(theta) * x + cos(theta) * y};} // Same as above
    pt perpCcw() const {return {-y, x};}
    pt perpCw() const {return {y, -x};}

    ptT norm2() const {return *this * *this;}
    ptT dist2(const pt &o) const {return (*this - o).norm2();}
    pt normalize() const {return *this / sqrt(norm2());} // Caution!! Only use with doubles
};
std::istream& operator >> (istream& is, pt &p) {return is >> p.x >> p.y;}
std::ostream& operator << (ostream& os, const pt &p) {return os << p.x << " " << p.y;}

pt operator * (ptT k, const pt &p){return {k * p.x, k * p.y};}

double angleCcw(const pt &a, const pt &b){return atan2(a ^ b, a * b);}
double angleCcw(const pt &o, const pt &a, const pt &b){return angleCcw(a - o, b - o);}

ptT triArea(const pt &o, const pt &a, const pt &b){return (b - o) ^ (a - o);}
int orientation(const pt &o, const pt &a, const pt &b)
{
    ptT cp = (b - o) ^ (a - o);
    return cp > EPS ? 1 : (cp < -EPS ? -1 : 0); //PS: change between > 0 or > EPS and < 0 or < -EPS for ints/doubles
} //cw: 1, ccw: -1, col: 0

typedef vector <pt> polygon;
int prev(int i, int n, int st = 1){return (i - st + n) % n;}
int next(int i, int n, int st = 1){return (i + st) % n;};

vector <ptT> getShoelaces(polygon &poly)
{
    int sz = poly.size();
    vector <ptT> shoelace(sz + 1);
    for (int i = 0; i < sz; i++)
        shoelace[i + 1] = shoelace[i] + (poly[i] ^ poly[next(i, sz)]); //Caution !! returns doubled/oriented area -> cw: negative
    return shoelace;
}

ptT polygonArea(polygon &poly)
{
    int sz = poly.size();
    ptT sol = 0;
    for (int i = 0; i < sz; i++)
        sol += poly[i] ^ poly[next(i, sz)]; //Caution !! returns doubled/oriented area -> cw: negative
    return sol;
}

struct line
{
    pt a, b, ab;

    // PS: can remove bool if lines are always made using the same form
    line(pt p = pt(), pt q = pt(), bool ptSlope = false)
    {
        a = p;
        if (ptSlope)
            ab = q, b = p + q;
        else
            ab = q - p, b = q;
    }

    bool onLine(const pt &p) {return abs(ab ^ (p - a)) < EPS;}
    bool onRay(const pt &p)
    {
        if (!onLine(p)) return false;
        return ab * (p - a) >= 0;
    }
    bool onSegment(const pt &p) // PS: Change to > 0 and < ab.norm() if need strictly in segment
    {
        if (!onLine(p)) return false;
        ptT dot = ab * (p - a);
        return dot >= 0 and dot <= ab.norm2();
    }

    ptT distLine(const pt &p) {return abs((p - a) ^ ab) / sqrt(ab.norm2());}
    ptT distRay(const pt &p)
    {
        if ((p - a) * ab <= 0) return sqrt(p.dist2(a));
        return distLine(p);
    }
    ptT distSegment(const pt &p)
    {
        if ((p - a) * ab <= 0) return sqrt(p.dist2(a));
        if ((p - b) * ab >= 0) return sqrt(p.dist2(b));
        return distLine(p);
    }

    pt projection(const pt &p) {return a + ab * ((p - a) * ab) / ab.norm2();}
    pt reflection(const pt &p) {return 2 * projection(p) - p;}
    pt closestSegment(const pt &p)
    {
        if ((p - a) * ab <= 0) return a;
        if ((p - b) * ab >= 0) return b;
        return projection(p);
    }
};

bool intersectionSegment(const line &m, const line &n)
{
    if (orientation(m.a, m.b, n.a) == orientation(m.a, m.b, n.b)) return false;
    if (orientation(n.a, n.b, m.a) == orientation(n.a, n.b, m.b)) return false;
    return true;
}

pair <bool, pt> findIntersection(const line &m, const line &n, ii mtype, ii ntype) // pairs represent left/right endpoints, 0: no endpoint, 1: open endpoint, 2: closed endpoint
{
    auto endCheck = [](ptT v1, ptT v2, int type)
    {
        return type == 0 ? true : (type == 1 ? v1 < v2 : v1 <= v2);
    };
    ptT denom = m.ab ^ n.ab;
    if (abs(denom) < EPS) return {false, pt()}; // PS: assumes that parallel lines do not intersect
    ptT mt = (n.a - m.a) ^ n.ab;
    ptT nt = (n.a - m.a) ^ m.ab;
    if (denom < 0) denom = -denom, mt = -mt, nt = -nt;
    bool intersects = endCheck(0, mt, mtype.first) and endCheck(mt, denom, mtype.second) and
                      endCheck(0, nt, ntype.first) and endCheck(nt, denom, ntype.second);
    pt res = intersects ? m.a + m.ab * mt / denom : pt();
    return {intersects, res};
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cout<<fixed<<setprecision(9);

    /* A: Finding polar angle [0, 2pi] for point p (long long) */
    freopen("angle1.in", "r", stdin);
    freopen("angle1.out", "w", stdout);
    pt p;
    cin >> p;
    double rad = angleCcw({1, 0}, p);
    if (rad < 0)
        rad = 2 * PI + rad;
    cout << rad <<'\n';

    /* B: Finding undirected angle [0, pi] between nonzero vectors (long long) */
    freopen("angle2.in", "r", stdin);
    freopen("angle2.out", "w", stdout);
    pt p, q;
    cin >> p >> q;
    double rad = abs(angleCcw(p, q));
    cout << rad << '\n';

    /* C: finding area of polygon (long long) */
    freopen("area.in", "r", stdin);
    freopen("area.out", "w", stdout);
    int n;
    cin >> n;
    polygon poly(n);
    for (int i = 0; i < n; i++)
        cin >> poly[i];
    ptT area = abs(polygonArea(poly));
    cout<< abs(polygonArea(poly)) / 2.0 <<'\n';

    /* D: finding area of triangle w/ orientation (long long) */
    freopen("area1.in", "r", stdin);
    freopen("area1.out", "w", stdout);
    pt points[3];
    for (int i = 0; i < 3; i++)
        cin >> points[i];
    cout << abs(triArea(points[0], points[1], points[2])) / 2.0 << '\n';

    // Helper for standard form equation
    auto lineToStandard = [](const line &l) // Returns {a, b, c} coefficients for ax + by + c = 0
    {
        if (abs(l.ab.x) < EPS)
            return tuple<ptT, ptT, ptT>{1, 0, -l.a.x};
        double slope = l.ab.y / l.ab.x;
        pt p = l.a;
        return tuple<ptT, ptT, ptT>{-slope, 1, slope * p.x - p.y};
    };

    auto standardToLine = [](ptT a, ptT b, ptT c) // Returns line corresponding to ax + by + c = 0
    {
        if (abs(b) < EPS)
            return line({-c/a, 0}, {0, 1}, true);
        return line({0, -c/b}, {b, -a}, true);
    };

    /* E: finding angle bisector of two segments (long double) */
    freopen("bisector.in", "r", stdin);
    freopen("bisector.out", "w", stdout);
    pt points[3];
    for (int i = 0; i < 3; i++)
        cin >> points[i];
    double angle = angleCcw(points[0], points[1], points[2]);
    pt angleBisectorEndpt = (points[1] - points[0]).rotateCcw(angle / 2.0) + points[0];
    double a, b, c;
    tie(a, b, c) = lineToStandard(line(points[0], angleBisectorEndpt));
    cout << a << " " << b << " " << c << '\n';

    /* F: finding distance from point to standard form line (long double) */
    freopen("distance1.in", "r", stdin);
    freopen("distance1.out", "w", stdout);
    pt p;
    ptT a, b, c;
    cin >> p >> a >> b >> c;
    line l = standardToLine(a, b, c);
    cout << l.distLine(p) << '\n';

    /* G: finding distance from point to line (long double) */
    freopen("distance2.in", "r", stdin);
    freopen("distance2.out", "w", stdout);
    pt p, a, b;
    cin >> p >> a >> b;
    line l(a, b);
    cout << l.distLine(p) << '\n';

    /* H: finding distance from point to ray (long double) */
    freopen("distance3.in", "r", stdin);
    freopen("distance3.out", "w", stdout);
    pt p, a, b;
    cin >> p >> a >> b;
    line l(a, b);
    cout << l.distRay(p) << '\n';

    /* I: finding distance from point to segment (long double) */
    freopen("distance4.in", "r", stdin);
    freopen("distance4.out", "w", stdout);
    pt p, a, b;
    cin >> p >> a >> b;
    line l(a, b);
    cout << l.distSegment(p) << '\n';

    /* J: finding distance between two segments (long double) */
    freopen("distance5.in", "r", stdin);
    freopen("distance5.out", "w", stdout);
    pt a, b, c, d;
    cin >> a >> b >> c >> d;
    line m(a, b), n(c, d);
    double res = 0.0;
    if(!intersectionSegment(m, n))
    {
        double min1 = min(m.distSegment(c), m.distSegment(d));
        double min2 = min(n.distSegment(a), n.distSegment(b));
        res = min(min1, min2);
    }
    cout << res << '\n';

    /* K: finding intersection point of non-parallel lines (long double) */
    freopen("intersec1.in", "r", stdin);
    freopen("intersec1.out", "w", stdout);
    line l[2];
    for (int i = 0; i < 2; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        l[i] = standardToLine(a, b, c);
    }
    cout << findIntersection(l[0], l[1], {0, 0}, {0, 0}).second << '\n';

    /* L: finding length of vector (long double) */
    freopen("length.in", "r", stdin);
    freopen("length.out", "w", stdout);
    pt p, q;
    cin >> p >> q;
    cout << sqrt(p.dist2(q)) << '\n';

    /* M: find normal equation of line given 2 points on it (long double) */
    freopen("line1.in", "r", stdin);
    freopen("line1.out", "w", stdout);
    pt p, q;
    cin >> p >> q;
    ptT a, b, c;
    tie(a, b, c) = lineToStandard(line(p, q));
    cout << a << " " << b << " " << c << '\n';

    /* N: find normal equation of line given point and slope (long double) */
    freopen("line2.in", "r", stdin);
    freopen("line2.out", "w", stdout);
    pt p, slp;
    cin >> p >> slp;
    ptT a, b, c;
    tie(a, b, c) = lineToStandard(line(p, slp.perpCcw(), true));
    cout << a << " " << b << " " << c << '\n';

    /* O: find two distinct lines that are always d-distance from given line with the same slope (long double) */
    freopen("line3.in", "r", stdin);
    freopen("line3.out", "w", stdout);
    ptT a, b, c, r;
    cin >> a >> b >> c >> r;
    line m = standardToLine(a, b, c);
    pt normal = m.ab.perpCw().normalize();
    line l[2];
    l[0] = line(m.a + r * normal, m.ab, true);
    l[1] = line(m.a - r * normal, m.ab, true);
    for (int i = 0; i < 2; i++)
    {
        ptT ra, rb, rc;
        tie(ra, rb, rc) = lineToStandard(l[i]);
        if (abs(ra) > EPS and ((ra < 0) ^ (a < 0)))
            ra = -ra, rb = -rb, rc = -rc;
        else if(abs(rb) > EPS and ((rb < 0) ^ (b < 0)))
            ra = -ra, rb = -rb, rc = -rc;
        cout<<ra<<" "<<rb<<" "<<rc<<'\n';
    }

    /* P: check if point is on given line (long double) */
    freopen("point1.in", "r", stdin);
    freopen("point1.out", "w", stdout);
    pt p;
    ptT a, b, c;
    cin >> p >> a >> b >> c;
    line l = standardToLine(a, b, c);
    if (orientation(l.a, l.b, p) == 0)
        cout << "YES" << '\n';
    else
        cout << "NO" << '\n';

    /* Q: check if point is on given ray (long double) */
    freopen("point2.in", "r", stdin);
    freopen("point2.out", "w", stdout);
    pt p, a, b;
    cin >> p >> a >> b;
    if (line(a, b).onRay(p))
        cout << "YES" << '\n';
    else
        cout << "NO" << '\n';

    /* R: check if point is on segment (long double) */
    freopen("point3.in", "r", stdin);
    freopen("point3.out", "w", stdout);
    pt p, a, b;
    cin >> p >> a >> b;
    if (line(a, b).onSegment(p))
        cout << "YES" << '\n';
    else
        cout << "NO" << '\n';

    /* S: check if two points are on the same side of line (long double) */
    freopen("position.in", "r", stdin);
    freopen("position.out", "w", stdout);
    pt p, q;
    ptT a, b, c;
    cin >> p >> q >> a >> b >> c;
    line l = standardToLine(a, b, c);
    if (orientation(l.a, l.b, p) == orientation(l.a, l.b, q))
        cout << "YES" << '\n';
    else
        cout << "NO" << '\n';

    /* T: find minimum distance between two rays (long double) */
    freopen("raydist.in", "r", stdin);
    freopen("raydist.out", "w", stdout);
    line l[2];
    for (int i = 0; i < 2; i++)
    {
        pt p, q;
        cin >> p >> q;
        l[i] = line(p, q);
    }
    double sol = 0.0;
    if (!findIntersection(l[0], l[1], {2, 0}, {2, 0}).first)
        sol = min(l[0].distRay(l[1].a), l[1].distRay(l[0].a));
    cout << sol << '\n';

    return 0;
}
