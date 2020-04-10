// cht, euler ordering, segtree on tree (subtree range updates, node queries)
// https://codeforces.com/group/ZFgXbZSjvp/contest/272908/problem/I
// 2020 NAPC

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back

struct edge{int to;};
using graph = vector<vector<edge>>;

struct equation {
  ll a, b;
  mutable ld intersectNxt = 0;
  ll slope() const {return a;}
  ll constant() const {return b;}
  ll y(ll x0) const {return a * x0 + b;}
  ld intersect(equation o) const {return ld (o.b - b) / (a - o.a);}
  bool operator < (const equation &o) const {return slope() < o.slope();}
  bool operator < (const ld &x) const {return intersectNxt < x;}
};

struct CHT : multiset<equation, less<>> {
  static const ll oo = numeric_limits<ll>::max() - 5;
  bool setNext(iterator x, iterator y) {
    if (y == end()) {
      x -> intersectNxt = oo;
      return false;
    }
    if (x -> slope() == y -> slope())
      x -> intersectNxt = x -> constant() > y -> constant() ? oo : -oo;
    else
      x -> intersectNxt = x -> intersect(*y);
    return x -> intersectNxt >= y -> intersectNxt;
  }
  void add(equation e) {
    e.intersectNxt = 0;
    auto it = insert(e), nit = next(it);
    while (setNext(it, nit))
      nit = erase(nit);
    if (it == begin()) return;
    auto pit = it;
    if (setNext(--pit, it))
      setNext(pit, it = erase(it));
    while (pit != begin()) {
      it = pit;
      pit = prev(pit);
      if (it != begin() and pit -> intersectNxt >= it -> intersectNxt)
        setNext(pit, erase(it));
      else break;
    }
  }
  ll get(ll x0) {
    if (empty()) return -oo;
    return lower_bound(x0) -> y(x0);
  }
};

const int MAXN = 80000;
int timer = 0;
int tin[MAXN + 5];
int tout[MAXN + 5];
void dfs(auto& g, int i, int p = -1) {
  tin[i] = timer++;
  trav(e, g[i]) if (e.to != p)
    dfs(g, e.to, i);
  tout[i] = timer - 1;
}

struct ST {
  int s;
  vector<CHT> v;
  ST(int n) : s{n}, v(4 * s) {}
  void update(int l, int r, const auto& elem) {update(1, 0, s - 1, l, r, elem);}
  void update(int i, int lb, int rb, int l, int r, const auto& elem) {
    if (lb > r or rb < l) return;
    else if (l <= lb and rb <= r) v[i].add(elem);
    else {
      int mb = (lb + rb) / 2;
      update(2 * i, lb, mb, l, r, elem);
      update(2 * i + 1, mb + 1, rb, l, r, elem);
    }
  }
  ll query(int p, ll x) {return query(1, 0, s - 1, p, x);}
  ll query(int i, int lb, int rb, int p, ll x) {
    ll res = -v[i].get(x);
    if (rb < p or lb > p) return CHT::oo;
    else if (lb == p and rb == p) return res;
    else {
      int mb = (lb + rb) / 2;
      auto lv = query(2 * i, lb, mb, p, x);
      auto rv = query(2 * i + 1, mb + 1, rb, p, x);
      return min({res, lv, rv});
    }    
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;
  vector<ll> a(n), b(n), c(n);
  rep(i, 0, n) cin >> a[i];
  rep(i, 0, n) cin >> b[i];
  rep(i, 0, n) cin >> c[i];
  graph g(n);
  rep(i, 0, n - 1) {
    int u, v;
    cin >> u >> v;
    --u; --v;
    g[u].PB({v});
    g[v].PB({u});
  }
  dfs(g, 0);
  
  vector<tuple<int, int, int>> queries(q); // T, V, index
  rep(i, 0, q) {
    int v, t;
    cin >> v >> t;
    --v;
    queries[i] = {t, v, i};
  }
  sort(all(queries), greater<>{});
  
  vector<pair<int, int>> cs;
  rep(i, 0, n) cs.push_back({c[i], i});
  sort(all(cs), greater<>{});

  ST tree(n);
  vector<ll> sol(q);
  int it = 0;
  rep(i, 0, q) {
    auto [t, v, ind] = queries[i];
    while (it < sz(cs) and cs[it].first >= t) {
      auto& [__, ind] = cs[it++];
      tree.update(tin[ind], tout[ind], equation{-b[ind], -a[ind]});
    }
    sol[ind] = tree.query(tin[v], t);
  }
  rep(i, 0, q) cout << sol[i] << " "; cout << '\n';
}
