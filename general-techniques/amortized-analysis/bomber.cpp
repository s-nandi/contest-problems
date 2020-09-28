// greedy (sol is either max_row + max_col or max_row+max_col-1), amortized (nested loop can only run m times before the condition is true)
// https://atcoder.jp/contests/abc176/tasks/abc176_e

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

const int MAXC = 300'000;

void trim_duplicate(auto& v) {
  sort(all(v));
  v.erase(unique(all(v)), end(v));
}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int r, c, m;
  cin >> r >> c >> m;

  vi xs(m), ys(m);
  vi xcnt(MAXC), ycnt(MAXC);
  vector<pii> pts(m);
  rep(i, 0, m) {
    cin >> xs[i] >> ys[i];
    --xs[i]; --ys[i];
    xcnt[xs[i]]++;
    ycnt[ys[i]]++;
    pts[i] = {xs[i], ys[i]};
  }
  auto max_x = *max_element(all(xcnt));
  auto max_y = *max_element(all(ycnt));
  sort(all(pts));

  vi saturated_x, saturated_y;
  rep(i, 0, m) {
    if (xcnt[xs[i]] == max_x) saturated_x.PB(xs[i]);
    if (ycnt[ys[i]] == max_y) saturated_y.PB(ys[i]);
  }
  trim_duplicate(saturated_x);
  trim_duplicate(saturated_y);

  auto best = max_x + max_y;
  bool reached = false;
  trav(x, saturated_x) trav(y, saturated_y) {
    if (!binary_search(all(pts), pair{x, y})) {reached = true; break;}
  }
  cout << (reached ? best : best - 1) << '\n';
}
