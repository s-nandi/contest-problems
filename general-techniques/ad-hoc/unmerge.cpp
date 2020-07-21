// adhoc (find max element -> suffix from this element onward must belong to 1 component), dp (knapsack/subset sum)
// https://codeforces.com/contest/1381/problem/B

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

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vi a(2 * n);
    trav(i, a){cin >> i; --i;}
    
    vi pos(2 * n);
    rep(i, 0, sz(a))
      pos[a[i]] = i;
    
    vi sizes;
    vi vis(2 * n);
    for (int i = sz(a) - 1; i >= 0; i--) {
      auto p = pos[i];
      int s = 0;
      rep(j, p, sz(a)) {
        if (vis[j]) break;
        vis[j] = true;
        s++;
      }
      if (s) sizes.PB(s);
    }

    vi dp(2 * n + 1);
    dp[0] = true;
    trav(s, sizes) {
      for (int i = 2 * n; i >= 0; i--){
        if (dp[i] and i + s <= 2 * n) {
          dp[i + s] = true;
        }
      }
    }
    cout << (dp[n] ? "YES" : "NO") << '\n';
  }
}
