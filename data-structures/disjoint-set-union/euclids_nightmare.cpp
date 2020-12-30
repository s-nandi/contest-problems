// dsu, reducing xor of length-2 mod-2 vectors to graph, treating length-1 vectors as (u, m) vectors instead
// https://codeforces.com/contest/1466/problem/F

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

struct edge{int to;};
using graph = vector<vector<edge>>;

constexpr auto dbg = false;

const int MOD = 1'000'000'007;
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

auto mult(ll a, ll b){return a * b % MOD;}

auto solve(int n, int m, auto a) {
  UF dsu(m + 1);
  int special = m;
  
  vector<array<int, 3>> edges; // u, v, id
  rep(it, 0, n) {
    const auto& row = a[it];
    auto k = sz(row);
    if (k == 1) edges.PB({row[0], special, it});
    else edges.PB({row[0], row[1], it});
  }

  vi res;
  for (auto& [u, v, id]: edges) {
    if (dsu.join(u, v)) res.PB(id);
  }

  vi roots;
  rep(i, 0, m + 1)
    if (i == dsu.find(i)) roots.PB(i);

  ll cnt = 1;
  trav(i, roots) {
    auto s = dsu.size(i);
    rep(it, 0, s - 1) cnt = mult(2, cnt);
  }
  cout << cnt << " " << sz(res) << '\n';
  trav(i, res) cout << (i + 1) << " "; cout << '\n';  
}

int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);
  int n, m;
  cin >> n >> m;
  vector<vi> a(n);
  trav(row, a) {
    int k;
    cin >> k;
    row.resize(k);
    trav(i, row) {
      cin >> i;
      --i;
    }
  }
  solve (n, m, a);
}
