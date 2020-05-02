// segment intersection, convex hull, point in hull
// https://utipc20s.kattis.com/problems/utipc20s.wellthatsjustgrate
// 2020 UT Spring Programming Contest

#include <bits/stdc++.h>
using namespace std;

using ld = long double;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back

constexpr ld EPS = 1e-9;
template <class T> int sgn(T x) { return (x > EPS) - (x < -EPS); }
template<class T>
struct Point {
  typedef Point P;
  T x, y;
  Point(T x=0, T y=0) : x(x), y(y) {}
  bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
  bool operator==(P p) const { return sgn(x - p.x) == 0 and sgn(y - p.y) == 0; }
  P operator+(P p) const { return P(x+p.x, y+p.y); }
  P operator-(P p) const { return P(x-p.x, y-p.y); }
  P operator*(T d) const { return P(x*d, y*d); }
  P operator/(T d) const { return P(x/d, y/d); }
  T dot(P p) const { return x*p.x + y*p.y; }
  T cross(P p) const { return x*p.y - y*p.x; }
  T cross(P a, P b) const { return (a-*this).cross(b-*this); }
};

template<class P> bool onSegment(P s, P e, P p) {
  return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

template<class P> vector<P> segInter(P a, P b, P c, P d) {
  auto oa = c.cross(d, a), ob = c.cross(d, b),
    oc = a.cross(b, c), od = a.cross(b, d);
  // Checks if intersection is single non-endpoint point.
  if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
    return {(a * ob - b * oa) / (ob - oa)};
  set<P> s;
  if (onSegment(c, d, a)) s.insert(a);
  if (onSegment(c, d, b)) s.insert(b);
  if (onSegment(a, b, c)) s.insert(c);
  if (onSegment(a, b, d)) s.insert(d);
  return {all(s)};
}

template<class P>
vector<P> convexHull(vector<P> pts) {
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
int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }

template <class P>
bool inHull(const vector<P>& l, P p, bool strict = true) {
  int a = 1, b = sz(l) - 1, r = !strict;
  if (sz(l) < 3) return r && onSegment(l[0], l.back(), p);
  if (sideOf(l[0], l[a], l[b]) > 0) swap(a, b);
  if (sideOf(l[0], l[a], p) >= r || sideOf(l[0], l[b], p)<= -r)
    return false;
  while (abs(a - b) > 1) {
    int c = (a + b) / 2;
    (sideOf(l[0], l[c], p) > 0 ? b : a) = c;
  }
  return sgn(l[a].cross(l[b], p)) < r;
}

template<class P>
vector<pair<P, P>> tosegments(P dl, P ur) {
  auto [x1, y1] = dl;
  auto [x2, y2] = ur;
  vector<pair<P, P>> res;
  res.PB({{x1, y1}, {x2, y1}});
  res.PB({{x2, y1}, {x2, y2}});
  res.PB({{x2, y2}, {x1, y2}});
  res.PB({{x1, y2}, {x1, y1}});
  return res;
}

template<class P>
vector<P> intersections(vector<pair<P, P>>& grate, P s, P e) {
  vector<P> res;
  trav(edge, grate) {
    trav(p, segInter(s, e, edge.first, edge.second))
      res.PB(p);
  }
  return res;
}

using ptT = ld;
using pt = Point<ptT>;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ptT l, w;
  int n, p;
  cin >> l >> w >> n >> p;
  vector<pair<pt, pt>> grate;
  rep(i, 0, n) {
    ptT x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    grate.PB({{x1, y1}, {x2, y2}});
  }
  rep(it, 0, p) {
    ptT x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    vector<pt> isect;
    auto phone = tosegments(Point{x1, y1}, Point{x2, y2});
    trav(edge, phone)
      trav(p, intersections(grate, edge.first, edge.second))
      isect.PB(p);

    auto hull = convexHull(isect);
    auto com = pt{(x1 + x2) / 2, (y1 + y2) / 2};
    if (sz(hull) <= 1) {
      cout << "Yes" << '\n';
    } else if (sz(hull) == 2) {
      auto contained = onSegment(hull[0], hull[1], com);
      cout << (contained ? "No" : "Yes") << '\n';
    } else {
      auto contained = inHull(hull, com, false);
      cout << (contained ? "No" : "Yes") << '\n';
    }
  }
}
