// greedy (optimal ordering of paranthetical expressions)
// https://atcoder.jp/contests/abc167/tasks/abc167_f

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<string> a(n);
  trav(i, a) cin >> i;

  using state = tuple<int, int, int, int>; // left close, right open, total diff, len
  vector<state> b(n);
  rep(i, 0, n) {
    int cnt = 0, lc = 0, ro = 0;
    trav(c, a[i])
      lc = max(lc, cnt += (c == ')') ? 1 : -1);
    reverse(all(a[i])); cnt = 0;
    trav(c, a[i])
      ro = max(ro, cnt += (c == ')') ? -1 : 1);
    b[i] = {lc, ro, ro - lc, sz(a[i])};
  }
  sort(all(b), [&](state s1, state s2) {
                 auto [lc1, ro1, delta1, len1] = s1;
                 auto [lc2, ro2, delta2, len2] = s2;
                 if (delta1 > 0 and delta2 <= 0) {
                   return true;
                 } else if (delta1 <= 0 and delta2 > 0) {
                   return false;
                 } else if (delta1 <= 0 and delta2 <= 0){
                   return tie(ro2, delta1) < tie(ro1, delta2);
                 } else if (delta1 > 0 and delta2 > 0) {
                   return tie(lc1, delta2) < tie(lc2, delta1);
                 } else assert(false);
               });
  bool good = true;
  int have = 0;
  for (const auto& [lc, ro, diff, len]: b) {
    good &= lc <= have;
    have += diff;
  }
  good &= have == 0;
  cout << (good ? "Yes" : "No") << '\n';
}
