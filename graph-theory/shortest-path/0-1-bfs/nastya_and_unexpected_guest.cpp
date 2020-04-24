// shortest path(0-1 BFS), expanded graph (multiplying each node by time)
// https://codeforces.com/contest/1340/problem/C

#include <bits/stdc++.h>
using namespace std;
 
using vi = vector<int>;
using ll = long long;
 
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
 
const int MAXN = 10000;
const int MAXT = 1000;
const int INF = 1031231234;
using state = pair<int, int>; // node, rem time
int dist[MAXN + 5][MAXT + 5]; // dist[i][j] = # of red lights to get to node i w/ j rem time before next red light
 
const auto dx = vector{-1, 1};
auto minn(auto& a, auto b){
  if (b < a) {a = b; return true;}
  return false;
}
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
 
  int n, m;
  cin >> n >> m;
  vi a(m);
  trav(i, a) cin >> i;
  sort(all(a));
  int g, r;
  cin >> g >> r;
 
  rep(i, 0, MAXN) rep(j, 0, MAXT + 1) dist[i][j] = INF;
 
  deque<state> q;
  q.push_back({0, g});
  dist[0][g] = 0;
  while (!q.empty()) {
    auto [i, rem] = q.front();
    q.pop_front();
    rep(k, 0, 2) {
      auto ni = i + dx[k];
      if (ni < 0 or ni >= m) continue;
      auto nrem = rem - abs(a[i] - a[ni]);
      if (nrem < 0) continue;
      if (minn(dist[ni][nrem], dist[i][rem])) {
        q.push_front({ni, nrem});
      }
    }
    if (rem == 0 and minn(dist[i][g], dist[i][rem] + 1)) {
      q.push_back({i, g});
    }
  }
  auto best = INF;
  rep(rem, 0, g + 1) {
    auto possible = (ll) dist[m - 1][rem] * (g + r) + (g - rem);
    minn(best, possible);
  }
  cout << (best != INF ? best : -1) << '\n';
}
