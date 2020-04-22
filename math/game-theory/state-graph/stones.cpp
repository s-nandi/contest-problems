// game theory (win/lose state graph)
// https://atcoder.jp/contests/dp/tasks/dp_k

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define rep(i, a, b) for(auto i=(a); i<(b); ++i)
#define trav(a, x) for(auto& a: x)

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;
  vi a(n);
  trav(i, a) cin >> i;
  vi dp(k + 1); // 0 -> lose, 1 -> win
  rep(i, 1, k + 1)
    trav(step, a) if (step <= i)
      dp[i] |= (1 - dp[i - step]);
  cout << (dp[k] ? "First" : "Second") << '\n';
}
