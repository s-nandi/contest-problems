// prefix sum, binary search, doubling trick for circular array, any optimal solution uses suffix of some day 
// https://codeforces.com/contest/1358/problem/D

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using vi = vector<int>;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back

struct edge{int to;};
using graph = vector<vector<edge>>;

ll nc2(ll a) {
  return a * (a + 1) / 2;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n; ll x;
  cin >> n >> x;
  vi a(n);
  trav(i,a) cin >> i;
  rep(i, 0, n) {
    a.PB(a[i]);
  }
  vector<ll> b(sz(a));
  rep(i, 0, sz(a)) {
    b[i] = nc2(a[i]);
  }
  vector<ll> psum(sz(a)), bsum(sz(b));
  rep(i, 0, sz(a)) {
    psum[i] = i ? psum[i - 1] + a[i] : a[i];
    bsum[i] = i ? bsum[i - 1] + b[i] : b[i];
  }
  auto sum = [&](int l, int r){return l ? psum[r] - psum[l - 1] : psum[r];};
  auto sum2 = [&](int l, int r){return l ? bsum[r] - bsum[l - 1] : bsum[r];};
  auto best = 0LL;
  rep(i, 0, n) {
    int lo = i, hi = 2 * n - 1;
    while (lo < hi) {
      auto mid = lo + (hi - lo) / 2;
      auto got = sum(i, mid);
      if (got < x) {
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }
    auto total = sum2(i, lo);
    auto extra = sum(i, lo) - x;
    auto actual = total - nc2(extra);
    best = max(best, actual);
  }
  cout << best << '\n';
}
