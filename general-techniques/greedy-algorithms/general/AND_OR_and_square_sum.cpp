// greedy, bitmasks, square sum is maximal when imbalance is maximized, [x, y] = [x | y, x & y] is sum invariant
// https://codeforces.com/contest/1368/problem/D

#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
using vi = vector<int>;
 
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back
 
struct edge{int to;};
using graph = vector<vector<edge>>;
 
const int MAXB = 21;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
 
 
  int n;
  cin >> n;
  vi a(n);
  trav(i, a) cin >> i;
 
  vi cnt(MAXB);
  trav(i, a) {
    rep(bit, 0, MAXB) {
      if (i & (1 << bit)) {
        cnt[bit]++;
      }
    }
  }
 
  ll res = 0;
  rep(i, 0, n) {
    ll num = 0;
    rep(bit, 0, MAXB) {
      if (cnt[bit] > 0) {
        num += (1 << bit);
        cnt[bit]--;
      }
    }
    res += num * num;
  }
  cout << res << '\n';
}
