// lazy segtree (affine range transformation, sum query)
// https://judge.yosupo.jp/problem/range_affine_range_sum

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

constexpr auto dbg = false;

const auto MOD = 998244353;
int add(int a, int b){auto res = a + b; return res < MOD ? res : res - MOD;}
int mult(int a, int b){return ((ll) a * b) % MOD;}

int midpoint(int l, int r){return l + (r - l) / 2;}

struct ST {
  struct Node {
    int sum;
  };
  struct Update {
    int mult, add;
    bool operator == (const Update& o) const {return mult == o.mult and add == o.add;}
  };
  /* PS start: change T,U,def,noop,f(),combine(),apply() */
  using T = Node;
  using U = Update;
  static constexpr T def = {0}; // identity element s.t. f(T a, def) = f(def, T a) = a
  static constexpr U noop = {1, 0}; // identity update s.t. combine(U a,noop) = combine(noop, U a) = a
  T f(const T& a, const T& b) {
    return {add(a.sum, b.sum)};
  }
  U combine(const U& first, const U& second) {
    return {mult(first.mult, second.mult), add(mult(first.add, second.mult), second.add)};
  }
  T apply(const T& v, const U& u, int lo, int hi) {
    auto len = hi - lo + 1;
    return T{add(mult(u.mult, v.sum), mult(u.add, len))};
  }
  /* PS end */

  int n;
  vector<T> val;
  vector<U> lazy;

  ST(int n_) : n{n_}, val(4 * n_, def), lazy(4 * n_, noop) {}
  ST(const auto& container) : n{sz(container)}, val(4 * n), lazy(4 * n, noop) {
    build(1, 0, n - 1, container);
  }
  void build(int i, int lo, int hi, const auto& container) {
    if (lo == hi) val[i] = {container[lo]}; // PS: change initialization from container
    else {
      auto mid = midpoint(lo, hi);
      build(2 * i, lo, mid, container);
      build(2 * i + 1, mid + 1, hi, container);
      val[i] = f(val[2 * i], val[2 * i + 1]);
    }
  }

  void update(int l, int r, const U& delta) {update(1, 0, n - 1, l, r, delta);}
  void update(int i, int lo, int hi, int l, int r, const U& delta) {
    if (r < lo or hi < l) push(i, lo, hi);
    else if (l <= lo and hi <= r) {
      lazy[i] = combine(lazy[i], delta);
      push(i, lo, hi);
    } else {
      auto mid = midpoint(lo, hi);
      push(i, lo, hi);
      update(2 * i, lo, mid, l, r, delta);
      update(2 * i + 1, mid + 1, hi, l, r, delta);
      val[i] = f(val[2 * i], val[2 * i + 1]);
    }
  }
  
  auto query(int l, int r){return query(1, 0, n - 1, l, r);}
  T query(int i, int lo, int hi, int l, int r) {
    if (r < lo or hi < l) return def;
    push(i, lo, hi);
    if (l <= lo and hi <= r) {
      return val[i];
    } else {
      auto mid = midpoint(lo, hi);
      auto lq = query(2 * i, lo, mid, l, r);
      auto rq = query(2 * i + 1, mid + 1, hi, l, r);
      return f(lq, rq);
    }
  }

  void push(int i, int lo, int hi) {
    if (lo != hi and !(lazy[i] == noop)) {
      lazy[2 * i] = combine(lazy[2 * i], lazy[i]);
      lazy[2 * i + 1] = combine(lazy[2 * i + 1], lazy[i]);
    }
    val[i] = apply(val[i], lazy[i], lo, hi);
    lazy[i] = noop;
  }
};

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;
  vi a(n);
  trav(i, a) cin >> i;
  ST st(a);
  rep(it, 0, q) {
    int t;
    cin >> t;
    if (t == 0) {
      int l, r, b, c;
      cin >> l >> r >> b >> c;
      --r;
      st.update(l, r, ST::Update{b, c});
    } else {
      int l, r;
      cin >> l >> r;
      --r;
      auto res = st.query(l, r);
      cout << res.sum << '\n';
    }
  }
}
