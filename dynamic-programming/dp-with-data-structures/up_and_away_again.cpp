// dp with segtree (inverted, prefix min update, point value query), line sweep
// https://codesprintla21open-team.kattis.com/problems/codesprintla21.upandawayagain

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

const int INF = 1031231234;
const int MAXHD = 2 * 100'000 + 500;

struct Tree {
  using T = int;
  static constexpr T unit = INF;
  T f(T a, T b) { return min(a, b); } // (any associative fn)
  vector<T> s; int n;
  Tree(int n = 0, T def = unit) : s(2 * n, def), n(n) {}
  T query(int pos) {
    T acc = unit;
    for (pos += n; pos >= 1; pos /= 2)
      acc = f(s[pos], acc);
    return acc;
  }
  void update(int l, int r, T val) {
    for (l += n, r += n; l <= r; (++l) >>= 1, (--r) >>= 1) {
      if (l & 1) s[l] = f(val, s[l]);
      if (~r & 1) s[r] = f(s[r], val);
    }
  }
};

auto solve(int n, int x, ll t, vi h, vi d) {
  vi hd(n);
  rep(i, 0, n) hd[i] = h[i] + d[i];

  vi inds(n);
  iota(all(inds), 0);
  sort(all(inds), [&](int i, int j){return h[i] < h[j];});

  Tree st(MAXHD);
  vi dp(n, INF);
  st.update(0, hd[x], 0);
  trav(i, inds) {
    if (h[i] < h[x]) continue;
    dp[i] = min(dp[i], i == x ? 0 : st.query(h[i]) + 1);
    st.update(0, hd[i], dp[i]);
  }
  ll res = dp[0];
  return res < INF ? res * t : -1LL;
}

int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n, x, t;
  cin >> n >> x >> t;
  --x;
  vi h(n), d(n);
  trav(i, h) cin >> i;
  trav(i, d) cin >> i;
  cout << solve(n, x, t, h, d) << '\n';
}
