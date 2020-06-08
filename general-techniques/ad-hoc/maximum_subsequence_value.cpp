// induction (trimming 1 number from any feasible solution maintains feasibility until n = 3)
// https://codeforces.com/contest/1365/problem/E

#include <bits/stdc++.h>
using namespace std;
 
using vi = vector<int>;
using ll = long long;
using ld = long double;
 
#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back
 
struct edge{int to;};
using graph = vector<vector<edge>>;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
 
  int n;
  cin >> n;
  vector<ll> a(n);
  trav(i, a) cin >> i;
 
  ll atleast = 0;
  if (n >= 3) {
    rep(i, 0, n) rep(j, i + 1, n) rep(k, j + 1, n) {
      atleast = max(atleast, a[i] | a[j] | a[k]);
    }
  } else if (n >= 2) {
    rep(i, 0, n) rep(j, i + 1, n)
      atleast = max(atleast, a[i] | a[j]);
  } else {
    assert(n == 1);
    atleast = a[0];
  }
  cout << atleast << '\n';
}
