// dp (on sorted vals), greedy (compress adjacent equal values), count inverse value (maximize # nonsplits)
// https://open.kattis.com/problems/ascendingphoto
// 2017 Northwestern Europe Regional

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

const int INF = 1031231324;

void maxx(auto& a, auto b){a = max(a, b);}

vi compress(vi a) {
  vi b;
  trav(i, a) if (empty(b) or b.back() != i)
    b.PB(i);
  return b;
}

struct Best2 {
  using T = pii;
  static constexpr T def = {-INF, -1};
  static bool isbetter(T a, T b) {return a > b;}

  T v1{def}, v2{def};
  void add(T v) {
    if (isbetter(v, v1)) swap(v, v1);
    if (isbetter(v, v2)) swap(v, v2);
  }

  T exclude(int ind) {
    return v1.second == ind ? v2 : v1;
  }
};

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  vi a(n);
  trav(i, a) cin >> i;
  a = compress(a);
  n = sz(a);
  
  auto sorted = a;
  sort(all(sorted));
  sorted.erase(unique(all(sorted)), end(sorted));
  auto indexof = [&](int i) -> int {
                   return lower_bound(all(sorted), i) - begin(sorted);
                 };
  trav(i, a) i = indexof(i);
  int m = sz(sorted); // a[i] now in [0..m-1]

  vector<vi> byvalue(n);
  rep(i, 0, n) byvalue[a[i]].PB(i);
  
  vi dp_first(n), dp_last(n);
  rep(val, 0, n) {
    int best_prev = 0;
    if (val > 0) {
      trav(i, byvalue[val - 1])
        maxx(best_prev, dp_last[i]);
    }
    Best2 firstval;
    trav(i, byvalue[val]) {
      maxx(dp_first[i], best_prev);
      if (i > 0 and a[i - 1] == val - 1)
        maxx(dp_first[i], dp_last[i - 1] + 1);
      firstval.add({dp_first[i], i});
    }
    trav(i, byvalue[val]) {
      auto exc = sz(byvalue[val]) > 1 ? i : -1;
      maxx(dp_last[i], firstval.exclude(exc).first);
    }
  }
  auto best = -INF;
  trav(i, byvalue[m - 1]) maxx(best, dp_last[i]);
  cout << ((n - 1) - best) << '\n';
}
