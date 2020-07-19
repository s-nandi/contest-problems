// centroid, bipartite coloring (every path of length >= 2 contains all small prime factors -- be careful with short paths containing centroid), num thy (max unique prime factors in # <= 100)
// https://www.codechef.com/COOK120A/problems/PATHETIC

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;

#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back

struct edge{int to;};
using graph = vector<vector<edge>>;

const int MAXA = 100;
bool comp[MAXA + 5];
vi primes;

const ll LIM = 2e18;
const int threshold1 = 29;
const int threshold2 = 53;

int dfs(const graph& g, int i, auto& sizes, int p = -1) {
  sizes[i] = 1;
  trav(e, g[i]) if (e.to != p)
    sizes[i] += dfs(g, e.to, sizes, i);
  return sizes[i];
}

int getcentroid(const graph& g) {
  vi sizes(sz(g));
  int start = 0;
  auto total = dfs(g, start, sizes);
  
  int i = start, p = -1;
  int behind = 0;
  while (true) {
    int nxt = -1;
    trav(e, g[i]) if (e.to != p) {
      if (2 * sizes[e.to] > total) {
        nxt = e.to;
        break;
      }
    }
    if (nxt == -1) break;
    p = i;
    i = nxt;
  }
  return i;
}

void color(const graph& g, int i, auto& colors, int c = 0, int p = -1) {
  colors[i] = c;
  trav(e, g[i]) if (e.to != p)
    color(g, e.to, colors, 1 - c, i);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  memset(comp, 0, sizeof(comp));
  rep(i, 2, MAXA + 1) {
    trav(p, primes) {
      if (i % p == 0) {
        comp[i] = true;
        break;
      }
    }
    if (!comp[i]) primes.PB(i);
  }

  ll mult1 = 1, mult2 = 1, multcenter = 1;
  trav(p, primes) {
    if (p <= threshold1) mult1 *= p;
    else if (p <= threshold2) mult2 *= p;
    else multcenter *= p;
  }
  assert(mult1 <= LIM);
  assert(mult2 <= LIM);
  assert(multcenter <= LIM);
  
  int T;
  cin >> T;
  while(T--) {
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

    vector<ll> res(n);
    if (n <= threshold1) {
      fill(all(res), mult1);
    } else {
      int centroid = getcentroid(g);
      vi colors(n);
      color(g, centroid, colors);
      rep(i, 0, n)
        res[i] = (colors[i] == 1) ? mult1 : mult2;
      res[centroid] = multcenter;
    }
    trav(i, res) cout << i << " "; cout << '\n';
  }
}
