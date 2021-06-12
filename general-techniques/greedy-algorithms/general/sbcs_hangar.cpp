// combo/greedy, nck (pascal's identity)
// https://codeforces.com/gym/102861/problem/H
// 2021 Brazil Subregional

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
using ll = long long;
using ld = long double;
using vi = vector<int>;
using pii = array<int,2>;

constexpr bool dbg = false;

struct edge{int to;};
using graph = vector<vector<edge>>;

const int MAXN = 50 + 5;
ll ways[MAXN + 1][MAXN + 1];

const ll INF = numeric_limits<ll>::max() - 10;

int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  auto nck = [&](int i, int j) {
               if (j < 0 or j > i) return 0LL;
               else return ways[i][j];
             };
  ways[0][0] = 1;
  rep(num, 1, MAXN + 1) {
    rep(chosen, 0, num + 1) {
      ways[num][chosen] = nck(num - 1, chosen) + nck(num - 1, chosen - 1);
    }
  }

  int n, k;
  cin >> n >> k;
  vector<ll> a(n);
  trav(i, a) cin >> i;
  sort(all(a));
  ll A, B;
  cin >> A >> B;
  auto countways = [&](ll limit) {
                     ll rem = limit;
                     vi taken;
                     ll res = 0;
                     for (int i = n - 1; i >= 0; i--) {
                       if (a[i] <= rem) {
                         // ways if don't take i
                         auto num_after = i;
                         auto can_take = k - sz(taken);
                         res += nck(num_after, can_take);
                         // take i
                         taken.PB(i);
                         
                         rem -= a[i];
                       }
                     }
                     if (sz(taken) == k) res++;
                     return res;
                   };
  auto res = countways(B) - countways(A - 1);
  cout << res << '\n';
}
