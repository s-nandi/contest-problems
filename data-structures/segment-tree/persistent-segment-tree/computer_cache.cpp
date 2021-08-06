// persistent segtree (inverted), range copy
// https://codeforces.com/gym/102433/problem/K
// 2019 Pacific Northwest Regional

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a);i<(b);++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back
using ll = long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int,int>;

constexpr auto dbg = false;
constexpr auto check = false;
constexpr auto custom = false;

struct edge{int to;};
using graph = vector<vector<edge>>;

const int MOD = 256;

auto midpoint(auto a, auto b){return a + (b - a) / 2;}

// Persistent range update, point query
struct ST {
  using T = int;
  using U = int;
  static constexpr T unit = 0;
  static T f(const T& a, const T& b){ return (a + b) % MOD; }
  static void combine(T& a, const U& upd) {
    a = (a + upd) % MOD;
  }
  static constexpr T def = 0;
  
  int L, R;
  vector<T> a;
  vi lc, rc;
 
  ST(const auto& vec) : L(0), R(sz(vec) - 1) {build(L, R, vec);}
  int make(int ln = -1, int rn = -1, T val = def) {
    lc.PB(ln), rc.PB(rn), a.PB(val);
    return sz(lc) - 1;
  }

  int build(auto lo, auto hi, const auto& vec) {
    int i = make();
    if (lo != hi) {
      auto mid = midpoint(lo, hi);
      int ln = build(lo, mid, vec);
      int rn = build(mid + 1, hi, vec);
      lc[i] = ln, rc[i] = rn;
    } else a[i] = vec[lo];
    return i;
  }
 
  T query(int i, auto p){ return query(i, L, R, p); }  
  T query(int i, auto lo, auto hi, auto p) {
    if (p < lo or p > hi) return unit;
    else if (i == -1) return def;
    else {
      auto mid = midpoint(lo, hi);
      auto lq = query(lc[i], lo, mid, p);
      auto rq = query(rc[i], mid + 1, hi, p);
      return f(f(lq, rq), a[i]);
    }
  }
 
  int update(int i, auto l, auto r, U upd) { return update(i, L, R, l, r, upd); }
  int update(int i, auto lo, auto hi, auto l, auto r, U upd) {
    if (r < lo or l > hi) return i;
    i = make(lc[i], rc[i], a[i]);
    if (l <= lo and hi <= r) {
      combine(a[i], upd);
    } else {
      auto mid = midpoint(lo, hi);
      auto ln = update(lc[i], lo, mid, l, r, upd);
      auto rn = update(rc[i], mid + 1, hi, l, r, upd);
      lc[i] = ln, rc[i] = rn;
    }
    return i;
  }
};

// Interval assign, point query
struct ST2 {
  using T = pii;
  using U = pii;
  static constexpr T def = pii{-1, -1};
  static constexpr T unit = pii{-2, -2};
  static void combine(T& a, const T& upd) {
    a = upd;
  }
  
  int L, R;
  vector<T> a;
 
  ST2(auto l, auto r) : L(l), R(r),  a(4 * (R - L + 1), def) {} 
  void push(int i, auto lo, auto hi) {
    if (!(a[i] == unit) and lo != hi) {
      auto mid = midpoint(lo, hi);
      update(2 * i, lo, mid, lo, hi, a[i]);
      update(2 * i + 1, mid + 1, hi, lo, hi, a[i]);
      a[i] = unit;
    }
  }

  T query(auto p){ return query(1, L, R, p); }
  T query(int i, auto lo, auto hi, auto p) {
    if (lo == hi) return a[i];
    else {
      auto mid = midpoint(lo, hi);
      push(i, lo, hi);
      return p <= mid ?
        query(2 * i, lo, mid, p) :
        query(2 * i + 1, mid + 1, hi, p);
    }
  }
 
  void update(auto l, auto r, U upd) { update(1, L, R, l, r, upd); }
  void update(int i, auto lo, auto hi, auto l, auto r, U& upd) {
    if (r < lo or l > hi) return;
    else if (l <= lo and hi <= r) {
      combine(a[i], upd);
      upd.second += (hi - lo + 1);
    } else {
      auto mid = midpoint(lo, hi);
      push(i, lo, hi);
      update(2 * i, lo, mid, l, r, upd);
      update(2 * i + 1, mid + 1, hi, l, r, upd);
    }
  }
};

int32_t main() {
  cin.tie(0)->sync_with_stdio(0);
  
  int n, m, q;
  cin >> n >> m >> q;

  vi start(m + 1);
  vi data_in;
  rep(i, 0, m) {
    int k;
    cin >> k;
    start[i] = sz(data_in);
    rep(it, 0, k) {
      int val;
      cin >> val;
      data_in.PB(val);
    }
  }
  start[m] = sz(data_in);

  ST data(data_in);
  data_in.clear();
  data_in.shrink_to_fit();
  int root = 0;
  
  ST2 cache(0, n - 1);
  rep(it, 0, q) {
    int t;
    cin >> t;
    if (t == 1) {
      int i, p;
      cin >> i >> p;
      --i; --p;
      auto ind = start[i];
      int len = start[i + 1] - start[i];
      cache.update(p, p + len - 1, pair{root, ind});
    } else if (t == 2) {
      int p;
      cin >> p;
      --p;
      auto [rt, ind] = cache.query(p);
      if (rt == -1) cout << 0 << '\n';
      else {
        auto res = data.query(rt, ind);
        cout << res << '\n';
      }
    } else {
      int i, l, r;
      cin >> i >> l >> r;
      --i; --l; --r;
      root = data.update(root, start[i] + l, start[i] + r, 1);
    }
  }
}
