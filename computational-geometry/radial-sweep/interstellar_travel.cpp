// radial sweep (duplicate events, only process >= 2 * PI for valid ans), acceleration (delta on rate of change)
// https://codeforces.com/gym/102433/problem/J
// 2019 Pacific Northwest Regional

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
 
constexpr ld PI = acos(-1);
 
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(3);
 
  int n;
  cin >> n;
  vector<ld> t, s, a, delta;
  ld base = 0;
  rep(i, 0, n) {
    ld tt, ss, aa;
    cin >> tt >> ss >> aa;
    if (ss > 0) {
      t.PB(tt), s.PB(ss), a.PB(aa);
      delta.PB(min(PI, tt / ss));
      auto weakest = tt - delta.back() * ss;
      base += weakest;
    } else base += tt;
  }
  n = sz(t); 
  auto wrapped = [&](const auto& e) {
                   auto [pos, delta_roc] = e;
                   return pair{pos + 2 * PI, delta_roc};
                 };
  
  vector<pair<ld, ld>> events; // pos, delta rate of change
  rep(i, 0, n) {
    auto e1 = pair{a[i] - delta[i], s[i]};
    auto e2 = pair{a[i], -2 * s[i]};
    auto e3 = pair{a[i] + delta[i], s[i]};
    events.PB(e1);
    events.PB(e2);
    events.PB(e3);
    events.PB(wrapped(e1));
    events.PB(wrapped(e2));
    events.PB(wrapped(e3));
  }
  sort(all(events));
  if (!empty(events)) {
    auto prev_pos = events[0].first;
    auto roc = 0.L;
    auto val = 0.L;
    auto best = 0.L;
    for (const auto& [pos, delta_roc] : events) {
      auto gap = (pos - prev_pos);
      val += gap * roc;
      roc += delta_roc;
      prev_pos = pos;
      if (pos >= 2 * PI) best = max(best, val);
    }
    base += best;
  }
  cout << setprecision(11) << fixed << base << '\n';
}
