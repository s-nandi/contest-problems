// ad-hoc, permutation cycles
// https://codeforces.com/contest/1385/problem/G
// Note: could also be solved via implicit bipartite graph

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
    vi a(n), b(n);
    trav(i, a){cin >> i; --i;}
    trav(i, b){cin >> i; --i;}
    vector<vi> pos(n);
    rep(i, 0, n) {
      pos[a[i]].PB(i);
      pos[b[i]].PB(i);
    }
    bool impossible = false;
    rep(i, 0, n) {
      if (sz(pos[i]) != 2) impossible = true;
    }
    if (impossible) {cout << -1 << '\n'; continue;}

    int acc = 0;
    vi sol;
    vi vis(n);
    rep(i, 0, n) {
      auto curr = a[i];
      auto ind = i;
      vi chain1, chain2;
      while (!vis[curr]) {
        if (a[ind] == curr) chain1.PB(ind);
        else chain2.PB(ind);
        vis[curr] = true;
        
        auto nind = pos[curr][0] == ind ? pos[curr][1] : pos[curr][0]; 
        auto ncurr = a[nind] == curr ? b[nind] : a[nind];

        ind = nind;
        curr = ncurr;
      }

      if (sz(chain1) > sz(chain2)) swap(chain1, chain2);
      acc += sz(chain1);
      trav(i, chain1) sol.PB(i);
    }
    cout << acc << '\n';
    trav(i, sol) cout << (i + 1) << " "; cout << '\n';
  }
}
