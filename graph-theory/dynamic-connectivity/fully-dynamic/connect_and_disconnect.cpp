// offline dynamic connectivity (add/remove edge updates, count # of connected components queries), O(n log^2 n) solution based on dividing 'live' time of each edge into log(n) intervals a la segment tree
// https://codeforces.com/gym/100551/problem/A
// Note: There is a O(n log n) solution that doesn't run much faster in practice for N = 300'000

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
      if (queries[lo]) res.PB(ncomp);
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
 
  freopen("connect.in", "r", stdin);
  freopen("connect.out", "w", stdout); 
  
  int n, k;
  cin >> n >> k;
  map<Update, int> add_time;
  ST st(k + 1, n);
  rep(it, 0, k) {
    char type;
    cin >> type;
    if (type == '+' or type == '-') {
      int u, v;
      cin >> u >> v;
      --u; --v;
      if (u > v) swap(u, v);
      
      if (type == '+') add_time[{u, v}] = it;
      else {
        st.add_update(add_time[{u, v}], it, Update{u, v});
        add_time.erase({u, v});
      }
    } else st.add_query(it, Query{});
  }
  for (cauto& [update, last]: add_time)
    st.add_update(last, k, update);
 
  auto res = st.solve();
  for (cauto& i: res) cout << i << " "; cout << '\n';
}
