// convex hull trick (parabolic functions)
// https://atcoder.jp/contests/dp/tasks/dp_z

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define PB push_back

struct equation {
  ll m, b; // y = m * x + b
  ll y(ll x0){return m * x0 + b;}
  ld intersect(equation o){return (ld) (o.b - b) / (m - o.m);}
};

struct CHT {
  deque<equation> hull;
  void add(const equation &e) {
    while (hull.size() > 1 and hull.rbegin()[1].intersect(e) < hull.rbegin()[1].intersect(hull.rbegin()[0]))
      hull.pop_back();
    hull.PB(e);
  }
  ll get(ll x0) {
    if(hull.empty()) return 0; // PS
    while (hull.size() > 1 and hull[0].y(x0) > hull[1].y(x0))
      hull.pop_front();
    return hull[0].y(x0);
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n; ll c;
  cin >> n >> c;
  vector<ll> a(n);
  trav(i, a) cin >> i;

  CHT cht;
  vector<ll> dp(n);
  cht.add({-2 * a[0], dp[0] + a[0] * a[0]});
  rep(i, 1, n) {
    dp[i] = cht.get(a[i]) + c + a[i] * a[i];
    cht.add({-2 * a[i], dp[i] + a[i] * a[i]});
  }
  cout << dp[n - 1] << '\n';
}
