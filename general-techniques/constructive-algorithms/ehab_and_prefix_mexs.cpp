// constructive, mex, identify fixed values then fill gaps with increasing values
// https://codeforces.com/contest/1364/problem/C

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

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  vi a(n);
  trav(i, a) cin >> i;

  set<int> unused;
  rep(i, 0, 2 * n + 100) {
    unused.insert(i);
  }
  
  vi b(n, -1);
  rep(i, 0, n) {
    if (a[i] > i + 1) {
      cout << -1 << '\n';
      exit(0);
    }
    if (i == 0 and a[i] != 0) {
      b[0] = 0;
    } else if (i != 0 and a[i] != a[i - 1]) {
      b[i] = a[i - 1];
    }
    if (b[i] != -1 and unused.count(b[i])) unused.erase(b[i]);
  }
  if (unused.count(a.back())) unused.erase(a.back());

  rep(i, 0, n) {
    if (b[i] == -1) {
      b[i] = *unused.begin();
      unused.erase(unused.begin());
    }
  }
  trav(i, b) cout << i << " "; cout << '\n';
}
