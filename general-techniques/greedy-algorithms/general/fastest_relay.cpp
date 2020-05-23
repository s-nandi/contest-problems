// greedy (at most 4 best for a particular category might be useful), backtracking
// https://codesprintla20-team.kattis.com/problems/codesprintla20.fastestrelay

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int, int>;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back

struct edge{int to;};
using graph = vector<vector<edge>>;

const int INF = 1031231234;
int solve(int i, auto& candidates, auto& used, int& acc) {
  if (i == 4) return acc;
  int best = INF;
  for (auto& [tm, ind]: candidates[i]) {
    if (count(all(used), ind)) continue;
    used.PB(ind);
    acc += tm;
    auto possible = solve(i + 1, candidates, used, acc);
    used.pop_back();
    acc -= tm;
    best = min(best, possible);
  }
  return best;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  vector<array<int, 4>> a(n);
  rep(i, 0, n) {
    rep(j, 0, 4) {
      cin >> a[i][j];
    }
  }
  vector<vector<ii>> candidates(4);
  rep(j, 0, 4) {
    priority_queue<ii> pq;
    rep(i, 0, n) {
      pq.push({a[i][j], i});
      if (sz(pq) > 4) pq.pop();
    }
    while(!pq.empty()) {
      candidates[j].PB(pq.top());
      pq.pop();
    }
  }
  int acc = 0;
  vi used;
  auto res = solve(0, candidates, used, acc);
  cout << res << '\n';
}
