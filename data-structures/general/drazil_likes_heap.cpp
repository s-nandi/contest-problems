// greedy, heap, good to prove
// https://codeforces.com/contest/1330/problem/E

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>; 
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define per(i, a, b) for (auto i = (a) - 1; i >= (b); --i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back

void remove(auto& heap, int i, int n) {
  int lc = 2 * i <= n ? heap[2 * i] : 0;
  int rc = 2 * i + 1 <= n ? heap[2 * i + 1] : 0;
  if (lc == 0 and rc == 0) heap[i] = 0;
  else {
    heap[i] = max(lc, rc);
    if (lc > rc) remove(heap, 2 * i, n);
    else remove(heap, 2 * i + 1, n);
  }
}
 
void solve() {
  int h, g;
  cin >> h >> g;
  int n = (1 << h) - 1, m = (1 << g) - 1;
  vi a(n + 1);
  rep(i, 1, n + 1) cin >> a[i];
  vector<vi> children(n + 1);
  vi best(m + 1);
  per(i, n + 1, 1) {
    if (i <= n / 2) {
      children[i].reserve(sz(children[i * 2]) + sz(children[i * 2 + 1]));
      merge(all(children[2 * i]), all(children[2 * i + 1]), back_inserter(children[i]));
    }
    children[i].insert(lower_bound(all(children[i]), a[i]), a[i]); 
    if (i <= m) {
      int lc = 2 * i <= m ? best[2 * i] : 0;
      int rc = 2 * i + 1 <= m ? best[2 * i + 1] : 0;
      best[i] = *upper_bound(all(children[i]), max(lc, rc));
    }
  }
  auto acc = 0LL;
  vi ops;
  rep(i, 1, m + 1) {
    acc += best[i];
    while (a[i] != best[i]) {
      remove(a, i, n);
      ops.PB(i);
    }
  }
  cout << acc << '\n';
  trav(i, ops) cout << i << " "; cout << '\n';
}
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
 
  int T;
  cin >> T;
  while(T--) solve();
}
