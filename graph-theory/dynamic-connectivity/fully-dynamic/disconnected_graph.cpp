// offline dynamic connectivity (independent batch edge removal update, is_disconnected queries)
// https://codeforces.com/gym/100551/problem/E
// Note: reducing the # of distinct time steps improves runtime significantly (~700 ms => ~400 ms)

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

using Update = pii;
struct Query{};
using event = tuple<int, int, int, int>; // u, v, t1, t2 (update) or -1, -1, t, t (query)

struct RollbackUF {
  vi e; vector<pii> st;
  RollbackUF(int n) : e(n, -1) {}
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
 
struct ST {
  int s;
  vector<vector<Update>> updates;
  vector<optional<Query>> queries; 
  RollbackUF dsu;
  int ncomp;
  
  ST(int n, int nn) : s{n}, updates(4 * s), queries(s), dsu(nn), ncomp{nn} {}
  void add_update(int l, int r, cauto& u) {add_update(1, l, r, u, 0, s - 1);}
  void add_update(int i, int l, int r, cauto& u, int lo, int hi) {
    if (r < lo or hi < l) return;
    else if (l <= lo and hi <= r) updates[i].PB(u);
    else {
      auto mid = (lo + hi) / 2;
      add_update(2 * i, l, r, u, lo, mid);
      add_update(2 * i + 1, l, r, u, mid + 1, hi);
    }
  }
  void add_query(int t, cauto& q){queries[t] = q;}
  
  auto solve() {
    vi res;
    solve(1, res, 0, s - 1);
    return res;
  }
  void solve(int i, auto& res, int lo, int hi) {
    int save_time = dsu.time(), save_comp = ncomp;
    for (cauto& [u, v]: updates[i]) ncomp -= dsu.join(u, v);
    
    if (lo == hi) {
      if (queries[lo]) res.PB(ncomp == 1);
    } else {
      auto mid = (lo + hi) / 2;
      solve(2 * i, res, lo, mid);
      solve(2 * i + 1, res, mid + 1, hi);
    }
    dsu.rollback(save_time);
    ncomp = save_comp;
  }
};

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);
 
  freopen("disconnected.in", "r", stdin);
  freopen("disconnected.out", "w", stdout);
  
  int n, m;
  cin >> n >> m;
  vector<pii> edges(m);  

  int timer = 0;
  vi add_time(m);
  vector<event> events;
  
  rep(it, 0, m) {
    int u, v;
    cin >> u >> v;
    --u; --v;
    if (u > v) swap(u, v);
    add_time[it] = 0; // all original edges inserted at time 0
    edges[it] = {u, v};
  }
  timer++;
  
  int k;
  cin >> k;
  rep(__, 0, k) {
    int c;
    cin >> c;
    vi ids(c);
    trav(id, ids) {cin >> id; --id;}
    trav(id, ids) {
      cauto& [u, v] = edges[id];
      events.PB({u, v, add_time[id], timer}); // all edges in same batch removed at same time
    }
    timer++;
    events.PB({-1, -1, timer, timer}); // query event (and timer increment) could be removed; just need to mark the times that correspond to some output
    timer++;
    trav(id, ids) add_time[id] = timer; // all edges in same batch re-inserted at same time
    timer++;
  }
  rep(id, 0, m) {
    cauto& [u, v] = edges[id];
    events.PB({u, v, add_time[id], timer}); // all non-deleted edges are removed at the same time
  }
  timer++;

  ST st(timer, n);
  for (cauto& [u, v, t1, t2]: events) {
    if (u == -1) st.add_query(t1, Query{});
    else st.add_update(t1, t2, Update{u, v});
  }
  auto res = st.solve();
  for (cauto& i: res) cout << (i ? "Connected" : "Disconnected") << '\n';
}
