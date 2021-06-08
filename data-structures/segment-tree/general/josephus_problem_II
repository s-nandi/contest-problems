// binary descent on segtree (find kth active index in [l, r]), josephus problem
// https://cses.fi/problemset/task/2163/

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

int midpoint(int lo, int hi){return (lo + hi) / 2;}

struct ST {
  using T = int;
  static T f(T a, T b){return a + b;}
  static constexpr T def = 0;
  
  int s;
  vi a;
  ST(int n) : s{n}, a(4 * n, def) {}
  
  void update(int p, int v) {update(1, 0, s - 1, p, v);}
  void update(int i, int lo, int hi, int p, int v) {
    if (p < lo or p > hi) return;
    else if (p <= lo and hi <= p) a[i] += v;
    else {
      auto mid = midpoint(lo, hi);
      update(2 * i, lo, mid, p, v);
      update(2 * i + 1, mid + 1, hi, p, v);
      a[i] = f(a[2 * i], a[2 * i + 1]);
    }
  }

  int find(int l, int r, int& target){return find(1, 0, s - 1, l, r, target);}
  int find(int i, int lo, int hi, int l, int r, int& target) {
    if (hi < l or lo > r) return -1;
    else if (l <= lo and hi <= r and a[i] < target) {
      target -= a[i];
      return -1;
    } else if (lo == hi) {
      return lo;
    } else {
      auto mid = midpoint(lo, hi);
      if (auto lq = find(2 * i, lo, mid, l, r, target); lq != -1) return lq;
      else return find(2 * i + 1, mid + 1, hi, l, r, target);
    }
  }
};

int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n, k;
  cin >> n >> k; ++k;
  ST st(n);
  rep(i, 0, n) st.update(i, 1);
  
  int pos = 0;
  vi res(n);
  rep(i, 0, n) {
    auto rem = k;
    auto got = st.find(pos, n - 1, rem);
    if (got == -1) {
      auto total = st.a[1];
      rem = (rem - 1) % total + 1;
      got = st.find(0, n - 1, rem);
      assert(got != -1);
    }
    res[i] = got;
    pos = got;
    st.update(got, -1);
  }
  trav(i, res) cout << (i + 1) << " "; cout << '\n';
}
