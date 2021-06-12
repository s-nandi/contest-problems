// binary lifting, offline propagating downwards (segment tree)
// https://codeforces.com/gym/102861/problem/E
// 2021 Brazil Subregional

#include <bits/stdc++.h>
using namespace std;
 
#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
using ll = long long;
using ld = long double;
using vi = vector<int>;
using pii = array<int,2>;
 
constexpr bool dbg = false;
 
struct edge{int to;};
using graph = vector<vector<edge>>;

const int MAXA = 100'000 + 50;

struct Tree {
  typedef int T;
  static constexpr T unit = 0;
  T f(T a, T b) { return a + b; }
  vector<T> s; int n;
  Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
  void update(int pos, T val) {
    for (s[pos += n] += val; pos /= 2;)
      s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
  }
  T query(int b, int e) {
    ++e;
    T ra = unit, rb = unit;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2) ra = f(ra, s[b++]);
      if (e % 2) rb = f(s[--e], rb);
    }
    return f(ra, rb);
  }
};
 
vector<vi> treeJump(vi& P){
  int on = 1, d = 1;
  while(on < sz(P)) on *= 2, d++;
  vector<vi> jmp(d, P);
  rep(i,1,d) rep(j,0,sz(P))
    jmp[i][j] = jmp[i-1][jmp[i-1][j]];
  return jmp;
}
 
int jmp(vector<vi>& tbl, int nod, int steps){
  rep(i,0,sz(tbl))
    if(steps&(1<<i)) nod = tbl[i][nod];
  return nod;
}

void dfs(const auto& g, int i, const auto& age, const auto& bynode, auto& endpoints, auto& res) {
  trav(elem, bynode[i]) {endpoints.update(elem, 1); }
  
  res[i] = endpoints.query(0, age[i]);
  trav(e, g[i])
    dfs(g, e.to, age, bynode, endpoints, res);
 
  trav(elem, bynode[i]) {endpoints.update(elem, -1);}
}
 
int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);
 
  int n, q;
  cin >> n >> q;
  vi age(n);
  vi par(n);
  graph g(n);
  rep(i, 0, n) {
    cin >> age[i] >> par[i];
    --par[i];
    if (par[i] != i) g[par[i]].PB({i});
  }
  auto jmp = treeJump(par);
 
  vector<vi> bynode(n); // bynode[i] = {left endpoint of each query going down i's subtree}
  rep(it, 0, q) {
    int o, l, r;
    cin >> o >> l >> r;
    --o;
    int root = o;
    for (int i = sz(jmp) - 1; i >= 0; i--) {
      assert(age[root] <= r);
      auto nod = jmp[i][root];
      if (age[nod] <= r) {
        root = nod;
      }
    }
    bynode[root].PB(l);
  }
  Tree endpoints(MAXA + 1);
  vi res(n);
  dfs(g, 0, age, bynode, endpoints, res);
  trav(i, res) cout << i << " "; cout << '\n';
}
