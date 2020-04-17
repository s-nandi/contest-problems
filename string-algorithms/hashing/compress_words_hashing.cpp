// hashing (add front, add back)
// https://codeforces.com/contest/1200/problem/E

#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define sz(x) (int)(x).size()
 
const int alpha = 317;
const int MAXN = 1000000;
const int MOD = 1000000007;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  vector<ll> pows(MAXN + 1);
  pows[0] = 1;
  rep(i, 1, MAXN + 1)
    pows[i] = pows[i - 1] * alpha % MOD;
  
  int n;
  cin >> n;
  string acc;
  rep(it, 0, n) {
    string s;
    cin >> s;
    int matched = 0;
    ll h1 = 0, h2 = 0;
    rep(i, 0, min(sz(s), sz(acc))) {
      h1 = (h1 * alpha + s[i]) % MOD;
      h2 = (h2 + pows[i] * acc[sz(acc) - 1 - i]) % MOD;
      if (h1 == h2) matched = i + 1;
    }
    rep(i, matched, sz(s))
      acc += s[i];
  }
  cout << acc << '\n';
}
