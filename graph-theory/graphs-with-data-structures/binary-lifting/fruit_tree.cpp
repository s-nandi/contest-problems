// binary lifting, boyer-moore majority, offline processing (dfs)
// https://codeforces.com/group/ZFgXbZSjvp/contest/272908/problem/F
// 2020 NAPC -2

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(auto i = a; i < (b); ++i)
#define PB push_back
using vi = vector<int>;
using graph = vector<vi>;

struct info {
  int candidate{0}, cnt{0};
  info combine(const auto& o) const {
    if (candidate == o.candidate) return {candidate, cnt + o.cnt};
    else if (cnt > o.cnt) return {candidate, cnt - o.cnt};
    else return {o.candidate, o.cnt - cnt};
  }
};

const int MAXN = 250000;
const int MAXP = 20;
int n, q;
graph g;
int v[MAXN + 5];

int dep[MAXN + 5];
int par[MAXP + 1][MAXN + 5];
info maj[MAXP + 1][MAXN + 5];

int candidate[MAXN + 5];
int needed[MAXN + 5];
int actual[MAXN + 5];
vi add_at[MAXN + 5]; // add_at[i] = {x, ...} => i is a query node for query x
vi sub_at[MAXN + 5]; // sub_at[i] = {x, ...} => i is lca for query x
int counts[MAXN + 5];

void dfs(int i, int p, int d = 0) {
  if (par[0][i] != -1) return;
  par[0][i] = p;
  maj[0][i] = {v[i], 1};
  dep[i] = d;
  for (auto j: g[i])
    dfs(j, i, d + 1);
}

void build() {
  rep(d, 1, MAXP + 1) {
    rep(i, 0, n) {
      int mid = par[d - 1][i];
      par[d][i] = par[d - 1][mid];
      maj[d][i] = maj[d - 1][i].combine(maj[d - 1][mid]);
    }
  }
}

pair<int, int> lca(int i, int j) { // lca, majority candidate
  if (dep[i] < dep[j]) swap(i, j);
  auto dist = dep[i] - dep[j];
  auto acc = info{};
  for (int p = MAXP; p >= 0; p--) {
    if (dist & (1 << p)) {
      acc = acc.combine(maj[p][i]);
      i = par[p][i];
    }
  }
  if (i == j) return {i, acc.combine(maj[0][i]).candidate};
  for (int p = MAXP; p >= 0; p--) {
    int a = par[p][i], b = par[p][j];
    if (a != b) {
      acc = acc.combine(maj[p][i]).combine(maj[p][j]);
      tie(i, j) = pair{a, b};
    }
  }
  acc = acc.combine(maj[0][i]).combine(maj[0][j]).combine(maj[0][par[0][i]]);
  return {par[0][i], acc.candidate};
}

auto dist(int i, int j, int anc) {return dep[i] + dep[j] - 2 * dep[anc];}

void solve(int i, int p) {
  ++counts[v[i]];
  for(auto ind: add_at[i])
    actual[ind] += counts[candidate[ind]];
  for (auto ind: sub_at[i])
    actual[ind] -= 2 * counts[candidate[ind]] - (candidate[ind] == v[i] ? 1 : 0);
  for (auto j: g[i]) if (j != p)
    solve(j, i);
  --counts[v[i]];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    rep(i, 0, n) cin >> v[i];
    g = graph(n);
    rep(i, 0, n - 1) {
      int a, b;
      cin >> a >> b;
      --a; --b;
      g[a].PB(b);
      g[b].PB(a);
    }
    memset(par, -1, sizeof(par));
    dfs(0, 0);
    build();
    rep(i, 0, q) {
      int a, b;
      cin >> a >> b;
      auto [anc, majority] = lca(--a, --b);
      needed[i] = (dist(a, b, anc) + 1) / 2;
      candidate[i] = majority;
      add_at[a].PB(i);
      add_at[b].PB(i);
      sub_at[anc].PB(i);
    }
    solve(0, -1);
    rep(i, 0, q)
      cout << (actual[i] > needed[i] ? candidate[i] : -1) << '\n';
}
