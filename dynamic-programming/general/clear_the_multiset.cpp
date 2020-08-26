// dp on partitions, greedy (all vertical [operation 2] operations can be all done at the start, dp finds the optimal horizontal ops along w/ vertical ops for keeping an interval at the same height)
// https://codeforces.com/contest/1400/problem/E

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

auto minn(auto& a, auto b){a = min(a, b);}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);
  
  int n;
  cin >> n;
  vi a(n);
  trav(i, a) cin >> i;
  a.insert(begin(a), 0);
  n = sz(a);

  constexpr auto INF = 1031231234;
  auto dp = vector(n, vi(n, INF)); // [i][j] => prefix upto i, last block reduced to a[j]
  dp[0][0] = 0;
  rep(i, 1, n) {
    rep(j, 0, i) {
      if (a[j] <= a[i]) {
        auto cost_continue = a[i] != a[j];
        minn(dp[i][j], dp[i - 1][j] + cost_continue); // continue previous partition
      }
      auto cost_new = a[j] >= a[i] ? 0 : a[i] - a[j];
      minn(dp[i][i], dp[i - 1][j] + cost_new); // create new partition; if higher than previous partition, more operations needed, otherwise, already accounted for
    }
  }
  cout << *min_element(all(dp.back())) << '\n';
}
