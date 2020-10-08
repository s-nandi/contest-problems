// permutation dp (tracking position of last element, prefix sums optimization), precompute answers before queries
// https://open.kattis.com/problems/permutationdescent
// 2016 Greater NY Regional
// Note: There is a faster N^2 solution that loops in order from the smallest element to the largest element, and the state is [i][v]
//       representing placing the ith smallest number and having v prior descents => v positions will keep # of descents the same (ex. 3 1 => 3 4 1)
//       while the remaining i - v positions will increase the # of descents by 1 (ex. 2 5 => 2 6 5)

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

const auto MOD = 1001113;
auto add(auto a, auto b){auto res = a + b; return res < MOD ? res : res - MOD;}
auto sub(auto a, auto b){auto res = a - b; return res >= 0 ? res : res + MOD;}
auto sadd(auto& a, auto b){a = add(a, b);}

const int MAXN = 100 + 5;

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  auto dp = vector(MAXN + 1, vector(MAXN, vi(MAXN))); // i, # descents, 0-indexed pos of last number
  auto psum = dp;

  auto sum = [&](int i, int desc, int l, int r) {
               if (i < 0 or desc < 0) return 0;
               if (l > r) return 0;
               return l ? sub(psum[i][desc][r], psum[i][desc][l - 1]) : psum[i][desc][r];
             };
  
  dp[1][0][0] = 1;
  rep(i, 2, MAXN + 1) {
    rep(desc, 0, MAXN) {
      rep(pos, 0, MAXN) {
        psum[i - 1][desc][pos] = add(pos ? psum[i - 1][desc][pos - 1] : 0, dp[i - 1][desc][pos]);
      }
    }
    rep(desc, 0, i) {
      rep(pos, 0, i) {
        auto& curr = dp[i][desc][pos];
        sadd(curr, sum(i - 1, desc - 1, pos, MAXN - 1));
        sadd(curr, sum(i - 1, desc, 0, pos - 1));
      }
    }
  }

  int T;
  cin >> T;
  while(T--) {
    int tnum, n, v;
    cin >> tnum >> n >> v;
    cout << tnum << " " << sum(n, v, 0, n - 1) << '\n';
  }
}
