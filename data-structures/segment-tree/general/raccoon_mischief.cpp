// inverted segment tree (latest update over range, # of updates over range)
// https://codeforces.com/gym/102621/problem/D
// 2020 Montgomery Blair Programming Contest

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a: x)

struct data_max {
  int v{numeric_limits<int>::min()};
  static data_max f(const auto& a, const auto& b) {
    return {max(a.v, b.v)};
  }
};

struct data_sum {
  int v{0};
  static data_sum f(const auto& a, const auto& b) {
    return {a.v + b.v};
  }
};

template<typename T>
struct ST {
  int s;
  vector<T> v;
  ST(int n) : s{n}, v(2 * s) {}
  void update(int l, int r, T elem) {
    for (l += s, r += s; l <= r; (++l) >>= 1, (--r) >>= 1) {
      if (l & 1) v[l] = T::f(v[l], elem);
      if (~r & 1) v[r] = T::f(elem, v[r]);
    }
  }
  T query(int p) {
    T res{};
    for (p += s; p >= 1; p >>= 1)
      res = T::f(res, v[p]);
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

  ST<data_max> st_max(n);
  ST<data_sum> st_sum(n);
  vi qs(q);
  rep(i, 0, q) {
    int l, r, x;
    cin >> l >> r >> x;
    --l; --r;
    st_max.update(l, r, {i});
    st_sum.update(l, r, {1});
    qs[i] = x;
  }
  vi sol(n);
  rep(i, 0, n) {
    auto num_updates = st_sum.query(i).v;
    if (num_updates == 0) sol[i] = a[i];
    else if ((a[i] == 0) ^ (num_updates & 1) == 1) sol[i] = 0;
    else sol[i] = qs[st_max.query(i).v];
  }
  trav(i, sol) cout << i << " "; cout << '\n';
}
