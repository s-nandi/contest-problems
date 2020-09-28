// dijkstra (multi source)
// https://codeforces.com/contest/938/problem/D

#include <bits/stdc++.h>
using namespace std;

constexpr auto dbg = true;

#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using vi = vector<int>;

struct edge{int to; ll w;};
using graph = vector<vector<edge>>;

using state = tuple<ll, int>; // sh. distance, node
constexpr auto INF = (ll) 1e18;

template <typename T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;

auto minn(auto& a, auto b){return b < a ? a = b, true : false;}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m;
  graph g(n);
  rep(it, 0, m) {
    int u, v; ll w;
    cin >> u >> v >> w;
    --u; --v;
    g[u].PB({v, w});
    g[v].PB({u, w});
  }
  vector<ll> a(n);
  trav(i, a) cin >> i;
  
  min_queue<state> q;
  vi vis(n);
  vector<ll> dist(n, INF);
  rep(i, 0, n) {
    dist[i] = a[i];
    q.push({dist[i], i});
  }
  while (!empty(q)) {
    auto [d, i] = q.top(); q.pop();
    if (vis[i]) continue;
    vis[i] = true;
    trav(e, g[i]) if (minn(dist[e.to], dist[i] + 2 * e.w))
      q.push({dist[e.to], e.to});
  }
  trav(i, dist) cout << i << " "; cout << '\n';
}
