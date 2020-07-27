// venice trick (+ std::set iterator fiddling), invariant maintainance (Frontier.pq), if refill on node not on path A->B then never perform another refill before hitting a node on path AB, repeating nodes not useful
// https://www.facebook.com/codingcompetitions/hacker-cup/2020/qualification-round/problems/D2
// Note: Could (probably) also be done with iterative segment tree: st[i] = min cost at distance d. Query range is [-delta, m - dist - delta]

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

const ll INF = 1e17;
int n, m;

/* 
 * pq will contain pairs in increasing order of distance and decreasing order of cost;
 * only relevant pairs are stored -- if any pair is dominatated ((a,b) dominates (c,d) if a<=c and b<=d)
 * it is not stored in the set
 */
struct Frontier {
  set<pair<int, ll>> pq; // (distance, cost)
  int delta = 0;

  static bool makes_redundant(const auto& candidate, const auto& replaced) {
    return candidate.first <= replaced.first and candidate.second <= replaced.second;
  }

  void add(int dist, ll cost) {
    auto elem = pair<int, ll>{dist - delta, cost};
    auto [it, new_insert] = pq.insert(elem);
    if (!new_insert) return;
    if (it != begin(pq) and makes_redundant(*prev(it), *it)) {
      pq.erase(elem);
      return;
    }
    if (it != prev(end(pq)) and makes_redundant(*next(it), *it)) {
      pq.erase(elem);
      return;
    }
    while(it != begin(pq) and makes_redundant(*it, *prev(it)))
      pq.erase(prev(it));
    while (it != prev(end(pq)) and makes_redundant(*it, *next(it)))
      pq.erase(next(it));
  }

  ll mincost(int maxdist) const {
    assert(!empty(pq));
    auto it = pq.upper_bound({maxdist - delta, INF});
    return it == begin(pq) ? INF : prev(it) -> second;
  }

  void increment(){delta++;}
};

bool dfs_path(const graph& g, int i, int dst, auto& path, int prv = -1) {
  path.PB(i);
  if (i == dst) return true;
  trav(e, g[i]) if (e.to != prv)
    if (dfs_path(g, e.to, dst, path, i)) return true;
  path.pop_back();
  return false;
}

void set_dp(auto& frontier, const auto& c, auto& dp, auto& contrib, int i, int dist) {
  dp[i] = frontier.mincost(m - dist);
  contrib[i] = dp[i] + c[i];
  frontier.add(dist, contrib[i]);
}

void dfs_side(auto& g, int i, int p, auto& c, auto& dp, auto& contrib, auto& frontier, int dist = 1) {
  set_dp(frontier, c, dp, contrib, i, dist);
  trav(e, g[i]) if (e.to != p)
    dfs_side(g, e.to, i, c, dp, contrib, frontier, dist + 1);
}

void solve(auto& g, auto& path, int it, auto& c, auto& dp, auto& contrib, auto& reserved, auto& frontier) {
  if (it == sz(path)) return;
  auto i = path[it];
  set_dp(frontier, c, dp, contrib, i, 0);
  trav(e, g[i]) if (!binary_search(all(reserved), e.to))
    dfs_side(g, e.to, i, c, dp, contrib, frontier);
  frontier.increment();
  solve(g, path, it + 1, c, dp, contrib, reserved, frontier);
}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  // freopen("input.txt", "r", stdin);
  // freopen("output.txt", "w", stdout);

  int num_tests;
  cin >> num_tests;
  rep(curr_test, 1, num_tests + 1) {
    int a, b;
    cin >> n >> m >> a >> b;
    --a; --b;
    graph g(n);
    vector<ll> c(n);
    rep(i, 0, n) {
      int p;
      cin >> p >> c[i];
      --p;
      if (c[i] == 0) c[i] = INF;
      if (p >= 0) {
        g[i].PB({p});
        g[p].PB({i});
      }
    }
    vi path;
    dfs_path(g, a, b, path);

    auto sorted = path;
    sort(all(sorted));
    vector<ll> dp(n, INF), contrib(n, INF);
    Frontier frontier;
    frontier.add(0, 0);
    frontier.increment();
    solve(g, path, 1, c, dp, contrib, sorted, frontier);
    
    cout << "Case #" << curr_test << ": ";
    cout << (dp[b] < INF ? dp[b] : -1LL) << '\n';
  }
}
