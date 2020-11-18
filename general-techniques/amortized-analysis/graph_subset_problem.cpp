// amortized analysis, invariant maintenance (q only contains nodes with degree < k), clique of size k implies a subset with intra-degrees of k-1, toposort-like processing, offline linear adjacency checking
// https://codeforces.com/contest/1439/problem/B

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
#define cauto const auto
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using vi = vector<int>;

struct edge {int to;};
using graph = vector<vector<edge>>;

/**
 * If there's a subset w/ min intra-degree k, we'll find it at the end; keep nodes with degree >= k alive (DONT push them to q)
 *
 * So assume there is no such subset, so there is either a k-clique or no solution. Since we assume that there is no k-subset,
 * we know that a k-clique (if it exists) must contain a node popped from q, otherwise there would have been a k-subset
 *
 * We also know if there is a k-clique, there would be a subset w/ min intra-degree k-1; so, we know that:

 * Case 1: If there are any nodes with degree < k-1 they clearly cannot be part of either a subset or clique solution; delete these
 * These nodes can actually be handled the same way as the latter case, but deleting them without checking for a clique yields a ~40% speedup
 *
 * Case 2: If there is a node i with degree == k - 1, they might be part of a clique; take the clique consisting of this node and all (k-1) neighbors
 *                                                                                    and verify if this is actually a clique
 *
 * The clique checking requires O(k^2) time (offline), and afterwards, i is deleted, which reduces the total degree in the graph by (k-1)
 * So this clique checking will only be done O(m / k) times, so the total cost is O((m / k) * (k ^ 2)) = O(mk)
 * Now, note that a k-clique requires O(k^2) edges, so k is O(sqrt(m)), which makes the total runtime O(m sqrt(m))
 */
auto solve(int n, cauto& g, int k) {
  vi deg(n);
  rep(i, 0, n) deg[i] = sz(g[i]);
  queue<int> q;
  rep(i, 0, n) if (deg[i] < k)
    q.push(i);

  auto delete_node = [&](int i) {
                       trav(e, g[i]) if (--deg[e.to] == k - 1)
                         q.push(e.to);
                       deg[i] = 0; // need this to avoid using i in some other node's clique
                     };

  vector<vi> possible_clique;
  while (!empty(q)) {
    auto i = q.front(); q.pop();

    if (deg[i] < k - 1) {
      delete_node(i);
    } else if (deg[i] == k - 1) {
      vi clique; clique.reserve(k);
      clique.PB(i);
      trav(e, g[i]) if (deg[e.to] > 0)
        clique.PB(e.to);
      possible_clique.emplace_back(move(clique));
      delete_node(i);
    } else assert(false);
  }
  
  auto npossible = sz(possible_clique);
  vi good_clique(npossible, true);
  vector<vector<pii>> required_neighbor(n); // (neighbor, clique index)
  rep(it, 0, npossible) {
    trav(i, possible_clique[it]) trav(j, possible_clique[it]) if (i < j) {
      required_neighbor[i].PB({j, it});
    }
  }

  vi satisfied(n);
  rep(i, 0, n) {
    for (cauto& [req, __]: required_neighbor[i]) satisfied[req] = false;
    trav(e, g[i]) satisfied[e.to] = true;
    for (cauto& [req, ind]: required_neighbor[i])
      if (!satisfied[req])
        good_clique[ind] = false;
  }
  rep(it, 0, npossible) if (good_clique[it]) return pair{2, possible_clique[it]};
  
  vi subset;
  rep(i, 0, n) if (deg[i] >= k) subset.PB(i);
  return pair{sz(subset) > 0 ? 1 : -1, subset};
}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);
  
  int T;
  cin >> T;
  while(T--) {
    int n, m, k;
    cin >> n >> m >> k;
    graph g(n);
    rep(it, 0, m) {
      int u, v;
      cin >> u >> v;
      --u; --v;
      g[u].PB({v});
      g[v].PB({u});
    }

    auto [type, res] = solve(n, g, k);
    if (type == 1) {
      cout << 1 << " " << sz(res) << '\n';
      trav(i, res) cout << (i + 1) << " "; cout << '\n';
    } else if (type == 2) {
      cout << 2 << '\n';
      trav(i, res) cout << (i + 1) << " "; cout << '\n';
    } else cout << -1 << '\n';
  }
}
