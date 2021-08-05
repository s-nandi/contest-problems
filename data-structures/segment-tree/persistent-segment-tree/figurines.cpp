// persistent segtree
// https://codeforces.com/gym/103081/problem/H
// 2020 Southwestern European Regional

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
 
int midpoint(int a, int b){return (a + b) / 2;}
 
struct ST {
  using T = int; // PS
  static constexpr T unit = 0;
  static T f(const T& a, const T& b){return a + b;}
  static T m(const T& a, auto val){return a + val;}
  static T init(auto val){return val;}
  
  int n{0};
  vector<T> v;
  vi lc, rc;
 
  ST() {make();}
  int make() {
    lc.PB(-1); rc.PB(-1);
    v.PB(unit);
    return sz(lc) - 1;
  }
  void makechildren(int i, auto lo, auto hi) {
    if (lc[i] == -1 or rc[i] == -1) {
      int lchild = make(), rchild = make();
      lc[i] = lchild, rc[i] = rchild;
    }
  }
  int build(int n_) { assert(sz(v) == 1);
    n = n_;
    return 0;
  }
  int build(const auto& a) { assert(sz(v) == 1);
    n = sz(a);
    build(0, 0, n - 1, a);
    return 0;
  }
  void build(int i, auto lo, auto hi, const auto& a) {
    if (lo == hi) v[i] = init(a[lo]);
    else {
      auto mid = lo + (hi - lo) / 2;
      makechildren(i, lo, hi);
      build(lc[i], lo, mid, a);
      build(rc[i], mid + 1, hi, a);
      v[i] = f(v[lc[i]], v[rc[i]]);
    }
  }
 
  T query(int i, auto l, auto r){assert(n); return query(i, 0, n - 1, l, r);} // [l, r]
  T query(int i, auto lo, auto hi, int l, int r) {
    if (i == -1 or r < lo or l > hi) return unit;
    else if (l <= lo and hi <= r) return v[i];
    else {
      auto mid = lo + (hi - lo) / 2;
      auto lq = query(lc[i], lo, mid, l, r);
      auto rq = query(rc[i], mid + 1, hi, l, r);
      return f(lq, rq);
    }
  }
 
  int update(int i, auto pos, auto val) {assert(n); return update(i, 0, n - 1, pos, val);} // [l, r]
  int update(int i, auto lo, auto hi, auto pos, auto val) {
    if (pos < lo or pos > hi) return i;
    auto j = make();
    if (lo == hi) v[j] = m(v[i], val);
    else {
      auto mid = lo + (hi - lo) / 2;
      makechildren(i, lo, hi);
      auto nlc = update(lc[i], lo, mid, pos, val);
      auto nrc = update(rc[i], mid + 1, hi, pos, val);
      lc[j] = nlc, rc[j] = nrc;
      v[j] = f(v[lc[j]], v[rc[j]]);
    }
    return j;
  }
};
 
auto tokenize(const auto& s) {
  string curr = "";
  vector<string> res;
  trav(c, s) {
    if (isspace(c)) {
      if (!empty(curr)) res.PB(curr);
      curr = "";
    } else curr += c;
  }
  if (!empty(curr)) res.PB(curr);
  return res;
}
 
int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);
 
  int n;
  cin >> n;
  cin.ignore();
  vector<vector<pair<int, int>>> days(n); // {i, -1/+1}
  trav(day, days) {
    string s;
    getline(cin, s);
    auto tokens = tokenize(s);
    trav(token, tokens) {
      char sgn = token[0];
      int num = stoi(token.substr(1, sz(token) - 1));
      int delta = sgn == '+' ? 1 : -1;
      day.PB({num, delta});
    }
  }
  
  vi d(n);
  trav(i, d) cin >> i;
 
 
  ST st{};
  vi roots{st.build(n + 50)}; // roots[i + 1] gives state at the end of day i (0-indexed)
  rep(i, 0, n) {
    int nw = roots.back();
    for (const auto& [ind, delta]: days[i]) {
      if (dbg) {
        cout << "Update " << ind << " " << delta << endl;
      }
      nw = st.update(nw, ind, delta);
    }
    roots.PB(nw);
  }
 
  ll x = 0;
  rep(i, 0, n) { 
    auto curr_day = d[i];
    if (dbg){cout << "Query " << curr_day << " " << x << " to " << n << endl;}
    assert(curr_day >= 0);
    assert(curr_day < sz(roots));
    auto cnt = st.query(roots[curr_day], x, n + 1);
    x = (x + cnt) % n;
  }
  
  cout << x << '\n';
}
