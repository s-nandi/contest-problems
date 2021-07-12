// greedy (optimal merge [i, j] at average[i, j]), monotone stack of average (invariant)
// https://open.kattis.com/problems/accesspoints
// 2018 Northwestern Europe Regional

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a);i<(b);++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back

using ll = long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<ll,ll>;

struct edge{int to;};
using graph = vector<vector<edge>>;

constexpr auto dbg = false;

ld solve(int n, const auto& a) {
  vector<pii> res; // { (sum, count) }
  auto smaller_avg = [&](const pii& f1, const pii& f2) {
                       auto [num1, denom1] = f1;
                       auto [num2, denom2] = f2;
                       return (ll) num1 * denom2 < (ll) num2 * denom1;
                     };
  auto merge = [&](const pii& f1, const pii& f2) {
                 auto [sum1, count1] = f1;
                 auto [sum2, count2] = f2;
                 return pii{sum1 + sum2, count1 + count2};
               };

  res.PB(pii{a[0], 1});
  rep(i, 1, n) {
    pii curr = {a[i], 1};
    while (!empty(res) and smaller_avg(curr, res.back())) {
      curr = merge(curr, res.back());
      res.pop_back();
    }
    res.PB(curr);
  }
  
  vector<ld> b(n);
  {
    int it = 0;
    for (const auto& [sum, cnt]: res) {
      rep(i, 0, cnt) b[it++] = (ld) sum / cnt;
    }
  }
  ld cost = 0;
  rep(i, 0, n) cost += (b[i] - a[i]) * (b[i] - a[i]);
  return cost;
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  vi xs(n), ys(n);
  rep(i, 0, n) {
    cin >> xs[i] >> ys[i];
  }
  auto costx = solve(n, xs);
  auto costy = solve(n, ys);
  auto res = costx + costy;
  cout << fixed << setprecision(10) << res << '\n';
}
