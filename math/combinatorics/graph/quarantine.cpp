// combo, dp on tree, metagraph (reduce non-infected components to 1 weighted node), count # of paths crossing an edge with specific endpoints
// https://www.facebook.com/codingcompetitions/hacker-cup/2020/round-1/problems/C

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using vi = vector<int>;

struct edge{int to;};
using graph = vector<vector<edge>>;

constexpr char infected = '#';
constexpr char safe = '*';

void generate(auto& vec, int k, ll a, ll b, ll c) {
  rep(i, k, sz(vec)) vec[i] = int((a * vec[i - 2] + b * vec[i - 1] + c) % (i + 1) + 1);
}

void calcsize(const graph& g, int i, const string& s, auto& sizes, auto& numsafe, int p = -1) {
  sizes[i] = 1;
  numsafe[i] = (s[i] == safe);
  trav(e, g[i]) if (e.to != p) {
    calcsize(g, e.to, s, sizes, numsafe, i);
    sizes[i] += sizes[e.to];
    numsafe[i] += numsafe[e.to];
  }
}

int dfs_infected(const graph& g, const string& s, int i, vi& vis, vi& comp) {
  if (s[i] == infected) return 0;
  comp.PB(i);
  assert(!vis[i]); vis[i] = true;
  auto ns = 1;
  trav(e, g[i]) if (!vis[e.to])
    ns += dfs_infected(g, s, e.to, vis, comp);
  return ns;
}

void dfs_sparse(const graph& g, const string& s, int i, const auto& sizes, const auto& numsafe, auto& paths, auto& safesafe, int p = -1) {
  trav(e, g[i]) if (e.to != p) {
    if (s[i] == safe and s[e.to] == safe) {
      auto below = numsafe[e.to];
      auto above = numsafe[0] - below;
      safesafe += (ll) below * above;
    } else {
      auto below = sizes[e.to];
      auto above = sizes[0] - below;
      paths += (ll) below * above;
    }
    dfs_sparse(g, s, e.to, sizes, numsafe, paths, safesafe, i);
  }
}

pair<ll, ll> calcways(const graph& g, const vi& sizes, int i, auto biggest, auto second, auto totalbiggest, auto totalsecond, auto& ways, int p = -1) {
  ll cntbiggest = sizes[i] == biggest;
  ll cntsecond = (biggest != second and sizes[i] == second);
  trav(e, g[i]) if (e.to != p) {
    auto [biggestbelow, secondbelow] = calcways(g, sizes, e.to, biggest, second, totalbiggest, totalsecond, ways, i);
    auto biggestabove = totalbiggest - biggestbelow;
    auto secondabove = totalsecond - secondbelow;
    
    if (biggest == second) ways += (ll) biggestbelow * biggestabove;
    else ways += (ll) biggestbelow * secondabove + (ll) secondbelow * biggestabove;

    cntbiggest += biggestbelow;
    cntsecond += secondbelow;
  }
  return {cntbiggest, cntsecond};
}

ll nchoose2(ll n) {
  return (n * (n - 1)) / 2;
}

void solve() {
  int n, k;
  cin >> n >> k;
  string s;
  cin >> s;
  vi ed(n - 1);
  rep(i, 0, k) cin >> ed[i];
  ll A, B, C;
  cin >> A >> B >> C;
  generate(ed, k, A, B, C);
  
  graph g(n);
  rep(i, 0, n - 1) {
    auto from = i + 1;
    auto to = ed[i];
    --to;
    g[from].PB({to});
    g[to].PB({from});
  }

  vi vis(n);
  vector<pair<int, vi>> components;
  vi label(n, -1);
  int currlabel = 0;
  vi sizebylabel;
  rep(i, 0, n) {
    if (s[i] == infected) continue;
    if (vis[i]) continue;
    vi comp;
    auto compsize = dfs_infected(g, s, i, vis, comp);
    trav(node, comp) label[node] = currlabel;
    currlabel++;
    sizebylabel.PB(compsize);
    components.PB({compsize, comp});
  }
  
  auto numpairs = 0LL;
  trav(size_comp, components) numpairs += nchoose2(size_comp.first);
  
  if (sz(components) <= 1) {
    // if disconnect a safe-safe edge, need to join together two safe nodes
    // if disconnect an infected-infected or safe-infected edge, can join any two nodes
    vi sizes(n);
    vi numsafe(n);
    calcsize(g, 0, s, sizes, numsafe);
    
    auto infected_paths = 0LL;
    auto safesafe = 0LL;
    dfs_sparse(g, s, 0, sizes, numsafe, infected_paths, safesafe);

    auto mxcomp = numpairs;
    auto totalways = infected_paths + safesafe;
    cout << mxcomp << " " << totalways << '\n';
  } else {
    sort(all(components), [](const auto& a, const auto& b){return a.first > b.first;});
    auto biggest = components[0].first;
    auto second = components[1].first;

    rep(i, 0, n) {
      if (s[i] == infected) {
        label[i] = currlabel++;
        sizebylabel.PB(0);
      }
    }
    set<pii> edges;
    graph meta(currlabel);
    rep(i, 0, n) {
      trav(e, g[i]) {
        auto lab1 = label[i];
        auto lab2 = label[e.to];
        if (lab1 == lab2) continue;
        if (lab1 > lab2) swap(lab1, lab2);
        if (edges.count({lab1, lab2})) continue;
        meta[lab1].PB({lab2});
        meta[lab2].PB({lab1});
        edges.insert({lab1, lab2});
      }
    }
    int total_biggest = 0;
    int total_second = 0;
    trav(size_comp, components) {
      if (size_comp.first == biggest) total_biggest++;
      else if (size_comp.first == second) total_second++;
    }

    ll ways = 0;
    calcways(meta, sizebylabel, 0, biggest, second, total_biggest, total_second, ways);
    
    auto rejoin = (ll) biggest * second;
    auto delta = nchoose2(biggest + second) - nchoose2(biggest) - nchoose2(second);
    assert(delta == biggest * second);
    
    auto mxcomp = numpairs + delta;
    ll totalways = ways * rejoin;
    cout << mxcomp << " " << totalways << '\n';
  }
}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int T;
  cin >> T;
  rep(testnum, 1, T + 1) {
    cout << "Case #" << testnum << ": ";
    solve();
  }
}
