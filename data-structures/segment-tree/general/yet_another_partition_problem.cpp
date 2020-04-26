// inv segtree, finding partition ind s.t. a[i + 1]%a[i]=0 if both in same partition
// https://www.codechef.com/problems/EXUNC

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;

#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)

struct ST {
  int s;
  vector<ll> v;
  ST(int n) : s{n}, v(2 * s) {}
  void update(int l, int r, int u) {
    for(l += s, r += s; l <= r; (++l) >>= 1, (--r) >>= 1) {
      if (l & 1) v[l] += u;
      if (~r & 1) v[r] += u;
    }
  }
  auto query(int p) {
    ll res = 0;
    for (p += s; p >= 1; p >>= 1)
      res += v[p];
    return res;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;
  vi a(n);
  trav(i, a) cin >> i;

  ST st(n);
  rep(i, 1, n) {
    if (a[i] % a[i - 1] != 0)
      st.update(i, n - 1, 1);
  }
  rep(it, 0, q) {
    int t;
    cin >> t;
    if (t == 1) {
      int p, v;
      cin >> p >> v;
      --p;
      if (p > 0) {
        auto delta = (v % a[p - 1] != 0) - (a[p] % a[p - 1] != 0);
        st.update(p, n - 1, delta);
      }
      if (p < n - 1) {
        auto delta = (a[p + 1] % v != 0) - (a[p + 1] % a[p] != 0);
        st.update(p + 1, n - 1, delta);
      }
      a[p] = v;
    } else {
      int p;
      cin >> p;
      --p;
      auto comp = st.query(p);
      int lo = 0, hi = p;
      while (lo < hi) {
        auto mid = lo + (hi - lo) / 2;
        if (st.query(mid) == comp) hi = mid;
        else lo = mid + 1;
      }
      cout << lo + 1 << '\n';
    }
  }
}
