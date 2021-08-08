// rotating callipers, min bounding rectangle perimeter
// https://open.kattis.com/problems/fenceortho

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a);i<(b);++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back

using ll = long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int,int>;

constexpr auto dbg = false;

struct edge{int to;};
using graph = vector<vector<edge>>;

constexpr double PI = acos(-1.);
constexpr double EPS = 1e-9;
constexpr double INF = 1e18;

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
  typedef Point P;
  T x, y;
  explicit Point(T x=0, T y=0) : x(x), y(y) {}
  bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
  bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
  P operator+(P p) const { return P(x+p.x, y+p.y); }
  P operator-(P p) const { return P(x-p.x, y-p.y); }
  P operator*(T d) const { return P(x*d, y*d); }
  P operator/(T d) const { return P(x/d, y/d); }
  T dot(P p) const { return x*p.x + y*p.y; }
  T cross(P p) const { return x*p.y - y*p.x; }
  T cross(P a, P b) const { return (a-*this).cross(b-*this); }
  T dist2() const { return x*x + y*y; }
  double dist() const { return sqrt((double)dist2()); }
  // angle to x-axis in interval [-pi, pi]
  double angle() const { return atan2(y, x); }
  P unit() const { return *this/dist(); } // makes dist()=1
  P perp() const { return P(-y, x); } // rotates +90 degrees
  P normal() const { return perp().unit(); }
  // returns point rotated 'a' radians ccw around the origin
  P rotate(double a) const {
    return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
  friend ostream& operator<<(ostream& os, P p) {
    return os << "(" << p.x << "," << p.y << ")"; }
};

int next(int i, int n, int s = 1) { return (i + s) % n; }
int prev(int i, int n, int s = 1) { return (i - s + n) % n; }

template <typename P> vector<P> convexHull(vector<P> pts) {
  if (sz(pts) <= 1) return pts;
  sort(all(pts));
  vector<P> h(sz(pts)+1);
  int s = 0, t = 0;
  for (int it = 2; it--; s = --t, reverse(all(pts)))
    for (P p : pts) {
      while (t >= s + 2 && h[t-2].cross(h[t-1], p) <= 0) t--;
      h[t++] = p;
    }
  return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}

template<class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
  auto d = (e1 - s1).cross(e2 - s2);
  if (d == 0) // if parallel
    return {-(s1.cross(e1, s2) == 0), P(0, 0)};
  auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
  return {1, (s1 * p + e1 * q) / d};
}

template <class T2, class T1>
Point<T2> convert(Point<T1> p) {
  return Point<T2>((T2) p.x, (T2) p.y);
}

template <class P> P extend(P p, double ang) {
  return p + P{cos(ang), sin(ang)};
}

template <class P> pair<int, P> lineInterPointSlope(P p1, double s1, P p2, double s2) {
  return lineInter(p1, extend(p1, s1), p2, extend(p2, s2));
}

template <class P> auto perimeter(const vector<P>& a) {
  auto res = (a[0] - a.back()).dist();
  rep(i, 0, sz(a) - 1)
    res += (a[i + 1] - a[i]).dist();
  return res;
}

template <class P> double solve(vector<P> a) {
  constexpr int nsides = 4;
  
  int n = sz(a);
  auto rot_ind = max_element(all(a), [](auto p1, auto p2) {
                                       return tie(p1.y, p2.x) < tie(p2.y, p1.x);
                                     }) - begin(a); // top right corner
  rotate(begin(a), begin(a) + rot_ind, end(a)); // ensures sorted angles, see assert below

  double best = INF;
  vector<P> diff(n);
  rep(i, 0, n) diff[i] = a[next(i, n)] - a[i];
  vector<double> angles(n);
  rep(i, 0, n) angles[i] = diff[i].angle();
  assert(is_sorted(all(angles))); // necessary for 2-pointers idea to work

  auto angs = [&](int i) { return angles[i % n] + (i / n) * 2 * PI; };

  vi inds(nsides);
  rep(inds0, 0, n) {
    inds[0] = inds0;
    rep(i, 1, nsides) {
      inds[i] = max(inds[i], inds[i - 1]);
      while (angs(inds[i]) - angs(inds[0]) < i * PI / 2 - EPS) inds[i]++;
    }
    
    vector<Point<double>> points(nsides);
    rep(i, 0, 4) points[i] = convert<double>(a[inds[i] % n]);
    vector<double> slopes(nsides);
    rep(i, 0, 4) slopes[i] = angs(inds[0]) + i * PI / 2;
    vector<Point<double>> rect(nsides);
    rep(i, 0, nsides) {
      int j = prev(i, nsides);
      auto [status, isect] = lineInterPointSlope(points[i], slopes[i], points[j], slopes[j]);
      assert(status == 1);
      rect[i] = isect;
    }
    best = min(best, perimeter(rect));
  }
  return best;
}

int32_t main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  while (cin >> n) {
    vector<Point<int>> a(n);
    trav(p, a) cin >> p.x >> p.y;
    auto hull = convexHull(a);
    auto res = solve(hull);
    cout << setprecision(10) << fixed << res << '\n';
  }
}
