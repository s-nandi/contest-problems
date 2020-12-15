// gcd property (gcd(a, x) for any x is either a or <= a / 2)
// https://open.kattis.com/problems/collatzconjecture
// 2017 Benelux Algorithm Programming Contest

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

auto prune(auto& a) {
  decay_t<decltype(a)> res;
  trav(i, a) if (empty(res) or res.back() != i) res.PB(i);
  swap(res, a);
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  vector<ll> a(n);
  trav(i, a) cin >> i;

  prune(a); // constant factor optimization; passes without
  n = sz(a);

  vector<set<ll>> possible(n); // possible[r] = # of possible values w/ intervals [l, r] s.t. l <= r
                               // possible[r] can only have O(lg n) distinct values
  rep(r, 0, n) {
    possible[r].insert(a[r]);
    // extend intervals ending at r-1 to end at r by gcd'ing with a[r]
    if (r) trav(elem, possible[r - 1]) possible[r].insert(gcd(elem, a[r]));
  }
  set<ll> acc;
  rep(r, 0, n) trav(elem, possible[r]) acc.insert(elem);
  cout << sz(acc) << '\n';
}
