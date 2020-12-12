// cycle detection, casework, math
// https://codeforces.com/contest/1461/problem/E

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

auto ceildiv(auto a, auto b){return (a + b - 1) / b;}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ll k, l, r, t, x, y;
  cin >> k >> l >> r >> t >> x >> y;

  bool ok = true;
  if (y < x) {
    if (k + y <= r) k += y;
    if (k - x < l) ok = false;
    else {
      k -= x, t--;
      
      auto slack = k - l;
      auto perday = x - y;
      auto ndecs = ceildiv(slack + 1, perday); // # of days till < l ['slack+1' needed instead of 'slack' so we go < l instead of <= l]
      ok = t < ndecs;
    }
  } else {
    auto add_at = r - y;
    if (add_at - l >= x) {
      ok = true;
    } else {
      vi vis(x);
      while (t > 0) { // avoid multiple +y's without any -x's in between via the 'add_ad - l >= x' case
                      // can only have multiple +y's in a row if l + y < r - y => r - y - l > y => r - y - l > x since y >= x in this branch
        ll ndecs = 0;
        if (k > add_at) { // -x till <= add_at threshold
          auto slack = k - add_at;
          ndecs = min(t, ceildiv(slack, x));
        }
        k -= ndecs * x;
        t -= ndecs;
        
        if (k < l) {ok = false; break;}
        if (vis[k % x]) break; // since we can't have multiple +y's in a row, checking visitedness modulo x is safe
        vis[k % x] = true;
        k += y;
      }
    }
  }
  cout << (ok ? "Yes" : "No") << '\n';
}
