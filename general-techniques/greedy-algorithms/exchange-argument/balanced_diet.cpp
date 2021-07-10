// task scheduling (non trivial release/deadline), track earliest/latest time to pick t-th instance of the i-th sweet
// https://codeforces.com/gym/101242/problem/A
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

constexpr auto dbg = true;

ll ceildiv(ll a, ll b){return (a + b - 1) / b;}
ll floordiv(ll a, ll b){return a / b;}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;
  vi a(n);
  trav(i, a) cin >> i;
  ll tot = accumulate(all(a), 0LL);
  
  vi b(k);
  trav(i, b) {cin >> i; --i;}

  auto intervalfor = [&](int i, int t) { // ret. (exclusive, exclusive) range for t-th instance of task i
                       auto lo = floordiv(tot * (t - 1), a[i]);
                       auto hi = ceildiv(tot * (t + 1), a[i]);
                       return pair{lo, hi};
                     };

  auto release = [&](int i, int t) { // Earliest time to go from t to t + 1
                   auto curr_end = intervalfor(i, t).second;
                   auto next_start = intervalfor(i, t + 1).first + 1;
                   return min(next_start, curr_end);
                 };
  auto deadline = [&](int i, int t) { // Latest time to go from t to t + 1
                    auto curr_end = intervalfor(i, t).second;
                    auto next_start = intervalfor(i, t + 1).first + 1;
                    return max(curr_end, next_start);
                  };

  vi occ(n);
  trav(i, b) occ[i]++;

  set<tuple<ll, int>> releases, deadlines; // { (time, task index) }
  rep(i, 0, n) {
    assert(release(i, occ[i]) <= deadline(i, occ[i]));
    releases.insert({release(i, occ[i]), i});
  }

  int upto = k + tot;
  int res = upto;
  rep(steps, k + 1, upto + 1) {
    while (!empty(releases)) {
      const auto [tm, i] = *begin(releases);
      if (tm <= steps) {
        releases.erase(begin(releases));
        deadlines.insert({deadline(i, occ[i]), i});
      } else break;
    }

    if (empty(deadlines)) { res = steps - 1; break; } // apparently not necessary, see editorial
    
    const auto [tm, i] = *begin(deadlines);
    if (tm < steps) { res = tm - 1; break; }
    deadlines.erase(begin(deadlines));
    occ[i]++;
    releases.insert({release(i, occ[i]), i});
  }
  if (res >= upto) cout << "forever" << '\n';
  else cout << (res - k) << '\n';
}
