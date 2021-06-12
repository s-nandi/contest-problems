// amortized argument (there are <= |sum length| pairs of (s, t) strings s.t. t is a prefix of s), hashing
// https://codeforces.com/gym/102861/problem/C
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
 
const int MAXN = 1'000'000 + 500;
const int alpha = 727;
const int MOD[2] = {1000000007, 1000000009};
 
int alphs[2][MAXN];
void precompute_hash() {
  rep(t, 0, 2) {
    alphs[t][0] = 1;
    rep(i, 1, MAXN) 
      alphs[t][i] = (ll)alpha * alphs[t][i - 1] % MOD[t];
  }
}
 
using hashT = array<int, 2>;
struct hasher {
  array<vi, 2> h;
  hasher() { rep(t, 0, 2) h[t].assign(1, 0); }
  static int multpow(int v, int p, int t){
    return (ll) v * alphs[t][p] % MOD[t];
  }
  int mapping(char c) { return c - 'a' + 1; } 
  int length() { return sz(h[0]) - 1; }
  auto query(int l, int r){
    hashT res;
    rep(t, 0, 2)
      res[t] = multpow((h[t][r + 1] - h[t][l] + MOD[t]) % MOD[t],
                       MAXN - l - 1, t);
    return res;
  }
  void push(char c){
    rep(t, 0, 2) {
      h[t].PB(h[t].back() + multpow(mapping(c), sz(h[t]), t));
      h[t].back() %= MOD[t];
    }
  }
  void pop(){ rep(t, 0, 2) h[t].pop_back(); }
};

int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);
 
  precompute_hash();
  
  int n, m;
  cin >> n >> m;
  vector<string> a(n), b(m);
  trav(s, a) cin >> s;
  trav(s, b) cin >> s;
 
  vector<hasher> ah(n), bh(m);
  vector<pair<hashT, int>> amap, bmap;
  auto init_hashes = [&](const auto& strings, auto& hashes, auto& mapping) {
                       rep(i, 0, sz(strings)) {
                         trav(c, strings[i]) hashes[i].push(c);
                         mapping.PB({hashes[i].query(0, sz(strings[i]) - 1), i});
                       }
                       sort(all(mapping));
                     };
  init_hashes(a, ah, amap);
  init_hashes(b, bh, bmap);
  auto indexof = [&](const auto& mapping, auto elem) {
                   auto it = lower_bound(all(mapping), pair{elem, -1});
                   if (it != end(mapping) and it -> first == elem) return it -> second;
                   else return -1;
                 };
 
  map<hashT, array<vector<pair<int, int>>, 2>> bygap; // bygap[gap hash] = {{pairs in A}, {pairs in B}}
  vi apeculiar(n, true), bpeculiar(m, true);
  rep(i, 0, n) {
    rep(len, 1, sz(a[i])) {
      auto pref_hash = ah[i].query(0, len - 1);
      int i2 = indexof(amap, pref_hash);
      if (i2 != -1) {
        auto gap_hash = ah[i].query(len, sz(a[i]) - 1);
        bygap[gap_hash][0].PB({i, i2});
      }
    }
  }
  rep(j, 0, m) {
    rep(len, 1, sz(b[j])) {
      auto suff_hash = bh[j].query(sz(b[j]) - len, sz(b[j]) - 1);
      int j2 = indexof(bmap, suff_hash);
      if (j2 != -1) {
        auto gap_hash = bh[j].query(0, sz(b[j]) - len - 1);
        if (bygap.count(gap_hash)) {
          bygap[gap_hash][1].PB({j, j2});
        }
      }
    }
  }
 
  auto process_pairs = [&](auto& peculiar, const auto& vec) {
                         for (const auto& [i, j]: vec) {
                           peculiar[i] = peculiar[j] = false;
                         }
                       };
  for (const auto& [hsh, pairs_ab]: bygap) {
    const auto& [apairs, bpairs] = pairs_ab;
    if (!empty(apairs) and !empty(bpairs)) {
      process_pairs(apeculiar, apairs);
      process_pairs(bpeculiar, bpairs);
    }
  }
  cout << accumulate(all(apeculiar), 0) << " " << accumulate(all(bpeculiar), 0) << '\n';
}
