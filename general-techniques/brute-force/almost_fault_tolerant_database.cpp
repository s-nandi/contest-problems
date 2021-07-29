// backtracking, backtracking with constant max depth is O(1) * cost of a single recursive call
// https://codeforces.com/contest/1492/problem/E

#include <bits/stdc++.h>
using namespace std;
 
#define rep(i,a,b) for(auto i=(a);i<(b);++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back
using ll = long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int,int>;
 
constexpr auto dbg = false;
 
struct edge{int to;};
using graph = vector<vector<edge>>;
 
const int MAXDIFF = 2;
 
auto getdiffs(const vi& a, const vi& b) {
  vi res;
  rep(i, 0, sz(a)) if (a[i] != b[i]) res.PB(i);
  return res;
}

void yes(const auto& a) {
  cout << "Yes" << '\n';
  trav(i, a) cout << i << " "; cout << '\n';
  exit(0);
}

void recur(auto& a, int changes) {
  if (changes > MAXDIFF) return;
  rep(i, 0, sz(a)) {
    auto diffs = getdiffs(a[0], a[i]);
    if (sz(diffs) > 2 * MAXDIFF) return;
    if (sz(diffs) > MAXDIFF) {
      trav(pos, diffs) {
        auto old = exchange(a[0][pos], a[i][pos]);
        recur(a, changes + 1);
        a[0][pos] = old;
      }
      return;
    }
  }
  yes(a[0]);
}
 
int32_t main() {
  cin.tie(0)->sync_with_stdio(0);
 
  int n, m;
  cin >> n >> m;
  auto a = vector(n, vi(m));
  trav(r, a) trav(i, r) cin >> i;
  recur(a, 0);
  cout << "No" << '\n';
}
