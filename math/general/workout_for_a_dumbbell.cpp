// simulation, math
// https://open.kattis.com/problems/workout
// 2017 East-Central NA Regional

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

const int n = 10;
int a[n]; // jim's usage
int b[n]; // jim's recovery
int u[n];
int r[n];
int T[n]; // T[i] = u[i] + r[i]
int start[n];

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  rep(i, 0, n) {
    cin >> a[i] >> b[i];
  }
  rep(i, 0, n) {
    cin >> u[i] >> r[i] >> initial[i];
  }
  rep(i, 0, n) {
    start[i] = initial[i]; // initial could probably be replaced by start entirely
    T[i] = u[i] + r[i];    
  }
  
  auto update_start = [&](int i, int jim_start) {start[i] = max(start[i], jim_start + a[i]);};
  auto earliest_free = [&](int i, int tm) { // earliest time that station i will be free after or at time 'tm'
                         int res = 0;
                         if (tm < initial[i]) {
                           res = tm;
                         } else {
                           assert(start[i] <= tm);
                           if (start[i] + T[i] <= tm) {
                             auto gap = tm - start[i];
                             auto cycles = gap / T[i];
                             start[i] += cycles * T[i];
                           }
                           assert(start[i] + T[i] > tm and start[i] <= tm);
                           if (tm <= start[i] + u[i]) {
                             res = start[i] + u[i];
                           } else {
                             res = tm;
                           }
                           start[i] += T[i];                    
                         }
                         update_start(i, res);
                         return res;
                       };

  int curr = 0;
  rep(repeat, 0, 3)
    rep(i, 0, n)
    curr = earliest_free(i, curr) + a[i] + b[i];
  curr -= b[n - 1];
  
  cout << curr << '\n';
}
