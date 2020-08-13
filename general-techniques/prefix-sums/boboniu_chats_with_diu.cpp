// greedy, prefix sums, finding canonical form for solution (front of list is < m, then alternate 1 > m and d < m's until < m's are exhausted)
// https://codeforces.com/contest/1394/problem/A

#include <bits/stdc++.h>
using namespace std;
 
#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using vi = vector<int>;
 
struct edge{int to;};
using graph = vector<vector<edge>>;

auto ceildiv(auto a, auto b) {return (a + b - 1) / b;}
 
auto numtaken(int n, int d) {
  return ceildiv(n, d + 1);
}
 
int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);
 
  int n, d, m;
  cin >> n >> d >> m;
  vi a(n);
  trav(i, a) {cin >> i;}
 
  deque<ll> bg, sm;
  trav(i, a) {
    if (i > m) bg.PB(i);
    else sm.PB(i);
  }
  sort(all(bg), greater<>{});
  sort(all(sm), greater<>{});
  vector<ll> ps_bg(sz(bg) + 1);
  partial_sum(all(bg), begin(ps_bg) + 1);
  vector<ll> ps_sm(sz(sm) + 1);
  partial_sum(all(sm), begin(ps_sm) + 1);
 
  auto maxtaken = numtaken(n, d);
  auto maxbigger = min(sz(bg), maxtaken);
  
  auto best = 0LL;
  rep(leadingsmaller, 0, sz(sm) + 1) {
    auto curr = 0LL;
    curr += ps_sm[leadingsmaller];
    auto takenbigger = min(numtaken(sz(bg) + sz(sm) - leadingsmaller, d), sz(bg));
    curr += ps_bg[takenbigger];
    best = max(curr, best);
  }
  cout << best << '\n';
}
