// DSU (store subtree data), amortized analysis (smaller to larger), online (insert-only) bipartite checking
// https://www.codechef.com/problems/GEARS

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

namespace cp {
  auto gcd(auto a, auto b) -> decltype(a) {
    return b == 0 ? a : gcd(b, a % b);
  }
}

struct DSU {
  vi par;
  vector<uint8_t> inv, blk;
  DSU(int n) : par(n, -1), inv(n), blk(n) {}
  array<int, 3> find(int i, bool inverted = false, bool blocked = false) { // nodes are initially white, inverted => node is black
    auto ninverted = inverted ^ inv[i];
    auto nblocked = blocked | blk[i];
    if (par[i] < 0) return {i, ninverted, nblocked};
    else return find(par[i], ninverted, nblocked);
  } // return: root, color, is_blocked
  void join(int u, int v, bool is_same_color) {
    if ((u = find(u)[0]) == (v = find(v)[0])) {
      blk[u] |= is_same_color; // if connecting two nades w/ same color and same component, the component is now blocked
      return;
    }
    if (par[u] > par[v]) swap(u, v);
    par[u] += par[v];
    par[v] = u;
    inv[v] ^= is_same_color; // if connecting two disjoint components w/ same color, need to invert color of one of the components
                             // can't invert u since that inversion would also affect v
  }
};

struct fraction {
  ll num, denom;
  fraction(ll a, ll b) {
    auto g = cp::gcd(a, b);
    a /= g; b /= g;
    if (b < 0) a = -a, b = -b;
    num = a, denom = b;
  }
  friend ostream& operator << (ostream& os, const fraction& f) {
    return os << f.num << "/" << f.denom;
  }
};

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m;
  
  vi a(n);
  trav(i, a) cin >> i;
  
  DSU dsu(n);
  rep(it, 0, m) {
    int t;
    cin >> t;
    if (t == 1) {
      int x, c;
      cin >> x >> c;
      a[--x] = c;
    } else if (t == 2) {
      int u, v;
      cin >> u >> v;
      --u; --v;
      dsu.join(u, v, dsu.find(u)[1] == dsu.find(v)[1]);
    } else if (t == 3) {
      int u, v, vel;
      cin >> u >> v >> vel;
      --u; --v;
      auto ufind = dsu.find(u);
      auto vfind = dsu.find(v);
      if (ufind[0] != vfind[0] or ufind[2]) { // ie. disconnected or blocked
        cout << 0 << '\n';
      } else {
        auto odd_dist = ufind[1] ^ vfind[1];
        auto sgn = odd_dist ? -1 : 1;
        cout << fraction((ll) sgn * vel * a[u], a[v]) << '\n';
      }
    } else assert(false);
  }
}
