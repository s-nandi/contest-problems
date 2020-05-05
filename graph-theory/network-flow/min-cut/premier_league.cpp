// min cut (penalty construction)
// https://utipc20s.kattis.com/problems/utipc20s.premierleague
// 2020 UT Spring Programming Contest


#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define sz(x) (int)(x).size()

struct Dinic {
  struct Edge {
    int to, rev;
    ll c, oc;
    ll flow() { return max(oc - c, 0LL); } // if you need flows
  };
  vi lvl, ptr, q;
  vector<vector<Edge>> adj;
  Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
  void addEdge(int a, int b, ll c, int rcap = 0) {
    adj[a].push_back({b, sz(adj[b]), c, c});
    adj[b].push_back({a, sz(adj[a]) - 1, rcap, rcap});
  }
  ll dfs(int v, int t, ll f) {
    if (v == t || !f) return f;
    for (int& i = ptr[v]; i < sz(adj[v]); i++) {
      Edge& e = adj[v][i];
      if (lvl[e.to] == lvl[v] + 1)
        if (ll p = dfs(e.to, t, min(f, e.c))) {
          e.c -= p, adj[e.to][e.rev].c += p;
          return p;
        }
    }
    return 0;
  }
  ll calc(int s, int t) {
    ll flow = 0; q[0] = s;
    rep(L,0,31) do { // 'int L=30' maybe faster for random data
      lvl = ptr = vi(sz(q));
      int qi = 0, qe = lvl[s] = 1;
      while (qi < qe && !lvl[t]) {
        int v = q[qi++];
        for (Edge e : adj[v])
          if (!lvl[e.to] && e.c >> (30 - L))
            q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
      }
      while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
    } while (lvl[t]);
    return flow;
  }
  bool leftOfMinCut(int a) { return lvl[a] != 0; }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  using bid = tuple<int, int, int>;
  vector<bid> bids(n); // (cost, offer 1, offer 2)
  rep(i, 0, n) {
    int c, a, j;
    cin >> c >> a >> j;
    bids[i] = {c, a, j};
  }
  int m;
  cin >> m;
  using battle = tuple<int, int, int>; // (i, j, cost)
  vector<battle> battles(m);
  rep(i, 0, m) {
    int a, b, c;
    cin >> a >> b >> c;
    --a; --b;
    battles[i] = {a, b, c};
  }
  int nn = n + 2;
  int s = nn - 2, t = nn - 1;
  Dinic dnc(nn);
  int base = 0;
  rep(i, 0, n) {
    auto [cost, offer1, offer2] = bids[i];
    if (offer1 > offer2) dnc.addEdge(s, i, offer1 - offer2);
    else dnc.addEdge(i, t, offer2 - offer1);
    base += cost - max(offer1, offer2);
  }
  rep(i, 0, m) {
    auto [u, v, cost] = battles[i];
    dnc.addEdge(v, u, cost);
    dnc.addEdge(u, v, cost);
  }
  auto penalty = dnc.calc(s, t);
  cout << base + penalty << '\n';
}
