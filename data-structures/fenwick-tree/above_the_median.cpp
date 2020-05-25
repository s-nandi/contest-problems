// median to range sum reduction, fenwick tree, # of subarrays s.t. median is >= x
// http://usaco.org/index.php?page=viewproblem2&cpid=91
// Note: Have to manually test with USACO's test data

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back

struct FT {
  vi v;
  FT(int n) : v(n) {}
  void update(int pos, int val) {
    for (; pos < sz(v); pos |= (pos + 1)) v[pos] += val;
  }
  ll query(int l, int r){return l ? query(r) - query(l - 1) : query(r);}
  ll query(int p) {
    ll acc = 0;
    for (++p; p; p &= (p - 1)) acc += v[p - 1];
    return acc;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  freopen("median.in", "r", stdin);
  freopen("median.out", "w", stdout);

  int n, x;
  cin >> n >> x;
  vi a(n), b(n);
  rep(i, 0, n) {
    cin >> a[i];
    b[i] = a[i] >= x ? 1 : -1;
  }

  ll res = 0;
  int acc = 0;
  FT ft(2 * n + 1);
  int offset = n; // acc can be in range [-n, n]
  ft.update(0 + offset, 1);
  rep(i, 0, n) {
    acc += b[i];
    auto delta = ft.query(0, acc + offset);
    res += delta;
    ft.update(acc + offset, 1);
  }
  cout << res << '\n';
}
