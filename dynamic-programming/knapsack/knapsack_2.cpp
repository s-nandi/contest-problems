// inverse knapsack (track value in state instead of weight)
// https://atcoder.jp/contests/dp/tasks/dp_e

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)

const ll INF = 1e15;
auto minn(auto& a, auto b){a = min(a, b);}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N, W;
  cin >> N >> W;
  auto total = 0;
  vi w(N), b(N);
  rep(i, 0, N) {
    cin >> w[i] >> b[i];
    total += b[i];
  }
  auto dp = vector<ll>(total + 1, INF); // dp[i] = min weight needed for i benefit
  dp[0] = 0;
  rep(i, 0, N) {
    for (int benefit = total; benefit >= 0; benefit--) {
      if (benefit >= b[i])
        minn(dp[benefit], dp[benefit - b[i]] + w[i]);
    }
  }
  int best = 0;
  rep(i, 1, total + 1)
    if (dp[i] <= W)
      best = i;
  cout << best << '\n';  
}
