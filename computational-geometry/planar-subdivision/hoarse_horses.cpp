// euler's formula (multiple connected components), segment-segment intersection
// https://open.kattis.com/problems/hoarsehorses
// 2017 Benelux Algorithm Programming Contest

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;

#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back
#define cauto const auto

struct edge{int to;};
using graph = vector<vector<edge>>;

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
  typedef Point P;
  T x, y;
  explicit Point(T x_=0, T y_=0) : x(x_), y(y_) {}
  bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
  P operator+(P p) const { return P(x+p.x, y+p.y); }
  P operator-(P p) const { return P(x-p.x, y-p.y); }
  P operator*(T d) const { return P(x*d, y*d); }
  P operator/(T d) const { return P(x/d, y/d); }
  T dot(P p) const { return x*p.x + y*p.y; }
  T cross(P p) const { return x*p.y - y*p.x; }
  T cross(P a, P b) const { return (a-*this).cross(b-*this); }
  T dist2() const { return x*x + y*y; }
  double dist() const { return sqrt((double)dist2()); }
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
using pt = Point<ld>;

struct DSU {
  vi par;
  DSU(int n) : par(n, -1) {}
  int find(int i){return par[i] < 0 ? i : (par[i] = find(par[i]));}
  void join(int u, int v) {
    if ((u = find(u)) == (v = find(v))) return;
    par[u] += par[v];
    par[v] = u;
  }
};

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  vector<array<pt, 2>> lines(n);
  trav(line, lines) trav(p, line) cin >> p.x >> p.y;

  auto isect = vector(n, vector(n, false));
  rep(i, 0, n) rep(j, 0, i) {
    if (!empty(segInter(lines[i][0], lines[i][1], lines[j][0], lines[j][1]))) // technically we could check for segment intersection with integers
                                                                              // since we don't care about where the intersections happen
      isect[i][j] = isect[j][i] = true;
  }

  // it's ok to ignore degenerate lines and duplicate points since they cancel out; see below
  int V{0};
  {
    vector<pt> points;
    rep(i, 0, n) rep(t, 0, 2) points.PB(lines[i][t]);
    V = sz(points);
  }
  int E{0};
  {
    rep(i, 0, n) {
      int segments = 1;
      rep(j, 0, n) if (isect[i][j])
        segments++;
      E += segments;
    }
  }
  int CC{0};
  {
    DSU dsu(n);
    rep(i, 0, n) rep(j, 0, i) if (isect[i][j])
      dsu.join(i, j);
    set<int> roots;
    rep(i, 0, n) roots.insert(dsu.find(i));
    CC = sz(roots);
  }
  int F = E - V + CC + 1; // for this problem, an alternate formula would be F = # intersections - n + C + 1
  cout << (F - 1) << '\n';
}
