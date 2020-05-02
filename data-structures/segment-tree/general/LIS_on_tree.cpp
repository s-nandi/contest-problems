// LIS on tree, segment tree, dfs (prefix max on tree)
// https://atcoder.jp/contests/abc165/tasks/abc165_f

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back

struct edge{int to;};
using graph = vector<vector<edge>>;

struct ST {
  using T = ll;
  int s;
  vector<T> v;
  ST(int s) : s{s}, v(2 * s) {}
  T f(T a, T b){return max(a, b);}
  void update(int p, T val) {
    v[p += s] = val;
    for (p >>= 1; p >= 1; p >>= 1)
      v[p] = f(v[2 * p], v[2 * p + 1]);
  }
  T query(int l, int r) {
    if (l > r) return 0;
    T acc = 0;
    for (l += s, r += s; l <= r; (++l) >>= 1, (--r) >>= 1) {
      if (l & 1) acc = f(acc, v[l]);
      if (~r & 1) acc = f(v[r], acc);
    }
    return acc;
  }
};

vi sorted;
int getindex(int val) {
  return lower_bound(all(sorted), val) - begin(sorted);
}

void dfs(graph& g, int i, vi& a, ST& st, vi& res, int p = -1) {
  auto index = getindex(a[i]);
  auto old = st.query(index, index);
  res[i] = st.query(0, index - 1) + 1;
  st.update(index, res[i]);
  trav(e, g[i]) if (e.to != p)
    dfs(g, e.to, a, st, res, i);
  st.update(index, old);
}

void push(graph& g, int i, auto& res, int p = -1, int best = 0) {
  res[i] = max(res[i], best);
  trav(e, g[i]) if (e.to != p)
    push(g, e.to, res, i, max(best, res[i]));
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  vi a(n);
  trav(i, a) cin >> i;

  sorted = a;
  sort(all(sorted));
  sorted.erase(unique(all(sorted)), end(sorted));
  
  graph g(n);
  rep(i, 0, n - 1) {
    int u, v;
    cin >> u >> v;
    --u; --v;
    g[u].PB({v});
    g[v].PB({u});
  }

  ST st(n);
  vi res(n);
  dfs(g, 0, a, st, res);
  push(g, 0, res);
  trav(i, res) cout << i << '\n';
}
