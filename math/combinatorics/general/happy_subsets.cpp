// combo (overcounting, nck), 2 pointers
// https://www.codechef.com/HALO2020/problems/HAPSET

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back

const int MOD = 1000000007;
int add(int a, int b){return ((ll) a + b) % MOD;}
int mult(int a, int b){return (ll) a * b % MOD;}
int exp(int a, int b){
  int res = 1;
  for (; b; b >>= 1, a = mult(a, a))
    if (b & 1) res = mult(res, a);
  return res;
}
int divide(int a, int b) {
  return mult(a, exp(b, MOD - 2));
}

const int MAXN = 500000;
int factorial[MAXN + 5];
int nck(int n, int k) {
  if (k > n) return 0;
  return divide(factorial[n], mult(factorial[k], factorial[n - k]));
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  factorial[0] = 1;
  rep(i, 1, MAXN + 1) factorial[i] = mult(factorial[i - 1], i);

  int n, m, k;
  cin >> n >> m >> k;

  vi a(n);
  trav(i, a) cin >> i;
  sort(all(a));

  int prev_r = -1;
  int acc = 0;
  for (int l = 0, r = 0; l < n; l++) {
    while (r < n and a[r] - a[l] <= k) r++;
    int cnt = nck(r - l, m);
    int overcnt = prev_r >= l ? nck(prev_r - l, m) : 0;
    auto contrib = (cnt - overcnt + MOD) % MOD;
    acc = add(acc, contrib);
    prev_r = r;
  }
  cout << acc << '\n';
}
