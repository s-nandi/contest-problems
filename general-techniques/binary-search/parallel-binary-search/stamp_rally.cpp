// parallel binary search, DSU
// https://atcoder.jp/contests/agc002/tasks/agc002_d

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
constexpr auto check = false;
constexpr auto custom = false;

struct edge{int to;};
using graph = vector<vector<edge>>;

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
  int ask(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return size(a);
    else return size(a) + size(b);
  }
};

int32_t main() {
  cin.tie(0)->sync_with_stdio(0);
  
  int n, m;
  cin >> n >> m;
  vector<pii> edges(m);
  rep(it, 0, m) {
    int u, v;
    cin >> u >> v;
    --u; --v;
    edges[it] = {u, v};
  }

  int q;
  cin >> q;
  vector<array<int, 3>> qs(q);
  rep(it, 0, q) {
    rep(i, 0, 3) cin >> qs[it][i];
    --qs[it][0], --qs[it][1];
  }

  vi los(q, 0), his(q, m - 1); // bin search on ind of max edges
  vector<vi> bymid(m);
  while (true) {
    rep(mid, 0, m) bymid[mid].clear();
    bool done = true;
    rep(i, 0, q) {
      if (los[i] != his[i]) {
        auto mid = los[i] + (his[i] - los[i]) / 2;
        bymid[mid].PB(i);
        done = false;
      }
    }
    if (done) break;
    
    UF dsu(n);
    rep(mid, 0, m) {
      auto [u, v] = edges[mid];
      dsu.join(u, v);
      
      trav(i, bymid[mid]) {
        auto [a, b, req] = qs[i];
        auto have = dsu.ask(a, b);
        if (have >= req) {
          his[i] = mid;
        } else {
          los[i] = mid + 1;
        }
      }
    }
  }
  rep(i, 0, q) cout << (los[i] + 1) << '\n';
}
