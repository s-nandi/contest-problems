// greedy (bit by bit -- if i-th bit is distributed unevely some player wins otherwise tie), invariant (parity of 1's and of 0's)
// https://codeforces.com/contest/1383/problem/B

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

int mine(int cnt1, int cnt0) {
  int res;
  if (cnt1 % 2 == 0) res = 0;
  else if (cnt0 % 2 == 0) {
    auto each = (cnt1 - 1) / 2;
    if (each % 2 == 0) res = 1;
    else res = -1;
  } else {
    res = 1;
  }
  return res;
}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);
  
  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vi a(n);
    trav(i, a) cin >> i;

    int res = 0; // 1 : first, 0: tie, -1: second
    for (int bit = 30; bit >= 0; bit--) {
      int cnt1 = 0, cnt0 = 0;
      trav(i, a) {
        if (i & (1 << bit)) cnt1++;
        else cnt0++;
      }
      res = mine(cnt1, cnt0);
      if (res != 0) break;
    }
    if (res == 0) cout << "DRAW" << '\n';
    else cout << (res > 0 ? "WIN" : "LOSE") << '\n';
  }
}
