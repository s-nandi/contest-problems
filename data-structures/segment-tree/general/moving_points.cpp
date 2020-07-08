// dynamic segment tree, sweep line, reordering computation [(a - b1) + (a - b2) ... (a - bk) = cnt * a - sum(b)]
// https://codeforces.com/contest/1311/problem/F

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using vi = vector<int>;

struct edge{int to;};
using graph = vector<vector<edge>>;

const int MAXS = 100000000;

struct ST {
  using T = pair<int, ll>;
  static T f(const T& a, const T& b){return {a.first + b.first, a.second + b.second};}
  static T m(const T& a, ll val){return {a.first + 1, a.second + val};}
  
  int lo, hi;
  vector<T> v;
  vi lc, rc;
  ST(int lo, int hi) : lo{lo}, hi{hi} {make();}
  int make(ll val = 0) {
    lc.PB(-1); rc.PB(-1);
    v.PB({0, val});
    return sz(lc) - 1;
  }
  void normalize(int i) {
    if (lc[i] == -1 or rc[i] == -1) {
      int lchild = make();
      int rchild = make();
      lc[i] = lchild, rc[i] = rchild;
    }
  }
  void update(int pos, ll val) {update(0, pos, val, lo, hi);}
  void update(int i, int pos, ll val, int lo, int hi) {
    if (pos < lo or pos > hi) return;
    else if (pos == lo and pos == hi){v[i] = m(v[i], val);}
    else {
      int mid = lo + (hi - lo) / 2;
      normalize(i);
      update(lc[i], pos, val, lo, mid);
      update(rc[i], pos, val, mid + 1, hi);
      v[i] = f(v[lc[i]], v[rc[i]]);
    }
  }
  T query(int l, int r){return query(0, l, r, lo, hi);}
  T query(int i, int l, int r, int lo, int hi) {
    if (r < lo or l > hi) return {0, 0};
    else if (l <= lo and hi <= r) return v[i];
    else {
      int mid = lo + (hi - lo) / 2;
      normalize(i);         
      auto lq = query(lc[i], l, r, lo, mid);
      auto rq = query(rc[i], l, r, mid + 1, hi);
      return f(lq, rq);
    }
  }
};

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;
  vector<pii> a(n); // position, speed
  trav(i, a) cin >> i.first;
  trav(i, a) cin >> i.second;
  
  ll res = 0;
  ST st(-MAXS, MAXS); // st[speed] = (# points at speed, sum of positions at speed)
  sort(all(a));
  for (const auto& [position, speed]: a) {
    auto [cnt, acc] = st.query(-MAXS, speed);
    res += ((ll) cnt * position - acc);
    st.update(speed, position);
  }
  cout << res << '\n';
}
