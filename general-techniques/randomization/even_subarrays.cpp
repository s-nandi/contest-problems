// randomization/hashing, finding the number of subarrays where each element occurs twice
// https://codeforces.com/gym/103059/problem/E
// Note: there are other solutions that use less cheese and are more data-structurey 

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
 
const int MAXA = 200'000 + 5;
 
int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);
 
  const int MAXVAL = numeric_limits<int>::max() - 1;
  unsigned seed = chrono::high_resolution_clock::now().time_since_epoch().count();
  mt19937 gen{seed};
  uniform_int_distribution<int> dist(1, MAXVAL);
 
  vi mapping1(MAXA + 1);
  vi mapping2(MAXA + 1);
  rep(i, 0, MAXA + 1) {
    mapping1[i] = dist(gen);
    mapping2[i] = dist(gen);
  }
 
  int n;
  cin >> n;
  vector<pii> a(n);
  trav(i, a) {
    int val;
    cin >> val;
    int m1 = mapping1[val];
    int m2 = mapping2[val];
    i = {m1, m2};
  }
 
  ll sol = 0;
  map<pii, int> freq; // freq[(xor1, xor2)] = # instances of (xor1, xor2) in [lower_it, it]
  map<pii, vi> last2; // last2[hsh] = {last 2 positions where hsh appeared}
  vector<pii> acc(n + 1);
  
  int pxor1 = mapping1[0], pxor2 = mapping2[0];
  acc[0] = {pxor1, pxor2};
  freq[acc[0]]++;
  int lower_it = 0;

  rep(it, 0, n) {
    const auto& i = a[it];
 
    auto& positions = last2[i];
    if (sz(positions) >= 2) { assert(sz(positions) == 2);
      auto ind_lo = positions[0];
      positions.erase(begin(positions));
      while (lower_it < ind_lo) {
        freq[acc[lower_it]]--;
        lower_it++;
      }
    }
    positions.PB(it + 1);
 
    pxor1 ^= i[0];
    pxor2 ^= i[1];
    pii have = {pxor1, pxor2};
    acc[it + 1] = have;
    sol += freq[have];
    freq[have]++;
  }
  cout << sol << '\n';
}
