// greedy, amortized complexity, solving in reverse (food w/ max slack goes at back)
// https://codeforces.com/contest/1369/problem/E

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;
using ld = long double;
using ii = pair<int, int>;

#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back

struct edge{int to;};
using graph = vector<vector<edge>>;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;
  vi a(n);
  trav(i, a) cin >> i;
  vector<ii> b(m);
  trav(i, b) {
    cin >> i.first >> i.second;
    --i.first; --i.second;
  }
  
  vector<vi> friends(n);
  rep(i, 0, m) {
    auto [u, v] = b[i];
    friends[u].PB(i);
    friends[v].PB(i);
  }
  auto slack = a;
  for (auto [u, v]: b) {
    --slack[u], --slack[v];
  }
  priority_queue<ii> byslack;
  rep(i, 0, n)
    byslack.push({slack[i], i});

  vi processed(n), vis(m), sol;
  while (!empty(byslack)) {
    auto [_, category] = byslack.top(); byslack.pop();
    if (processed[category]) continue;
    if (slack[category] < 0) break;
    processed[category] = true;
    map<int, int> delta;
    trav(i, friends[category]) if (!vis[i]) {
      vis[i] = true;
      sol.PB(i);
      auto ocat = (category == b[i].first) ? b[i].second : b[i].first;
      delta[ocat]++;
    }
    for (const auto& [cat, diff]: delta) {
      byslack.push({slack[cat] += diff, cat});
    }
  }
  if (sz(sol) < m) cout << "DEAD" << '\n';
  else {
    cout << "ALIVE" << '\n';
    trav(i, vector(rbegin(sol), rend(sol)))
      cout << (i + 1) << " "; cout << '\n';
  }
}
