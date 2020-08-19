// implicit graph (each prime [& 1] is a node, a[i]'s are edges), num. theory (<= 7 fac. => <= 2 prm fac.), sh. cycle on unweighted/undirected graph, all cycles must contain some node <= sqrt(MAXA) => OK to only BFS from small nodes
// https://codeforces.com/contest/1325/problem/E

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
 
struct edge{int to, id;};
using graph = vector<vector<edge>>;
 
constexpr int MAXA = 1000000;
constexpr int MAXN = 100000;
constexpr int MAXF = 2 * MAXN;
constexpr int INF = 1031231234;
 
auto minn(auto& a, auto b){return b < a ? (a = b, true) : false;}

auto odd_power_factors(int val) {
  auto old = val;
  vi res;
  for (int f = 2; f * f <= old; f++) {
    int cnt = 0;
    while (val % f == 0) val /= f, cnt++;
    if (cnt & 1) res.PB(f);
  }
  if (val != 1) res.PB(val);
  return res;
}

int level[MAXF + 5];
int pid[MAXF + 5];
int q[MAXF + 1];

int shortest_cycle(const auto& g, int s) {
  fill(begin(level), begin(level) + sz(g), INF);
  fill(begin(pid), begin(pid) + sz(g), -1);
  int hd = 0, tl = 0;
  
  level[s] = 0;
  q[tl++] = s;
 
  int best = INF;
  while(hd < tl) {
    int i = q[hd++];
    trav(e, g[i]) if (e.id != pid[i]) {
      best = min(best, level[i] + level[e.to] + 1); // we might find a non-simple cycle, but such a cycle is never optimal (we can always trim the duplicated edges)
                                                    // so our optimal answer at the end is correct (DONT use the result of a single shortest_cycle call)
      if (minn(level[e.to], level[i] + 1)) {
        q[tl++] = e.to;
        pid[e.to] = e.id;
      }
    }
  }
  return best;
}
 
int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);
 
  int n;
  cin >> n;
  vi a(n);
  trav(i, a) cin >> i;
 
  map<int, int> indexer;
  auto getindex = [&](int i){
                    if (indexer.count(i)) return indexer[i];
                    else {
                      int res = sz(indexer);
                      return (indexer[i] = res);
                    }
                  };
  graph g(MAXF + 1);
  int nedges = 0;
  trav(i, a) {
    auto factors = odd_power_factors(i);
    while (sz(factors) < 2) factors.PB(1);
    
    auto u = getindex(factors[0]);
    auto v = getindex(factors[1]);
    g[u].PB({v, nedges});
    g[v].PB({u, nedges});
    nedges++;
  }
  int best = INF;
  for (const auto& [fac, mapping]: indexer) {
    if (fac * fac > MAXA) break;
    auto possible = shortest_cycle(g, mapping);
    best = min(best, possible);
  }
  cout << (best == INF ? -1 : best) << '\n';
}
