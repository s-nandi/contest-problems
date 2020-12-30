// greedy, if there is a palindrome of length k > 3 there must also be a palindrome of length 2 or 3, fix all 2/3 length palindromes greedily as late as possible
// https://codeforces.com/contest/1466/problem/C

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
#define cauto const auto
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using vi = vector<int>;

struct edge{int to;};
using graph = vector<vector<edge>>;

constexpr auto dbg = false;

int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;
  while(T--) {
    string s;
    cin >> s;
    int n = sz(s);
    int res = 0;
    rep(i, 0, n) {
      bool changed = false;
      if (i >= 1 and s[i] == s[i - 1]) changed = true;
      if (i >= 2 and s[i] == s[i - 2]) changed = true;

      if (changed) {
        s[i] = '?'; // can always change to 'some' letter that doesn't interfere with any interacting letters (just change to some letter not in [i - 3, i + 3] -- always possible)
        res++;
      }
    }
    cout << res << '\n';
  }
}
