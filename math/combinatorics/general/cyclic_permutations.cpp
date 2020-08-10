// combo, number of permutations s.t there are no valley positions (a > b < c) == permutations s.t each number is inserted to back or front in sorted order
// https://codeforces.com/contest/1391/problem/C

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

const int MOD = 1'000'000'007;

auto mult(ll a, ll b){return a * b % MOD;}
auto sub(ll a, ll b) {return (a - b + MOD) % MOD;}

auto factorial(int n) {
  ll res = 1;
  rep(i, 1, n + 1)
    res = mult(res, i);
  return res;
}

auto pow2(int n) {
  ll res = 1;
  rep(i, 1, n + 1)
    res = mult(res, 2);
  return res;
}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;
  cout << sub(factorial(n), pow2(n - 1)) << '\n';
}
