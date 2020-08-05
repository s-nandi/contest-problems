// greedy (why does this work IFF you try both removing and not removing top of weighted1 first??)
// https://codeforces.com/contest/1399/problem/E2

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
 
struct edge{int to; ll w; int c;};
using graph = vector<vector<edge>>;
  
auto getpriority(ll val, ll cnt) {
  return (val - val / 2) * cnt;
}
 
int dfs(auto& g, int i, ll acc, ll& allsum, auto& weighted1, auto& weighted2, int par = -1) {
  int oedge = 0;
  auto tot_leaves = 0;
  trav(e, g[i]) if (e.to != par) {
    auto nleaves = dfs(g, e.to, acc + e.w, allsum, weighted1, weighted2, i);
    if (dbg) cout << "Got : " << e.w << " with " << nleaves << " leaves" << " with cost: " << e.c << endl;
    if (e.c == 1) {
      weighted1.push({getpriority(e.w, nleaves), nleaves, e.w});
    } else {
      assert(e.c == 2);
      weighted2.push({getpriority(e.w, nleaves), nleaves, e.w});
    }
    oedge++;
    tot_leaves += nleaves;
  }
  if (oedge == 0) {
    tot_leaves++;
    allsum += acc;
  }
  return tot_leaves;
}
 
ll remove2(auto& pq, bool dryrun) {
  ll saved = 0;
  auto [saved_first, nleaves, weight] = pq.top(); pq.pop();
  saved += saved_first;
  saved += max(getpriority(weight / 2, nleaves), (!empty(pq) ? get<0>(pq.top()) : 0LL));
  if (dryrun) {
    pq.push({saved_first, nleaves, weight});
  } else {
    pq.push({getpriority(weight / 2, nleaves), nleaves, weight / 2});
    auto [saved_second, nleaves2, weight2] = pq.top(); pq.pop();
    assert(saved_first + saved_second == saved);
    pq.push({getpriority(weight2 / 2, nleaves2), nleaves2, weight2 / 2});
  }
  return saved;
}
 
constexpr auto INF = 1031231234;
 
auto solve(auto weighted1, auto weighted2, ll allsum, ll s) {
  int steps = 0;
  while (allsum > s) {
    if (!empty(weighted1) and allsum - get<0>(weighted1.top()) <= s) {
      steps++;
      break;
    }
    auto option_ones = empty(weighted1) ? -INF : remove2(weighted1, true);
    auto option_twos = empty(weighted2) ? -INF : get<0>(weighted2.top());
    if (option_ones > option_twos) {
      remove2(weighted1, false);
      allsum -= option_ones;
    } else {
      auto [savings, nleaves, weight] = weighted2.top(); weighted2.pop();
      assert(savings == option_twos);
      allsum -= savings;
      weighted2.push({getpriority(weight / 2, nleaves), nleaves, weight / 2});
    }
    steps += 2;
  }
  return steps;
}
 
int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);
 
  int T;
  cin >> T;
  while(T--) {
    int n; ll s;
    cin >> n >> s;
    graph g(n);
    rep(i, 0, n - 1) {
      int u, v; ll w; int c;
      cin >> u >> v >> w >> c;
      --u; --v;
      g[u].PB({v, w, c});
      g[v].PB({u, w, c});
    }
    priority_queue<tuple<ll, int, ll>> weighted1, weighted2; // priority, nleaves, weight
    ll allsum{0};
    dfs(g, 0, 0LL, allsum, weighted1, weighted2);
    auto possible1 = solve(weighted1, weighted2, allsum, s);
    auto possible2 = INF;
    if (!empty(weighted1)) {
      auto [savings, nleaves, weight] = weighted1.top(); weighted1.pop();
      allsum -= savings;
      weighted1.push({getpriority(weight / 2, nleaves), nleaves, weight / 2});
      possible2 = 1 + solve(weighted1, weighted2, allsum, s);
    }
    auto best = min(possible1, possible2);
    cout << best << '\n';
  }
}
