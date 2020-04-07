// toposort, greedy, maximizing min toposort by adding k edges
// https://codeforces.com/gym/100801 (problem G)
// 2015 NEERC Northern Subregional

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define sz(x) (int)(x).size()
#define PB push_back

struct edge{int to;};
using graph = vector<vector<edge>>;

template <typename T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using max_queue = priority_queue<T>;

auto poll(auto& pq) {
  auto curr = pq.top();
  pq.pop();
  return curr;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  /* Uncomment to submit
    freopen("graph.in", "r", stdin);
    freopen("graph.out", "w", stdout);
  */

  int n, m, k;
  cin >> n >> m >> k;
  graph g(n);
  rep(i, 0, m) {
    int a, b;
    cin >> a >> b;
    g[--a].PB({--b});
  }
  vi ideg(n);
  rep(i, 0, n) trav(e, g[i])
    ideg[e.to]++;

  int rem = k;
  min_queue<int> lhs;
  max_queue<int> rhs;
  rep(i, 0, n) if (ideg[i] == 0)
    lhs.push(i);
  
  vi topo;
  vector<pair<int, int>> added;
  auto relax = [&](int i) {
                 topo.PB(i);
                 trav(e, g[i])
                   if (--ideg[e.to] == 0)
		     lhs.push(e.to);
	       };
  rep(i, 0, n) {
    while (rem > 0 and (sz(lhs) > 1 or (sz(lhs) > 0 and sz(rhs) > 0 and rhs.top() > lhs.top()))) {
      rhs.push(poll(lhs));
      --rem;
    }
    if (!lhs.empty())
      relax(poll(lhs));
    else {
      added.PB({topo.back(), rhs.top()});
      relax(poll(rhs));
    }
  }
  trav(i, topo) cout << i + 1 << " "; cout << '\n';
  cout << sz(added) << '\n';
  for (auto [a, b]: added) cout << a + 1 << " " << b + 1 << '\n';
}
