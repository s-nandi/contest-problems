// MST property (set of edge weights is same across all MSTs), DSU with rollback, offline processing
// https://codeforces.com/contest/891/problem/C

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a);i<(b);++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)a.size()
#define PB push_back

using ll = long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int,int>;

struct edge{int to;};
using graph = vector<vector<edge>>;

constexpr auto dbg = false;

const int MAXW = 500'000;

auto sort_trim(auto& vec) {
  sort(all(vec));
  vec.erase(unique(all(vec)), end(vec));
}

struct RollbackUF {
  vi e; vector<pii> st;
  RollbackUF(int n) : e(n, -1) {}
  int size(int x) { return -e[find(x)]; }
  int find(int x) { return e[x] < 0 ? x : find(e[x]); }
  int time() { return sz(st); }
  void rollback(int t) {
    for (int i = time(); i --> t;)
      e[st[i].first] = st[i].second;
    st.resize(t);
  }
  bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    st.push_back({a, e[a]});
    st.push_back({b, e[b]});
    e[a] += e[b]; e[b] = a;
    return true;
  }
};

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;
  vector<array<int,3>> edges(m); // w, u, v
  rep(it, 0, m) {
    int u, v, w;
    cin >> u >> v >> w;
    edges[it] = {w, --u, --v};
  }
  int q;
  cin >> q;
  vector<vi> queries(q);
  trav(query, queries) {
    int cnt;
    cin >> cnt;
    query.resize(cnt);
    trav(i, query) {cin >> i; --i;}
  }

  auto cmp = [&](int i, int j) { return edges[i][0] < edges[j][0]; };
  vector<set<int>> byweight(MAXW + 1);
  rep(i, 0, q) {
    sort(all(queries[i]), cmp);
    trav(elem, queries[i])
      byweight[edges[elem][0]].insert(i);
  }
  
  vi inds(m);
  iota(all(inds), 0);
  sort(all(inds), cmp);

  auto eit = begin(inds);
  vector<decltype(begin(queries[0]))> qit(q);
  rep(it, 0, q) qit[it] = begin(queries[it]);
  auto leq_to = [&](int w) {
                  return [&, w](auto elem){return edges[elem][0] <= w;};
                };

  vi good(q, true);
  RollbackUF dsu(n);
  rep(weight, 0, MAXW + 1) {
    trav(qind, byweight[weight]) {
      auto timer = dsu.time();
      auto nxt = partition_point(qit[qind], end(queries[qind]), leq_to(weight));
      rep(it, qit[qind], nxt)
        good[qind] &= dsu.join(edges[*it][1], edges[*it][2]);
      qit[qind] = nxt;
      dsu.rollback(timer);
    }
    {
      auto nxt = partition_point(eit, end(inds), leq_to(weight));
      rep(it, eit, nxt)
        dsu.join(edges[*it][1], edges[*it][2]);
      eit = nxt;
    }
  }
  trav(res, good) cout << (res ? "YES" : "NO") << '\n';
}
