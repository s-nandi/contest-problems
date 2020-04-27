// radial sweep, non-trivial invariant, # of even partitions with straight line
// https://open.kattis.com/problems/fairdivisions
// 2019 Northeast NA Regional

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back

using ptT = long long;
int sgn(ptT v){return (v > 0) - (v < 0);}
struct pt {
  using T = ptT;
  T x, y;
  pt operator + (const pt& o) const {return {x + o.x, y + o.y};}
  pt operator - (const pt& o) const {return {x - o.x, y - o.y};}
  pt operator * (T k) const {return {k * x, k * y};}
  T operator * (const pt& o) const {return x * o.x + y * o.y;}
  T operator ^ (const pt& o) const {return x * o.y - y * o.x;}
  bool operator == (const pt& o) const {return x == o.x and y == o.y;}
  bool operator < (const pt& o) const {return tie(y, x) < tie(o.y, o.x);}
};
int orientation(const pt& a, const pt& b, const pt& c) {return sgn((b - a) ^ (c - b));}
pt reflect(const pt& a, const pt& b) {return a + (b - a) * 2;};

void remap(auto& vec, const auto& mapping) {
  auto tmp = vec;
  rep(i, 0, sz(vec)) vec[i] = tmp[mapping[i]];
}

enum color {red, blue};
int radialsweep(vector<pt> ps, pt origin) {
  ps.erase(find(all(ps), origin));
  auto normalized = ps;
  trav(p, normalized) if (p < origin)
    p = reflect(p, origin);
  vi indices(sz(ps));
  iota(all(indices), 0);
  auto cmp = [&](int i, int j) {
               return orientation(origin, normalized[i], normalized[j]) == 1;
             };
  sort(all(indices), cmp);
  remap(ps, indices);
  /*
   * Draw line EPS to the left of origin, and EPS right of event (loop var) point
   * Red points are on the same side of this line as the origin (cw), 
   * Blue points are on the other side of the line as the origin (ccw)
   *
   * Start with sweep line being 'horizontal' (EPS above origin, tilted EPS down)
   * So points < the origin are initially red and vice-versa (origin is always red)
   *
   * Note that fixing two red (or blue) points to determine a line does not work
   * since multiple such pairs can be used to construct distinct lines that do not
   * produce distinct partitions -- one red and one blue point must be used
   */
  array<int, 2> cnt;
  cnt[red] = 1, cnt[blue] = 0;
  vector<color> colors(sz(ps));
  rep(i, 0, sz(ps)) {
    colors[i] = ps[i] < origin ? red : blue;
    cnt[colors[i]]++;
  }
  int res = 0;
  for (auto l = 0, r = 0; l < sz(ps); l = r) {
    vector<int> process;
    while (r < sz(ps) and orientation(origin, ps[l], ps[r]) == 0)
      process.PB(r++);
    bool equal_before = cnt[red] == cnt[blue];
    bool have_above = false;
    trav(ind, process) {
      have_above |= origin < ps[ind];
      cnt[colors[ind]]--;
      colors[ind] = colors[ind] == red ? blue : red;
      cnt[colors[ind]]++;
    }
    /*
     * Must maintain invariant where we uniquely determine lines w/ 1 blue and 1 red
     * point s.t. line cannot be rotated any further without changing the partition
     *
     * If we don't have a point above in our current iteration, we would end up
     * counting an instance where the line is to the left of origin AND to the 
     * left of some point below the origin, so we ignore such cases and multiply
     * by two at the end
     *
     * We also check for red == blue equality BEFORE processing the current iteration
     * since we want to capture the situation where we are to the right of the blue
     * event point (which is one of the currently processed nodes), and since we are
     * sweeping left (ccw), this equality should be checked before processing the
     * event point which would rotate the line to the left of the blue event point
     */
    if (have_above and equal_before) res++;
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  vector<pt> ps(n);
  rep(i, 0, n) cin >> ps[i].x >> ps[i].y;
  auto ways = 0LL;
  trav(p, ps) ways += radialsweep(ps, p);
  cout << ways * 2 << '\n';
}
