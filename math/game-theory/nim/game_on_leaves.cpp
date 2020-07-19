// nim on tree (parity invariant), properties only matter mod (x + 1) in "remove <= x stones in 1 step" nim variant

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int,int>;

#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for (auto& a: x)
#define all(x) begin(x), end(x)
#define sz(x) (int)size(x)
#define PB push_back

struct edge{int to;};
using graph = vector<vector<edge>>;

const string firstplayer = "Ayush";
const string secondplayer = "Ashish";

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  while(T--) {
    int n, x;
    cin >> n >> x;
    --x;
    graph g(n);
    rep(i, 0, n - 1) {
      int u, v;
      cin >> u >> v;
      --u; --v;
      g[u].PB({v});
      g[v].PB({u});
    }
    if (sz(g[x]) <= 1) cout << firstplayer << '\n';
    else if (n & 1) cout << secondplayer << '\n';
    else cout << firstplayer << '\n';
  }
}
