// maximizing convex function (Note: lots of similar greedies fail, why does this one work?)
// https://codeforces.com/contest/1336/problem/B

#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
using vi = vector<int>;
 
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

constexpr ll INF = 3 * 1e18; 
ll weight(ll a, ll b, ll c) {
  return (b - a) * (b - a) + (c - b) * (c - b) + (a - c) * (a - c);
}
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
 
  int T;
  cin >> T;
  while(T--) {
    int s[3];
    rep(i, 0, 3) cin >> s[i];
    vi a[3];
    rep(i, 0, 3) {
      a[i].resize(s[i]);
      trav(elem, a[i]) cin >> elem;
      sort(all(a[i]));
    }
    auto best = INF;
    rep(it, 0, 3) {
      auto& x = a[it];
      auto& y = a[(it + 1)%3];
      auto& z = a[(it + 2)%3];
      auto max_smaller = [](const auto& cont, auto elem){return lower_bound(all(cont), elem) - begin(cont) - 1;};
      auto good = [](int ind, const auto& cont){return ind >= 0 and ind < sz(cont);};
      auto closer = [](auto a, auto b, auto target){return abs(a - target) < abs(b - target);};
      rep(yind, 0, sz(y)) {
        auto xlo = max_smaller(x, y[yind]);
        auto zlo = max_smaller(z, y[yind]);
        int xind = xlo, zind = zlo;
        rep(x_delta, -1, 2) rep(z_delta, -1, 2) {
          auto xpos = xlo + x_delta;
          auto zpos = zlo + z_delta;
          if (good(xpos, x) and (!good(xind, x) or closer(x[xpos], x[xind], y[yind])))
            xind = xpos;
          if (good(zpos, z) and (!good(zind, z) or closer(z[zpos], z[zind], y[yind])))
            zind = zpos;
        }
        auto possible = weight(y[yind], z[zind], x[xind]);
        best = min(best, possible);
      }
    }
    cout << best << '\n';
  }
}
