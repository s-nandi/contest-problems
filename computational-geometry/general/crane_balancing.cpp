// binary search, center of mass, stability issues (EPS floor)
// https://open.kattis.com/problems/crane
// 2014 World Finals

#include <bits/stdc++.h>
using namespace std;

using ld = long double;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define sz(x) (int)(x).size()

using ptT = ld;
struct pt {
  ptT x, y;
  pt operator + (const auto& o) const {return {x + o.x, y + o.y};}
  pt operator * (ptT k) const {return {k * x, k * y};}
  pt operator / (ptT k) const {return {x / k, y / k};}
  ptT operator ^ (const auto& o) const {return x * o.y - y * o.x;}
};

const ptT INF = 1031231234;
const ptT EPS = 1e-9;
const int ITERS = 45;

auto shoelace(const auto& ps) { // returns: (center of mass, area)
  pt res{0,0};
  ptT acc = 0;
  rep(i, 0, sz(ps)) {
    auto j = (i + 1) % sz(ps);
    auto a = (ps[i] ^ ps[j]);
    res = res + (ps[i] + ps[j]) * a;
    acc += a;
  }
  return pair{res / acc / 3, abs(acc) / 2};
}

auto com(pt p1, ptT w1, pt p2, ptT w2) {
  return (p1 * w1 + p2 * w2) / (w1 + w2);
}

int sideof(auto lo, auto hi, auto v) {
  // Careful: Using EPS here creates too much error s.t. floor/ceil fails later
  return (v < lo) ? -1 : ((v > hi) ? 1 : 0);
}

auto epsfloor(auto v) {
  if (abs(v - round(v)) < EPS) return round(v);
  else return floor(v);
}

auto epsceil(auto v) {
  if (abs(v - round(v)) < EPS) return round(v);
  else return ceil(v);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  vector<pt> crane(n);
  trav(p, crane) cin >> p.x >> p.y;

  ptT lb = INF, rb = -INF;
  trav(p, crane) {
    if (p.y != 0) continue;
    lb = min(lb, p.x);
    rb = max(rb, p.x);
  }
  auto [center, area] = shoelace(crane);
  bool canbalance =
    sideof(lb, rb, center.x) == 0 or
    sideof(rb, rb, center.x) * sideof(rb, rb, crane[0].x) == -1 or
    sideof(lb, lb, center.x) * sideof(lb, lb, crane[0].x) == -1;
  if (!canbalance) {
    cout << "unstable" << '\n';
    exit(0);
  }
  ptT min_weight, max_weight;
  bool prebalanced = sideof(lb, rb, center.x) == 0;
  if (prebalanced) min_weight = 0;
  else {
    ptT lo = 0, hi = INF;
    rep(i, 0, ITERS) {
      auto mid = lo + (hi - lo) / 2;
      auto pos = com(center, area, crane[0], mid);
      if (sideof(lb, rb, pos.x) == sideof(lb, rb, center.x))
        lo = mid;
      else
        hi = mid;
    }
    min_weight = hi;
  }
  bool inf_ok = sideof(lb, rb, crane[0].x) == 0;
  if (inf_ok) max_weight = INF;
  else {
    ptT lo = min_weight, hi = INF;
    rep(i, 0, ITERS) {
      auto mid = lo + (hi - lo) / 2;
      auto pos = com(center, area, crane[0], mid);
      if (sideof(lb, rb, pos.x) != 0)
        hi = mid;
      else
        lo = mid;
    }
    max_weight = lo;
  }
  int a = epsfloor(min_weight), b = epsceil(max_weight);
  cout << a << " .. " << (inf_ok ? "inf" : to_string(b)) << '\n';
}
