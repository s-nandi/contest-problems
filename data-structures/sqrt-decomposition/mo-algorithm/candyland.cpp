// 3D Mo's on trees
// https://napc21.kattis.com/problems/napc21.candyland

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
using piii = tuple<int, int, int>;

constexpr auto dbg = false;

using graph = vector<vector<int>>;

constexpr int MAXN = 100'000 + 50;
constexpr int blk = 4000; // ~N / Q^(1/3)
const int INF = 1031231234;

int V[MAXN];
int W[MAXN];
int C[MAXN];

int freq[MAXN];
bool dynamic[MAXN];
bool included[MAXN];
int last[MAXN];
vector<array<int, 3>> dynamics;
vector<array<int, 3>> queries;
ll ans = 0;

void changecnt(int col, int delta) {
  if (delta > 0)
    ans += (ll) W[freq[col]++] * V[col];
  else
    ans -= (ll) W[--freq[col]] * V[col];
}

void add(int ind, int end) {
  if (!dynamic[ind])
    changecnt(C[ind], 1);
  else
    included[ind] = true;
}
void del(int ind, int end) {
  if (!dynamic[ind])
    changecnt(C[ind], -1);
  else
    included[ind] = false;
}
ll calc(int tm) {
  for (const auto& [t, x, y]: dynamics) {
    last[x] = -INF;
  }
  for (const auto& [t, x, y]: dynamics) { // C[x] = y at time t
    if (t < tm) {
      last[x] = max(last[x], t);
    }
  }
  for (const auto& [t, x, y]: dynamics) if (included[x] and t == last[x]) {
      changecnt(y, 1);
    }
  auto res = ans;  
  for (const auto& [t, x, y]: dynamics) if (included[x] and t == last[x]) {
      changecnt(y, -1);
    }
  return res;
}

vector<ll> moTree(const vector<array<int, 3>>& Q, vector<vi>& ed, int root=0){
  int N = sz(ed), pos[2] = {};
  vi s(sz(Q)), I(N), L(N), R(N), in(N), par(N);
  vector<ll> res(sz(Q));
  add(0, 0), in[0] = 1;
  auto dfs = [&](int x, int p, int dep, auto& f) -> void {
               par[x] = p;
               L[x] = N;
               if (dep) I[x] = N++;
               for (int y : ed[x]) if (y != p) f(y, x, !dep, f);
               if (!dep) I[x] = N++;
               R[x] = N;
             };
  dfs(root, -1, 0, dfs);
#define K(x) pii(I[x[1]] / blk, I[x[2]] ^ -(I[x[1]] / blk & 1))
  iota(all(s), 0);
  sort(all(s), [&](int s, int t){ return K(Q[s]) < K(Q[t]); });
  for (int qi : s) rep(end,0,2) {
      int &a = pos[end], b = Q[qi][end + 1], i = 0;
#define step(c) { if (in[c]) { del(a, end); in[a] = 0; }        \
        else { add(c, end); in[c] = 1; } a = c; }
      while (!(L[b] <= L[a] && R[a] <= R[b]))
        I[i++] = b, b = par[b];
      while (a != b) step(par[a]);
      while (i--) step(I[i]);
      if (end) {
        res[qi] = calc(Q[qi][0]);
      }
    }
  return res;
}

int32_t main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m, q;
  cin >> n >> m >> q;
  rep(i, 0, m) cin >> V[i];
  rep(i, 0, n) cin >> W[i];
  graph g(n);
  rep(it, 0, n - 1) {
    int u, v;
    cin >> u >> v;
    --u; --v;
    g[u].PB(v);
    g[v].PB(u);
  }
  rep(i, 0, n) {
    cin >> C[i];
    --C[i];
  }
  vector<array<int, 3>> qs;
  rep(it, 0, q) {
    int t, x, y;
    cin >> t >> x >> y;
    --x; --y;
    qs.PB({t, x, y});
  }

  vector<ll> res;
  int nb = (sz(qs) + blk - 1) / blk;
  rep(b, 0, nb) {
    int lo = b * blk;
    int hi = min(sz(qs), (b + 1) * blk);
    memset(freq, 0, sizeof(freq));
    dynamics.clear();
    queries.clear();
    ans = 0;

    rep(it, lo, hi) {
      const auto& [t, x, y] = qs[it];
      if (t == 0) {
        included[x] = false;
        dynamic[x] = true;
        dynamics.PB({it, x, y});
      } else {
        queries.PB({it, x, y});
      }
    }
    rep(x, 0, n) if (dynamic[x])
      dynamics.PB({-1, x, C[x]});

    auto got = moTree(queries, g);
    trav(elem, got) cout << elem << '\n';;

    rep(it, lo, hi) {
      const auto& [t, x, y] = qs[it];
      if (t == 0) {
        dynamic[x] = false;
        C[x] = y;
      }
    }
  }
}
