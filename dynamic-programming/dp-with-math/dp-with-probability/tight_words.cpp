// dp with probabilities
// https://open.kattis.com/problems/tight

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
#define cauto const auto&
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using vi = vector<int>;

struct edge{int to;};
using graph = vector<vector<edge>>;

constexpr auto dbg = false;

const int MAXN = 100;

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  auto dp = vector(MAXN + 1, vector(10, vector<ld>(10 + 1))); // len, last digit, digit lim
  rep(lim, 1, 10 + 1) rep(last, 0, lim) dp[1][last][lim] = 1.0 / lim;
  rep(i, 1, MAXN) {
    rep(lim, 1, 10 + 1) {
      rep(last, 0, lim) {
        for (auto nxt = last - 1; nxt <= last + 1; nxt++) {
          if (nxt < 0 or nxt >= lim) continue;
          dp[i + 1][nxt][lim] += dp[i][last][lim] * (1.0 / lim);
        }
      }
    }
  }
  
  try {
    while (true) {
      int k, n;
      cin >> k >> n;
      if (k == 0 and n == 0) break;
      ++k;
      auto acc = 0.L;
      rep(it, 0, k)
        acc += dp[n][it][k]; // could partial sums ahead of time, but that's ok
      cout << fixed << setprecision(15) << (acc * 100) << '\n';
    }
  } catch(...){}
}
