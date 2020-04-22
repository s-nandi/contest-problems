// dp with data structures, max value increasing subsequence, invariant maintaining
// https://atcoder.jp/contests/dp/tasks/dp_q

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int, long long>;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  vi h(n), a(n);
  trav(i, h) cin >> i;
  trav(i, a) cin >> i;
  set<ii> best; // maintain (h_i, v_i) s.t. i < j => h_i < h_j and v_i < v_j
                // since if h_i < h_j and v_i > v_j, element j is redundant
  best.insert({0, 0});
  rep(i, 0, n) {
    auto pval = (--best.upper_bound({h[i], 0})) -> second;
    auto it = best.insert({h[i], pval + a[i]}).first;
    if (it != begin(best) and prev(it) -> second >= it -> second)
      best.erase(it); // i-th element is redundant
    else {
      while (next(it) != end(best) and it -> second >= next(it) -> second)
        best.erase(next(it)); // i-th element makes something bigger redundant
    }
  }
  auto res = 0LL;
  trav(elem, best)
    res = max(res, elem.second);
  cout << res << '\n';
}
