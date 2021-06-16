// lazy segtree (max range, inc range, binary descent), find max k s.t. count # in [0, k] >= k + 1
// https://codeforces.com/gym/102862/problem/I
// 2020 LU ICPC Selection

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
const int MAXA = 1'000'000 + 1;

int midpoint(int lo, int hi){return (lo + hi) / 2;}

struct ST {
  using T = int;
  using U = int;
  static constexpr T def = -INF;
  static constexpr U noop = 0;
  T f(T i, T j) { return max(i, j); }
  T combine(U u, U v) { return u + v; }
  T apply(U u, T i) { return u + i; }
  
  int s;
  vector<T> a;
  vector<U> b;
  ST(int n) : s{n}, a(4 * n), b(4 * n, noop) {build(1, 0, s - 1);}

  void push(int i, int lo, int hi) {
    if (b[i] != noop) {
      a[i] = apply(b[i], a[i]);
      if (lo != hi) {
        b[2 * i] = combine(b[2 * i], b[i]);
        b[2 * i + 1] = combine(b[2 * i + 1], b[i]);
      }
      b[i] = noop;
    }
  }
  
  void build(int i, int lo, int hi) {
    if (lo == hi) a[i] = -(lo + 1);
    else {
      auto mid = midpoint(lo, hi);
      build(2 * i, lo, mid);
      build(2 * i + 1, mid + 1, hi);
      a[i] = f(a[2 * i], a[2 * i + 1]);
    }
  }

  void update(int l, int r, U val) {update(1, 0, s - 1, l, r, val);}
  void update(int i, int lo, int hi, int l, int r, U val) {
    if (hi < l or lo > r) push(i, lo, hi);
    else if (l <= lo and hi <= r) {
      b[i] = combine(b[i], val);
      push(i, lo, hi);
    } else {
      auto mid = midpoint(lo, hi);
      push(i, lo, hi);
      update(2 * i, lo, mid, l, r, val);
      update(2 * i + 1, mid + 1, hi, l, r, val);
      a[i] = f(a[2 * i], a[2 * i + 1]);
    }
  }
  
  int lastnonneg(){return lastnonneg(1, 0, s - 1);}
  int lastnonneg(int i, int lo, int hi) {
    push(i, lo, hi);
    if (a[i] < 0) return -1;
    else if (lo == hi) {
      return lo;
    } else {
      auto mid = midpoint(lo, hi);
      auto rq = lastnonneg(2 * i + 1, mid + 1, hi);
      if (rq != -1) return rq;
      else return lastnonneg(2 * i, lo, mid);
    }
  }
};

int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int q;
  cin >> q;
  
  ST st(MAXA + 1);
  while (q--) {
    int t, val;
    cin >> t >> val;
    if (t == 1) {
      st.update(val, MAXA, 1);
    } else { assert(t == 2);
      st.update(val, MAXA, -1);
    }
    auto res = st.lastnonneg() + 1;
    cout << res << '\n';
  }
}
