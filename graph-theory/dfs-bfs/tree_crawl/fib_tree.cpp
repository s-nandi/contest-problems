// recursive structure (if multiple partitionings exist can choose any since at most 2 disjoint partitions exist and f(n-1)=f(n-2)+f(n-3)), dfs (find k1/k2 partition), fib(n-1) / fib(n) ~ 1/3 => log depth
// https://codeforces.com/contest/1491/problem/E

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

struct edge{int to, id;};
using graph = vector<vector<edge>>;

const int MAXN = 200'000;
const int THRESHOLD = 3; // F_3 or smaller trees always valid
int sizes[MAXN];

const auto fib = [](){
                   vi res{1, 1};
                   while (res.back() < MAXN) {
                     res.PB(res[sz(res) - 2] + res[sz(res) - 1]);
                   }
                   return res;
                 }();

optional<array<int, 3>> dfs_find_splits(const auto& g, int i, const int total_size, const auto& dead, const auto& is_valid, int p = -1) {
  auto goodedge = [&](const auto& e) {return e.to != p and !dead[e.id];};

  sizes[i] = 1;
  trav(e, g[i]) if (goodedge(e)) {
    if (auto got = dfs_find_splits(g, e.to, total_size, dead, is_valid, i); got) return got;
    
    sizes[i] += sizes[e.to];
    if (is_valid(sizes[e.to])) {
      auto above = total_size - sizes[e.to];
      auto below = sizes[e.to];
      return above > below ? array{i, e.to, e.id} : array{e.to, i, e.id}; // node on bigger side, node on smaller side, split edge i
    }
  }
  return nullopt;
}

bool recur(const auto& g, int i, auto& dead, int level) {
  if (level <= THRESHOLD) return true;
  else {
    auto valid_split = dfs_find_splits(g, i, fib[level], dead,
                                       [&](int s){return s == fib[level - 1] or s == fib[level - 2];});
    if (!valid_split) return false;
    else {
      const auto& [big_node, small_node, split_id] = *valid_split;
      dead[split_id] = true;
      return recur(g, big_node, dead, level - 1) and recur(g, small_node, dead, level - 2);
    }
  }
}

int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;
  graph g(n);
  rep(i, 0, n - 1) {
    int u, v;
    cin >> u >> v;
    --u; --v;
    g[u].PB({v, i});
    g[v].PB({u, i});
  }

  if (!binary_search(all(fib), n)) {
    cout << "NO" << '\n';
  } else {
    vi dead(n - 1);
    auto level = lower_bound(all(fib), n) - begin(fib);
    auto res = recur(g, 0, dead, level);
    cout << (res ? "YES" : "NO") << '\n';
  }
}
