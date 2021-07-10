// exchange argument (symmetry argument for negative diff elements)
// https://codeforces.com/gym/101242/problem/L
// 2016 World Finals

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
using pii = pair<int,int>;
 
struct edge{int to;};
using graph = vector<vector<edge>>;
 
constexpr auto dbg = false;
 
template <typename T>
int sgn(T a) {return (a > 0) - (a < 0);}
 
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
 
  int n;
  cin >> n;
  vector<pair<ll, ll>> a(n);
  rep(i, 0, n) {
    int v1, v2;
    cin >> v1 >> v2;
    a[i] = pair{v1, v2 - v1};
  }
 
  sort(all(a), [](const auto& d1, const auto& d2) {
                 auto [req1, diff1] = d1;
                 auto [req2, diff2] = d2;
                 if (sgn(diff1) != sgn(diff2)) return diff1 > diff2;
                 else if (sgn(diff1) >= 0) return req1 < req2;
                 else return req1 + diff1 > req2 + diff2;
               });
 
  ll needed = 0;
  ll curr_slack = 0;
  for (const auto& [req, diff]: a) {
    if (req > curr_slack) {
      needed += req - curr_slack;
      curr_slack = req;
    }
    curr_slack += diff;
  }
  if (curr_slack < 0) needed += -curr_slack;
  cout << needed << '\n';
}
