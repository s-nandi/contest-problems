// interval dp, greedy (>=1 col in range must be filled as much as possible), col k can be filled in dp[l, r] if block containing k is contained in [l, r]
// https://codeforces.com/contest/1372/problem/E
// Note: Can be done in M^3 + M^2 * N time with inverted prefix sums

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

const int INF = 1031231234;
void maxx(auto& a, auto b){a = max(a, b);}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m;
  auto comp = vector(n, vi(m));
  vector<vi> lo(n), hi(n);
  rep(i, 0, n) {
    int cnt;
    cin >> cnt;
    rep(it, 0, cnt) {
      int l, r;
      cin >> l >> r;
      --l; --r;
      lo[i].PB(l);
      hi[i].PB(r);
      rep(j, l, r + 1)
        comp[i][j] = it;
    }
  }

  auto dp = vector(m, vi(m));
  rep(len, 1, m + 1) {
    rep(l, 0, m - len + 1) {
      auto r = l + len - 1;
      rep(k, l, r + 1) {
        int score = 0;
        rep(i, 0, n) {
          auto cmp = comp[i][k];
          if (lo[i][cmp] >= l and hi[i][cmp] <= r)
            score++;
        }
        auto lhs = k > l ? dp[l][k - 1] : 0;
        auto rhs = k < r ? dp[k + 1][r] : 0;
        maxx(dp[l][r], score * score + lhs + rhs);
      }
    }
  }
  auto res = dp[0][m - 1];
  cout << res << '\n';
}
