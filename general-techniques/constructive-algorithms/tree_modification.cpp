// constructive, show  min bound w/ invariant on 2-coloring => each step reduces size of a color by 1, fix root and let it be A and greedily choose nodes 2 dist away to be C
// https://codeforces.com/contest/1375/problem/G

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

void dfs(graph& g, int i, auto& visited, auto& colors, int col = 0) {
  if (visited[i]) return;
  visited[i] = true;
  colors[i] = col;
  trav(e, g[i]) if (!visited[e.to])
    dfs(g, e.to, visited, colors, 1 - col);
}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;
  graph g(n);
  rep(it, 0, n - 1) {
    int u, v;
    cin >> u >> v;
    --u; --v;
    g[u].PB({v});
    g[v].PB({u});
  }
  vi visited(n);
  vi colors(n);
  dfs(g, 0, visited, colors);
  int n0 = 0, n1 = 0;
  rep(i, 0, n) {
    n0 += (colors[i] == 0);
    n1 += (colors[i] == 1);
  }
  auto res = min(n0, n1) - 1;
  cout << res << '\n';
}
