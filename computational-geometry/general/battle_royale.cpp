// optimal path avoiding circle, circle tangents
// https://codeforces.com/gym/102021 (problem B)
// 2018 German Collegiate Programming Contest

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
using ll = long long;
using ld = long double;
using vi = vector<int>;
using pii = array<int,2>;

constexpr bool dbg = false;

struct edge{int to;};
using graph = vector<vector<edge>>;

constexpr auto PI = acos(-1);

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
  double dist(P p) const { return (*this - p).dist(); }
  // angle to x-axis in interval [0, 2pi]
  double angle() const { return atan2(y, x) + PI; }
  P unit() const { return *this/dist(); } // makes dist()=1
  P perp() const { return P(-y, x); } // rotates +90 degrees
  P normal() const { return perp().unit(); }
  // returns point rotated 'a' radians ccw around the origin
  P rotate(double a) const {
    return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
  friend ostream& operator<<(ostream& os, P p) {
    return os << "(" << p.x << "," << p.y << ")"; }
};

template<class P>
vector<pair<P, P>> tangents(P c1, double r1, P c2, double r2) {
  P d = c2 - c1;
  double dr = r1 - r2, d2 = d.dist2(), h2 = d2 - dr * dr;
  if (d2 == 0 || h2 < 0)  return {};
  vector<pair<P, P>> out;
  for (double sign : {-1, 1}) {
    P v = (d * dr + d.perp() * sqrt(h2) * sign) / d2;
    out.push_back({c1 + v * r1, c2 + v * r2});
  }
  if (h2 == 0) out.pop_back();
  return out;
}

using ptT = ld;
using pt = Point<ptT>;
ptT INF = 1e18;

auto arclength(pt p1, pt p2, pt c, ptT r) { // min arc length between p1 and p2 on circle (c, r)
  auto vec1 = p1 - c;
  auto vec2 = p2 - c;
  auto ang1 = vec1.angle();
  auto ang2 = vec2.angle();
  auto diff = abs(ang1 - ang2);
  rep(offset, -1, 2) {
    diff = min(diff, abs((ang1 + 2 * PI * offset) - ang2));
  }
  return diff * r;
}

int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);
  cout << setprecision(9) << fixed;

  pt c;
  cin >> c.x >> c.y;
  pt d;
  cin >> d.x >> d.y;
  pt big; ptT rbig;
  cin >> big.x >> big.y >> rbig;
  pt small; ptT rsmall;
  cin >> small.x >> small.y >> rsmall;

  array<vector<pt>, 2> tang;
  auto cand = vector{c, d};
  rep(t, 0, 2) {
    auto p = cand[t];
    auto got = tangents(small, rsmall, p, 0);
    trav(elem, got) tang[t].PB(elem.first);
  }

  ptT best = INF;
  rep(k1, 0, sz(tang[0])) {
    rep(k2, 0, sz(tang[1])) {
      auto straight1 = cand[0].dist(tang[0][k1]);
      auto curve = arclength(tang[0][k1], tang[1][k2], small, rsmall);
      auto straight2 = cand[1].dist(tang[1][k2]);
      auto possible = straight1 + curve + straight2;
      best = min(best, possible);
    }
  }
  cout << best << '\n';
}
