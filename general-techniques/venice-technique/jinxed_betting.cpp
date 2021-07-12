// venice set (maintain w/ sorted vector), amortization, max splits and regroups in log(size) steps
// https://open.kattis.com/problems/jinxedbetting
// 2018 Northwestern Europe Regional

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a);i<(b);++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back

using ll = long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int,int>;

struct edge{int to;};
using graph = vector<vector<edge>>;

constexpr auto dbg = false;

const ll INF = 1e18;

struct VeniceSet {
  using T = pair<ll, int>;
  
  vector<T> pq;
  ll delta{0};

  void add(ll v, int c) {
    v -= delta;
    if (!empty(pq) and pq.back().first == v)
      pq.back().second += c;
    else
      pq.push_back({v, c});
  }

  void pop() {pq.pop_back();}
  
  T correct(auto elem) {
    elem.first += delta;
    return elem;
  }
  T best() {
    return correct(pq.back());
  }
  T best2() {
    return correct(rbegin(pq)[1]);
  }
};

int lg2(int n) {
  int res = 0;
  while ((1LL << res) <= n) res++;
  return res;
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  vector<ll> a(n);
  trav(i, a) cin >> i;
  map<ll, int> freq;
  rep(i, 1, n) freq[a[i]]++;
  
  VeniceSet pq{};
  pq.add(-INF, 1);
  for (const auto& [val, cnt]: freq)
    pq.add(val, cnt);

  ll res = 0;
  auto simulate_1 = [&]() {
                      auto [v, c] = pq.best(); pq.pop();
                      auto h = c / 2;
                      pq.delta++;
                      pq.add(v, c - h);
                      if (h) pq.add(v + 1, h);
                      
                      res++;
                    };
  auto simulate_cycles = [&](ll repeats) {
                           auto [v, c] = pq.best(); pq.pop();
                           int steps = lg2(c);
                           pq.delta += repeats * steps;
                           pq.add(v + repeats * (steps - 1), c);
                           
                           res += repeats * steps;
                         };
  
  while (true) {
    auto [v, c] = pq.best();
    auto [v2, c2] = pq.best2();
    if (v > a[0]) break;
    
    auto gap1 = a[0] - v;
    auto gap2 = v - v2;

    auto delta_max = lg2(c) - 1;
    auto maintain_gap1 = delta_max ? gap1 / delta_max : INF;
    auto maintain_gap2 = gap2;

    auto full_cycles = min(maintain_gap1, maintain_gap2);
    if (full_cycles)
      simulate_cycles(full_cycles);
    else
      simulate_1();
  }
  cout << (res - 1) << '\n';
}
