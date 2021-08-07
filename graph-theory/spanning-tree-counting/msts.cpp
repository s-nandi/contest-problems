// kirchoffs theorem, dsu (compress edges with ascending weights, count spanning tree for each component separately)
// https://www.spoj.com/problems/MSTS/

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a);i<(b);++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back
using ll = long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int,int>;

constexpr auto dbg = false;

struct edge{int to;};
using graph = vector<vector<edge>>;

constexpr int MOD = 31011;

void trimsort(auto& vec) {
  sort(all(vec));
  vec.erase(unique(all(vec)), end(vec));
}

void matminor(auto& mat, int ind) {
  mat.erase(begin(mat) + ind);
  trav(row, mat) row.erase(begin(row) + ind);
}

struct UF {
  vi e;
  UF(int n) : e(n, -1) {}
  bool sameSet(int a, int b) { return find(a) == find(b); }
  int size(int x) { return -e[find(x)]; }
  int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
  bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    e[a] += e[b]; e[b] = a;
    return true;
  }
};

constexpr ll mod = MOD;
ll det(vector<vector<ll>>& a) {
  int n = sz(a); ll ans = 1;
  rep(i,0,n) {
    rep(j,i+1,n) {
      while (a[j][i] != 0) { // gcd step
        ll t = a[i][i] / a[j][i];
        if (t) rep(k,i,n)
                 a[i][k] = (a[i][k] - a[j][k] * t) % mod;
        swap(a[i], a[j]);
        ans *= -1;
      }
    }
    ans = ans * a[i][i] % mod;
    if (!ans) return 0;
  }
  return (ans + mod) % mod;
}

ll solve(int n, auto edges, const auto& byweight) {
  ll ways = 1;
  UF dsu(n);
  for (const auto& [lo, hi]: byweight) {
    rep(i, lo, hi) {
      auto& [w, u, v] = edges[i];
      u = dsu.find(u);
      v = dsu.find(v);
    }
    rep(i, lo, hi) {
      const auto& [w, u, v] = edges[i];
      dsu.join(u, v);
    }
    map<int, vector<pii>> bycomp;
    rep(i, lo, hi) {
      const auto& [w, u, v] = edges[i];
      bycomp[dsu.find(u)].PB({u, v});
    }

    for (auto& [comp, compedges]: bycomp) {
      vi sorted;
      auto indexof = [&](int i) { return lower_bound(all(sorted), i) - begin(sorted); };
      for (const auto& [u, v]: compedges)
        sorted.PB(u), sorted.PB(v);
      trimsort(sorted);
      for (auto& [u, v]: compedges)
        u = indexof(u), v = indexof(v);
      
      int nn = sz(sorted);
      auto mat = vector<vector<ll>>(nn, vector<ll>(nn));
      for (const auto& [u, v]: compedges) {
        --mat[u][v];
        ++mat[v][v];
        --mat[v][u];
        ++mat[u][u];
      }
      matminor(mat, 0);
      ll mult = det(mat);
      ways = (ways * mult) % mod;
    }
  }
  return ways;
}

int32_t main() {
  cin.tie(0)->sync_with_stdio(0);
  
  int n, m;
  cin >> n >> m;
  vector<array<int, 3>> edges(m);
  for (auto& [w, u, v]: edges) {
    cin >> u >> v >> w;
    --u; --v;
  }
  sort(all(edges));

  vector<pii> byweight;
  for (int l = 0, r = 0; l < m; l = r) {
    while (r < m and edges[r][0] == edges[l][0]) r++;
    byweight.PB({l, r});
  }
  cout << solve(n, edges, byweight) << '\n';
}
