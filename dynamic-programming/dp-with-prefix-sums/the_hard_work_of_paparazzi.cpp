// dp (prefix min optimization - looking more than 2 * r - 2 states behind is guaranteed to be a valid transition since t is STRICTLY increasing)
// https://codeforces.com/contest/1427/problem/C

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

constexpr int MAXS = 998;
constexpr int INF = 1031231234;

auto maxx(auto& a, auto b){a = max(a, b);}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int r, n;
  cin >> r >> n;
  ++n; // add a sentinel (0, 1, 1) at the start
  
  vi t(n), x(n), y(n);
  t[0] = 0; x[0] = 1; y[0] = 1;
  rep(i, 1, n)
    cin >> t[i] >> x[i] >> y[i];

  vi dp(n, -INF);
  vi pmax(n, -INF);
  dp[0] = pmax[0] = 0;
  rep(i, 1, n) {
    rep(j, max(0, i - MAXS + 1), i) {
      auto time = t[i] - t[j];
      auto dist = abs(x[i] - x[j]) + abs(y[i] - y[j]);
      if (dist <= time) maxx(dp[i], dp[j] + 1);
    }
    if (i >= MAXS) maxx(dp[i], pmax[i - MAXS] + 1);
    pmax[i] = i ? max(pmax[i - 1], dp[i]) : dp[i];
  }
  cout << pmax.back() << '\n';
}
