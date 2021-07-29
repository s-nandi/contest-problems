// huffman coding, small number of equivalence classes (order of letters doesn't affect probability) -- simulate & skip steps
// https://open.kattis.com/problems/weather
// 2015 World Finals

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

constexpr auto dbg = false;

struct edge{int to;};
using graph = vector<vector<edge>>;

template <typename T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;

ll multinomial(auto& v) {
  ll c = 1, m = v.empty() ? 1 : v[0];
  rep(i,1,sz(v)) rep(j,0,v[i])
    c = c * ++m / (j+1);
  return c;
}

void recur(int n, int i, const auto& a, auto& equiv, auto& cnt, ld prob = 1.L) {
  if (n == 0) equiv.push({prob, multinomial(cnt)});
  else if (i < sz(a)) {
    cnt[i]++;
    recur(n - 1, i, a, equiv, cnt, prob * a[i]);
    cnt[i]--;
    recur(n, i + 1, a, equiv, cnt, prob);       
  }
}

int32_t main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  array<ld, 4> a;
  trav(i, a) cin >> i;
  
  array<int, 4> cnt{};
  min_queue<pair<ld, ll>> pq;
  recur(n, 0, a, pq, cnt);
  
  ld res = 0.L;
  auto huffman = [&](ld p1, ll c1, ld p2, ll c2) {
                   auto c = min(c1, c2);
                   pq.push({p1 + p2, c});
                   res += (p1 + p2) * c;
                   if (c1 - c > 0) pq.push({p1, c1 - c});
                   if (c2 - c > 0) pq.push({p2, c2 - c});
                 };
  while (!empty(pq)) {
    auto [p1, c1] = pq.top(); pq.pop();
    if (c1 == 1 and empty(pq)) break;
    
    if (c1 > 1) {
      auto h1 = c1 / 2;
      auto h2 = c1 - h1;
      huffman(p1, h1, p1, h2);
    } else {
      auto [p2, c2] = pq.top(); pq.pop();
      huffman(p1, c1, p2, c2);
    }
  }
  cout << fixed << setprecision(11) << res << '\n';
}
