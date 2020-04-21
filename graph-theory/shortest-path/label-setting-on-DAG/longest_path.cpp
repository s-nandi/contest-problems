// longest path on DAG
// https://atcoder.jp/contests/dp/tasks/dp_g

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define PB push_back

struct edge{int to;};
using graph = vector<vector<edge>>;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;
  graph g(n);
  vi ideg(n);
  rep(i, 0, m) {
    int u, v;
    cin >> u >> v;
    --u; --v;
    g[u].PB({v});
    ideg[v]++;
  }
  vi dp(n);
  queue<int> q;
  rep(i, 0, n) if (ideg[i] == 0)
    q.push(i);
  auto relax = [&](int i) {
                 trav(e, g[i]) {
                   dp[e.to] = max(dp[e.to], dp[i] + 1);
                   if (--ideg[e.to] == 0)
                     q.push(e.to);
                 }
               };
  while (!q.empty()) {
    int i = q.front();
    q.pop();
    relax(i);
  }
  cout << *max_element(all(dp)) << '\n';
}
