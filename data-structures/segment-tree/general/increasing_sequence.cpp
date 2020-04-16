// segtree (lca of inds w/ max elem), bin lift, # of inds whose removal would change LIS containing index i
// https://codeforces.com/group/ZFgXbZSjvp/contest/272908/problem/J
// 2020 NAPC -2

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

const int MAXN = 300000;
const int MAXP = 19;
int depth[MAXN + 5];
int par[MAXP + 1][MAXN + 5];
void add_edge(int u, int v) {
  par[0][v] = u;
  depth[v] = v != u ? depth[u] + 1 : 0;
  rep(p, 1, MAXP + 1)
    par[p][v] = par[p - 1][par[p - 1][v]];
}

int lca(int u, int v){
  if (depth[u] < depth[v]) swap(u, v);
  int dist = depth[u] - depth[v];
  for (int i = MAXP; i >= 0; i--)
    if (dist & (1 << i))
      u = par[i][u];
  if (u == v) return u;
  for (int i = MAXP; i >= 0; i--)
    if (par[i][u] != par[i][v])
      tie(u, v) = pair{par[i][u], par[i][v]};
  return par[0][u];
}

const int INF = 1231231234;
struct info {
  int mx{0}, essential{0};
  void update(auto val, auto ind){mx = val, essential = ind;}
  info combine(const info& o) const {
    if (mx == o.mx) return {mx, lca(essential, o.essential)};
    else return mx > o.mx ? *this : o;
  }
};

template <typename T>
struct ST {
  int s;
  vector<T> v;
  ST(int n) : s(n), v(2 * s) {}
  void update(int p, auto... elem) {
    v[p += s].update(elem...);
    for (p >>= 1; p; p >>= 1)
      v[p] = v[p << 1].combine(v[p << 1 | 1]);
  }
  T query(int l, int r) {
    T acc{};
    for (l += s, r += s; l <= r; (++l) >>= 1, (--r) >>= 1) {
      if (l & 1) acc = acc.combine(v[l]);
      if(!(r & 1)) acc = acc.combine(v[r]);
    }
    return acc;
  }
};

vi solve_suffix(const auto& a) {
  int root = sz(a);
  depth[root] = 0;
  rep(p, 0, MAXP + 1) par[p][root] = root;
  
  ST<info> st(sz(a) + 1);
  vi res(sz(a));
  for (int i = sz(a) - 1; i >= 0; i--) {
    info q = st.query(a[i], sz(a));
    if (q.mx == 0)
      add_edge(root, a[i]);
    else
      add_edge(q.essential, a[i]);
    st.update(a[i], q.mx + 1, a[i]);
    res[i] = depth[a[i]] - 1;
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  vi a(n);
  trav(i, a) {
    cin >> i;
    --i;
  }
  auto res1 = solve_suffix(a);
  reverse(all(a));
  rep(i, 0, n) a[i] = (n - 1) - a[i];
  auto res2 = solve_suffix(a);
  reverse(all(res2));
  rep(i, 0, n)
    cout << res1[i] + res2[i] << " ";
  cout << '\n';
}
