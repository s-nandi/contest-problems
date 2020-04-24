// permutation dp, # of permutations that satisfy < and > constraints, dp with partial sums
// https://atcoder.jp/contests/dp/tasks/dp_t

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a);i<(b);++i)
#define all(a) begin(a),end(a)

const int MAXN = 3000;
const int MOD = 1000000007;
int dp[MAXN + 5]; // dp[j] at iteration i = # of ways to place up to i-th element inclusive
                  //                        s.t. last element is the j-th smallest element so far (so 0 <= j <= i)
int psum[MAXN + 5];

auto sadd(auto& a, auto b){
  a += b;
  if (a >= MOD) a -= MOD;
}
template <typename T>
T add(T a, T b){return (a + b) % MOD;}
template <typename T>
T sub(T a, T b){return (a - b + MOD) % MOD;}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  string s;
  cin >> s;

  auto sum = [&](int i, int j){return i ? sub(psum[j], psum[i - 1]) : psum[j];};

  dp[0] = 1;
  rep(i, 1, n) {
    partial_sum(all(dp), begin(psum), add<int>);
    memset(dp, 0, sizeof(dp));
    rep(j, 0, i + 1) {
      if (s[i - 1] == '<')
        sadd(dp[j], sum(0, j - 1));
      else
        sadd(dp[j], sum(j, i - 1));
    }
  }
  auto res = accumulate(all(dp), 0, add<int>);
  cout << res << '\n';
}
