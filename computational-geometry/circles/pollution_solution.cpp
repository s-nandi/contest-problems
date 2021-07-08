// circle polygon intersection
// https://codeforces.com/gym/101208/problem/J
// 2013 World Finals

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a);i<(b);++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back

using ll = long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int,int>;

struct edge{int to;};
using graph = vector<vector<edge>>;

constexpr auto dbg = false;

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
  ld dist() const { return sqrt((ld)dist2()); }
};

typedef Point<ld> P;
#define arg(p, q) atan2(p.cross(q), p.dot(q))
ld circlePoly(P c, ld r, vector<P> ps) {
  auto tri = [&](P p, P q) {
               auto r2 = r * r / 2;
               P d = q - p;
               auto a = d.dot(p)/d.dist2(), b = (p.dist2()-r*r)/d.dist2();
               auto det = a * a - b;
               if (det <= 0) return arg(p, q) * r2;
               auto s = max(0.L, -a-sqrt(det)), t = min(1.L, -a+sqrt(det));
               if (t < 0 || 1 <= s) return arg(p, q) * r2;
               P u = p + d * s, v = p + d * t;
               return arg(p,u) * r2 + u.cross(v)/2 + arg(v,q) * r2;
             };
  auto sum = 0.0;
  rep(i,0,sz(ps))
    sum += tri(ps[i] - c, ps[(i + 1) % sz(ps)] - c);
  return sum;
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n; ld r;
  cin >> n >> r;
  P center{0, 0};
  vector<P> ps(n);
  rep(i, 0, n) {
    cin >> ps[i].x >> ps[i].y;
  }
  cout << fixed << setprecision(12) << circlePoly(center, r, ps) << '\n';
}
