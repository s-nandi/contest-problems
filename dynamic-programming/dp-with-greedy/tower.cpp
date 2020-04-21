// greedy + knapsack, exchange argument, good to prove
// https://atcoder.jp/contests/dp/tasks/dp_x

#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
using vi = vector<int>;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

const int MAXN = 1000;
const int MAXS = 10000;
ll dp[MAXN + 5][2 * MAXS + 5];
 
auto maxx(auto& a, auto b){a = max(a, b);}
void reorder(auto& v, const auto& mapping) {
  auto v2 = v;
  rep(i, 0, sz(v))
    v[i] = v2[mapping[i]];
}
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
 
  int n;
  cin >> n;
  vi w(n), s(n), v(n);
  rep(i, 0, n)
    cin >> w[i] >> s[i] >> v[i];

  vi ind(n);
  iota(all(ind), 0);
  sort(all(ind), [&](int i, int j) {return s[i] + w[i] < s[j] + w[j];});
  reorder(v, ind), reorder(w, ind), reorder(s, ind);
  
  memset(dp, -1, sizeof(dp));
  dp[0][0] = 0;
  rep(i, 0, n) {
    rep(weight, 0, MAXS + 1) {
      if (dp[i][weight] == -1) continue;
      maxx(dp[i + 1][weight], dp[i][weight]);
      if (weight <= s[i])
        maxx(dp[i + 1][weight + w[i]], dp[i][weight] + v[i]);
    }
  }
  auto res = 0LL;
  rep(i, 0, n + 1)
    maxx(res, *max_element(all(dp[i])));
  cout << res << '\n';
}
