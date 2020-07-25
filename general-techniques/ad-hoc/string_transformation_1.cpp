// simulation, greedy (for letter x move all instances up to smallest bigger letter -- optimal to not leave any behind)
// https://codeforces.com/contest/1383/problem/A

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

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;
    bool bad = false;
    vector<set<char>> bychar(20);
    rep(i, 0, n) {
      if (s[i] > t[i]) bad = true;
      else if (s[i] < t[i]) {
        bychar[s[i] - 'a'].insert(t[i]);
      }
    }
    if (bad) {cout << -1 << '\n'; continue;}
    int res = 0;
    rep(c, 0, 20) {
      if (!empty(bychar[c]) and *begin(bychar[c]) == c) {
        bychar[c].erase(begin(bychar[c]));
      }
      if (sz(bychar[c]) == 0) continue;
      auto mn = *begin(bychar[c]);
      res++;
      trav(elem, bychar[c]) {
        if (elem == mn) continue;
        assert(elem > mn);
        bychar[mn - 'a'].insert(elem);
      }
    }
    cout << res << '\n';
  }
}
