// game, proofy (# of moves is fixed regardless of choices)
// https://codeforces.com/contest/1373/problem/B

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using ii = pair<int, int>;
using vi = vector<int>;

#define rep(i, a, b) for(auto i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back

struct edge{int to;};
using graph = vector<vector<edge>>;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  while (T--) {
    string s;
    cin >> s;

    int moves = 0;
    while (true) {
      bool nothing = true;
      int pos = -1;
      rep(i, 0, sz(s) - 1) {
        if (s[i] != s[i + 1]) {
          nothing = false;
          pos = i;
          break;
        }
      }
      if (nothing) break;
      else {
        moves++;
        string t;
        rep(i, 0, sz(s)) {
          if (i != pos and i != pos + 1)
            t += s[i];
        }
        s = t;
      }
    }
    cout << ((moves & 1) ? "DA" : "NET") << '\n';
  }
}
