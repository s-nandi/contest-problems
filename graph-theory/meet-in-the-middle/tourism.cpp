// meet in the middle (fix even nodes), backtracking
// https://codeforces.com/contest/1314/problem/D

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

const ll INF = 1e15;

ll cheapest(const auto& len2, auto& used, int i, int j) {
  for (const auto& [dist, middle]: len2[i][j]) {
    if (!used[middle]) // triggers <= 5 times since sz(evens) <= 5
      return dist;
  }
  return INF;
}

ll solve(const auto& len2, auto& used, int k, auto& evens) {
  if (2 * sz(evens) == k) {
    ll delta = 0;
    rep(i, 0, sz(evens)) {
      int pi = i ? i - 1 : sz(evens) - 1;
      delta += cheapest(len2, used, evens[pi], evens[i]);
    }
    return delta;
  } else {
    auto best = INF;
    rep(i, 0, sz(len2)) {
      evens.PB(i);
      used[i]++;
      best = min(best, solve(len2, used, k, evens));
      used[i]--;
      evens.pop_back();
    }
    return best;
  }
}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n, k;
  cin >> n >> k;
  auto dist = vector(n, vi(n));
  trav(r, dist) trav(e, r) cin >> e;
  rep(i, 0, n) dist[i][i] = INF;

  auto len2 = vector(n, vector(n, vector<pii>{})); // best[i][j] = {(dist, middle)...}
  rep(i, 0, n) rep(j, 0, n) {
    rep(k, 0, n)
      len2[i][j].PB({dist[i][k] + dist[k][j], k});
    sort(all(len2[i][j]));
  }

  vi evens = {0};
  vi used(n);
  auto res = solve(len2, used, k, evens);
  cout << res << '\n';
}
