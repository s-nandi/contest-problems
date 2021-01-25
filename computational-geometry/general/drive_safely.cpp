// geo primitives (angle of turn given 3 points), dp (interval dp - consider placing stop sign at the start of some [l, r] interval when at dp[l][# stopsigns])
// https://open.kattis.com/problems/drivesafely
// 2019 Bergen Open

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
#define cauto const auto
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using vi = vector<int>;

struct edge{int to;};
using graph = vector<vector<edge>>;

const ld MAXS = 180.L;
constexpr ld EPS = 1e-6;
constexpr ld INF = 1e15;

constexpr auto PI = acos(-1.);
using ptT = ld;
struct pt {
  ptT x, y;
  pt operator - (const auto& o) const {return {x - o.x, y - o.y};}
  ptT angle() const {return atan2(y, x) * 360. / (2 * PI);}
  ptT dist(const pt& o) const {
    auto dx = abs(x - o.x);
    auto dy = abs(y - o.y);
    return sqrt(dx * dx + dy * dy);
  }
};

auto minn(auto& a, auto b) {
  return b < a ? a = b, true : false;
}

int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n, k;
  cin >> n >> k;
  vector<pt> a(n);
  trav(p, a) {
    cin >> p.x >> p.y;
  }

  vector<ptT> dists;
  vector<ptT> limits;
  rep(i, 1, n) {
    // line from (i - 1) to i
    auto d = a[i - 1].dist(a[i]);
    dists.PB(d);
    limits.PB(MAXS);
    
    // turn from (i - 1) to i to (i + 1)
    if (i + 1 < n) {
      auto v1 = a[i] - a[i - 1];
      auto v2 = a[i + 1] - a[i];
      auto ang1 = v1.angle();
      auto ang2 = v2.angle();
      auto [mn, mx] = minmax(ang1, ang2);
      auto diff = min(mx - mn, (mn + 360.) - mx);
      limits.PB(MAXS - diff);
      dists.PB(0);
    }
  }
  assert(sz(dists) == sz(limits));
  int nevents = sz(dists);
  
  auto distmat = vector(nevents, vector<ptT>(nevents));
  auto limitmat = vector(nevents, vector<ptT>(nevents));
  rep(l, 0, nevents) {
    distmat[l][l] = dists[l];
    limitmat[l][l] = limits[l];
    rep(r, l + 1, nevents) {
      distmat[l][r] = distmat[l][r - 1] + dists[r];
      limitmat[l][r] = min(limitmat[l][r - 1], limits[r]);
    }
  }
  auto getdist = [&](int l, int r) {return distmat[l][r];};
  auto getlimit = [&](int l, int r) {return limitmat[l][r];};
  auto timefor = [&](int l, int r) {return getdist(l, r) / getlimit(l, r);};
  
  auto best = timefor(0, nevents - 1);

  auto dp = vector(nevents + 1, vector<ptT>(k + 1, INF)); // dp[i][j] = min time to get through 0..i exclusive, after using j speed limits
  rep(j, 0, k + 1) dp[0][j] = 0;
  rep(upto, 0, nevents) { // get from 0 to upto inclusive without a speed limit
    auto pref_limit = getlimit(0, upto);
    if (pref_limit < MAXS - EPS) continue;
    dp[upto + 1][0] = timefor(0, upto);
  }
  rep(i, 0, nevents) {
    rep(j, 0, k) {
      rep(upto, i, nevents) { // use a single speed limit from i..upto inclusive
        minn(dp[upto + 1][j + 1], dp[i][j] + timefor(i, upto));
      }
    }
  }
  rep(j, 0, k + 1) minn(best, dp[nevents][j]);
  cout << setprecision(11) << fixed << best << '\n';
}
