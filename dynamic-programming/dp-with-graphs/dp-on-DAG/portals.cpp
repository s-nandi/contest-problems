// dp on DAG (and partial sum), only take backedge when at last possible edge
// https://codeforces.com/contest/1271/problem/D

#include <bits/stdc++.h>
using namespace std;

struct edge{int to;};
using graph = vector<vector<edge>>;

constexpr auto MAXS = 5000;
constexpr auto INF = 1031231234;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m, k;
  cin >> n >> m >> k;
  vector<int> a(n), b(n), c(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i] >> b[i] >> c[i];
  }
  
  graph g(n);
  vector<int> indegree(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    --u; --v;
    g[u].push_back({v});
    indegree[v]++;
  }
  for (int i = 0; i < n; i++) {
    g[i].push_back({i});
    indegree[i]++;
  }
    
  auto dp = vector(n + 1, vector<int>(MAXS + 1, -INF));
  dp[0][k] = 0;
  for (int i = 0; i < n; i++) {
    for (auto [to]: g[i]) {
      --indegree[to];
    }
      
    for (int k = a[i]; k <= MAXS; k++) {
      if (dp[i][k] == -INF) continue;
      auto have = k + b[i];
      vector<int> benefits;
      for (auto [to]: g[i]) {
        if (indegree[to] == 0) {
          benefits.push_back(c[to]);
        }
      }
      sort(begin(benefits), end(benefits), greater<>{});
      partial_sum(begin(benefits), end(benefits), begin(benefits));
	
      auto need = i + 1 < n ? a[i + 1] : 0;
      dp[i + 1][have] = max(dp[i + 1][have], dp[i][k]);
      for (int j = 0; j < min((int) benefits.size(), have - need); j++) {
        auto possible = dp[i][k] + benefits[j];
        dp[i + 1][have - (j + 1)] = max(dp[i + 1][have - (j + 1)], possible);
      }
    }
  }
    
  auto res = *max_element(begin(dp[n]), end(dp[n]));
  if (res == -INF) {
    cout << -1 << '\n';
  } else {
    cout << res << '\n';
  }
}
