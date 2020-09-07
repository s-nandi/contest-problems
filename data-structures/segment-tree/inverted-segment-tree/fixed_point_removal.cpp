// inverted segment tree, binary search on segtree, offline processing, when rightmost element is added the weight of some prefix (or none) of left intervals will increase by 1 (based on slack)
// https://codeforces.com/contest/1404/problem/C
// Note: can also be done by fixing left endpoint, with 2 segment trees, one lazy (sum prefix, min range) and one regular (increment position, sum range)

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

struct ST {
  int s;
  vi v;
  ST(int n) : s{n}, v(2 * s) {}
  void update(int l, int r, int val) {
    for (l += s, r += s; l <= r; (++l) >>= 1, (--r) >>= 1) {
      if (l & 1) v[l] += val;
      if (~r & 1) v[r] += val;
    }
  }
  int query(int p) {
    int acc = 0;
    for (p += s; p; p >>= 1)
      acc += v[p];
    return acc;
  }
  int rightmost_geq(int upto, int val) { // assumes st.query(i) is non-increasing
    int lo = 0, hi = upto;
    while (lo < hi) {
      auto mid = lo + (hi - lo + 1) / 2;
      if (query(mid) >= val) lo = mid;
      else hi = mid - 1;
    }
    if (query(lo) < val) return -1;
    else return lo;
  }
};

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n, q;
  cin >> n >> q;
  vi a(n);
  trav(i, a) {cin >> i; --i;}
  vector<vector<pii>> byright(n);
  rep(it, 0, q) {
    int l, r;
    cin >> l >> r;
    r = n - 1 - r;
    byright[r].PB({l, it});
  }
  vi res(q);
  ST st(n);
  rep(i, 0, n) {
    if (a[i] <= i) {
      auto pos = st.rightmost_geq(i, i - a[i]);
      if (pos != -1) {
        st.update(0, pos, 1);
      }
    }
    for (const auto& [l, ith]: byright[i]) {
      res[ith] = st.query(l);
    }
  }
  trav(i, res) cout << i << '\n';
}
