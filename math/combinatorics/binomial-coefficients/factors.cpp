// multinomial (handling overflow risk), backtrack
// https://codeforces.com/gym/101208/problem/D
// 2013 World Finals

#include <bits/stdc++.h>
using namespace std;
 
#define rep(i,a,b) for(auto i=(a);i<(b);++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back
 
using ll = unsigned long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int,int>;
 
struct edge{int to;};
using graph = vector<vector<edge>>;
 
constexpr auto dbg = false;
 
const auto MAXV = (1ULL << 63) - 1;
 
map<ll, ll> ans;
void store_candidate(ll a, ll b) {
  if (ans.count(a)) ans[a] = min(ans[a], b);
  else ans[a] = b;
}

ll mult(ll a, ll b) {
  return b > MAXV / a ? MAXV + 1 : a * b;
}
 
vi primes{2};
int getprime(int ind) {
  for (int i = primes.back() + 1; ind >= sz(primes); i++) {
    bool isprime = true;
    trav(j, primes) isprime &= i % j != 0;
    if (isprime) primes.PB(i);
  }
  return primes[ind];
}
 
ll multinomial(const vi& vec) {
  ll num = 1, res = 1;
  trav(elem, vec) rep(i, 1, elem + 1) {
    auto g = gcd(res, i), g2 = gcd(num, i / g);
    res = mult(res / g, num++ / g2);
    if (res > MAXV) break;
  }
  return res;
}
 
bool partition_count(int s, int pos, vi& vec, ll k) {
  if (k > MAXV) return false;
  ll mval = multinomial(vec);
  if (mval > MAXV) return false;
  store_candidate(mval, k);
  rep(i, pos, s) {
    if (i == 0 or vec[i - 1] >= 1 + vec[i]) {
      vec[i]++;
      partition_count(s, i, vec, mult(k, getprime(i)));
      vec[i]--;
    }
  }
  return true;
}
 
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  ll pmult = 1;
  for (int s = 1; ; s++) {
    vi vec(s, 1);
    pmult = mult(pmult, getprime(s - 1));
    if (!partition_count(s, 0, vec, pmult)) break;
  }
  
  ll v;
  while(cin >> v and v > 0)
    cout << v << " " << ans[v] << '\n';
}
