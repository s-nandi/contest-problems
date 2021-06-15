// euler tour numbering, maintain max num of disjoint intervals (overlapping intervals guaranteed to nest one another)
// https://codeforces.com/contest/1528/problem/C

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

template <typename T>
optional<T> find_containing(const set<T>& intervals, auto val) {
  auto it = intervals.upper_bound(val);
  if (it == begin(intervals)) return nullopt;
  else {
    --it;
    const auto& cand = *it;
    assert(cand[0] <= val[0]);
    if (cand[1] >= val[1]) return cand;
    else return nullopt;
  }
}

template <typename T>
optional<T> find_contained(const set<T>& intervals, auto val) {
  auto it = intervals.lower_bound(val);
  if (it == end(intervals)) return nullopt;
  else {
    const auto& cand = *it;
    assert(val[0] <= cand[0]);
    if (cand[1] <= val[1]) return cand;
    else return nullopt;
  }
}

void dfs(const auto& g, int i, auto& times, int& tm) {
  times[i][0] = tm++;
  trav(e, g[i])
    dfs(g, e.to, times, tm);
  times[i][1] = tm;
}

int solve(const auto& g, int i, const auto& times, auto& intervals) {
  const auto& curr = times[i];

  auto redundant = find_containing(intervals, curr);
  if (redundant) intervals.erase(*redundant);

  auto contained = find_contained(intervals, curr);
  if (!contained) intervals.insert(curr);

  int best = sz(intervals);
  trav(e, g[i])
    best = max(best, solve(g, e.to, times, intervals));

  if (!contained) intervals.erase(curr);
  if (redundant) intervals.insert(*redundant);
  return best;
}

int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    graph g1(n), g2(n);
    rep(i, 1, n) {
      int par;
      cin >> par;
      g1[--par].PB({i});
    }
    rep(i, 1, n) {
      int par;
      cin >> par;
      g2[--par].PB({i});
    }

    vector<pii> times(n);
    {
      int timer = 0;
      dfs(g2, 0, times, timer);
    }
    
    set<pii> intervals;
    auto res = solve(g1, 0, times, intervals);
    cout << res << '\n';
  }
}
