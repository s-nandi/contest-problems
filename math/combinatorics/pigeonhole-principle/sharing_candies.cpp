// pigeonhole principle
// https://codesprintla21open-individual.kattis.com/problems/codesprintla21.sharingcandies

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
using ll = long long;
using ld = long double;
using vi = vector<int>;
using pii = array<int,2>;

constexpr bool dbg = false;

struct edge{int to;};
using graph = vector<vector<edge>>;

int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;
  vi a(n);
  trav(i, a) cin >> i;

  auto printsol = [&](int i, int j) {
                    ++i, ++j;
                    cout << (j - i + 1) << '\n';
                    rep(it, i, j + 1) cout << it << " "; cout << '\n';
                    exit(0);
                  };

  int acc = 0;
  vi last(n, -1);
  rep(i, 0, n) {
    acc = (acc + a[i]) % n;
    if (acc == 0) {
      printsol(0, i);
    } else if (last[acc] != -1) {
      printsol(last[acc] + 1, i);
    } else {
      last[acc] = i;
    }
  }
}
