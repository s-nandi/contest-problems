// min-cost triangulation, line seg. intersect check, pt in angular range check
// https://open.kattis.com/problems/structuralintegrity
// 2020 Mount Allison Programming Showdown

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define sz(a) (int)size(a)

using ptT = long long;
int sgn(ptT v){return (v > 0) - (v < 0);}
struct pt {
  ptT x, y;
  pt operator + (const pt& o) const {return {x + o.x, y + o.y};}
  pt operator - (const pt& o) const {return {x - o.x, y - o.y};}
  pt operator * (ptT k) const {return {x * k, y * k};}
  pt operator / (ptT k) const {return {x / k, y / k};}
  ptT operator * (const pt& o) const {return x * o.x + y * o.y;}
  ptT operator ^ (const pt& o) const {return x * o.y - y * o.x;}
};
int orientation(const pt& a, const pt& b, const pt& c){return sgn((b - a) ^ (c - b));}
ptT dist2(const pt& a, const pt& b){return (b - a) * (b - a);}
bool onSegment(const pt& s, const pt& e, const pt& p) {
  return sgn((s - p) ^ (e - p)) == 0 and (s - p) * (e - p) <= 0;
}
bool intersect(const pt& a, const pt& b, const pt& c, const pt& d) {
  auto oa = (d - c) ^ (a - c), ob = (d - c) ^ (b - c);
  auto oc = (b - a) ^ (c - a), od = (b - a) ^ (d - a);
  if (sgn(oa) * sgn(ob) < 0 and sgn(oc) * sgn(od) < 0) return true;
  else
    return onSegment(c, d, a) or onSegment(c, d, b) or
           onSegment(a, b, c) or onSegment(a, b, d);
}

bool between_angle(const pt& o, pt a, pt b, const pt& p) {
  assert(orientation(o, a, b) != 0);
  if (orientation(o, a, p) == 0 or orientation(o, p, b) == 0) return true;
  bool flip = false;
  if (orientation(o, a, b) == -1) {flip = true; swap(a, b);}
  auto oab = orientation(o, a, b);
  if (orientation(o, a, p) == oab and orientation(o, p, b) == oab) return true ^ flip;
  else return false ^ flip;
} // return true iff p in ccw angle aob

int n;
int next(int i, int s = 1){return i + s < n ? i + s : i + s - n;}
int prev(int i, int s = 1){return i - s >= 0 ? i - s : i - s + n;}

bool feasible(const auto& ps, int i, int j) {
  if (!between_angle(ps[i], ps[prev(i)], ps[next(i)], ps[j])) return false;
  rep(k, 0, sz(ps)) {
    if (k == i or k == j or next(k) == i or next(k) == j) continue;
    if (intersect(ps[k], ps[next(k)], ps[i], ps[j])) return false;
  }
  return true;
}

const int MAXN = 200;
const ll INF = 1e15;
ll costs[MAXN + 5][MAXN + 5];
ll dp[MAXN + 5][MAXN + 5]; // dp[len][i] = cost for triangulating closed loop [i..i+len]
auto minn(auto& a, auto b){a = min(a, b);}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  vector<pt> ps(n);
  trav(p, ps) cin >> p.x >> p.y;

  rep(i, 0, n) rep(j, 0, n) costs[i][j] = INF;
  rep(i, 0, n) rep(j, 0, n) if (i != j) {
    if (j == next(i) or j == prev(i)) costs[i][j] = 0;
    else if (feasible(ps, i, j))
      costs[i][j] = dist2(ps[i], ps[j]);
  }

  rep(len, 0, n) rep(i, 0, n) dp[len][i] = INF;
  rep(len, 0, 3) rep(i, 0, n) dp[len][i] = 0;
  rep(len, 3, n) {
    rep(i, 0, n) {
      int j = next(i, len);
      rep(step, 1, len) {
        int k = next(i, step);
        auto cost = costs[i][k] + costs[j][k]; // make triangle ijk
        minn(dp[len][i], dp[step][i] + dp[len - step][k] + cost);
      }
    }
  }
  auto best = dp[n - 1][0];
  cout << best << '\n'; // impossible is never printed; can always triangulate
}
