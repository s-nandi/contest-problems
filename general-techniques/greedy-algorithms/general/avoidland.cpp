// greedy, pawns end up occupying rows 1..n, cols 1..n and we can always avoid collisions -- greedily put leftmost pawn on 1, next left pawn on 2, etc, cols and rows are independent
// https://open.kattis.com/problems/avoidland
// 2014 Northeast NA Regional

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
#define cauto const auto&
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using vi = vector<int>;

struct edge{int to;};
using graph = vector<vector<edge>>;

constexpr auto dbg = true;

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;
  vi xs(n), ys(n);
  rep(i, 0, n) cin >> xs[i] >> ys[i];
  sort(all(xs));
  sort(all(ys));
  vi coord(n);
  iota(all(coord), 1);
  ll res = 0;
  rep(i, 0, n) {
    res += abs(xs[i] - coord[i]);
    res += abs(ys[i] - coord[i]);
  }
  cout << res << '\n';
}
