// bellman ford (negative cycle check), log transform, reverse edges to only do 1 spfa iteration
// https://codesprintla21open-individual.kattis.com/problems/codesprintla21.villagertrading

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

ld eps = 1e-8;
bool approx(ld a, ld b) { return abs(a - b) < eps; }

const ld inf = 1e18;
struct Ed { int a, b; ld w; int s() { return a < b ? a : -a; }};
struct Node { ld dist = inf; int prev = -1; };

void bellmanFord(vector<Node>& nodes, vector<Ed>& eds, int s) {
  nodes[s].dist = 0;
  sort(all(eds), [](Ed a, Ed b) { return a.s() < b.s(); });

  int lim = sz(nodes) / 2 + 2; // /3+100 with shuffled vertices
  rep(i,0,lim) for (Ed ed : eds) {
    Node cur = nodes[ed.a], &dest = nodes[ed.b];
    if (approx(abs(cur.dist), inf)) continue;
    ld d = cur.dist + ed.w;
    if (d < dest.dist) {
      dest.prev = ed.a;
      dest.dist = (i < lim-1 ? d : -inf);
    }
  }
  rep(i,0,lim) for (Ed e : eds) {
    if (nodes[e.a].dist == -inf)
      nodes[e.b].dist = -inf;
  }
}

int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  map<string, int> indexer;
  auto indexof = [&](const string& s) {
                   if (indexer.count(s)) return indexer[s];
                   else {
                     int res = sz(indexer);
                     indexer[s] = res;
                     return res;
                   }
                 };

  vector<tuple<int, int, ld>> trade; // item i, item j, log(ratio)
  rep(it, 0, n) {
    int k;
    cin >> k;
    rep(__, 0, k) {
      int a1, a2;
      string s1, s2;
      cin >> a1 >> s1 >> a2 >> s2;
      auto ind1 = indexof(s1);
      auto ind2 = indexof(s2);
      auto rat = log((ld) a1) - log((ld) a2);
      trade.PB({ind2, ind1, rat});
    }
  }
  int target = indexof("Emerald");
  auto nn = sz(indexer);

  vector<Node> nodes(nn);
  vector<Ed> eds;
  eds.reserve(sz(trade));
  for (const auto& [i, j, rat]: trade) {
    auto& ed = eds.emplace_back();
    ed.a = i; ed.b = j; ed.w = rat;
  }

  bellmanFord(nodes, eds, target);    
  bool havecycle = false;
  rep(j, 0, nn)
    havecycle |= nodes[j].dist == -inf;
  cout << (havecycle ? "yes" :  "no") << '\n';
}
