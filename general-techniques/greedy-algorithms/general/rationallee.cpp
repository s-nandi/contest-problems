// greedy, sorting
// https://codeforces.com/contest/1369/problem/C

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
  while(T--) {
    int n, k;
    cin >> n >> k;
    vi a(n);
    trav(i, a) cin >> i;
    vi b(k);
    trav(i, b) cin >> i;
    sort(all(b), greater<>{});
    sort(all(a));
 
    ll res = 0;
    while(!b.empty() and b.back() == 1) {
      res += 2 * a.back();
      b.pop_back();
      a.pop_back();
    }
    int it = 0;
    rep(i, 0, sz(b)) {
      res += a[it];
      rep(j, 0, b[i] - 1) {
        it++;
      }
    }
    rep(i, 0, sz(b)) {
      if (b[i] == 1) res += a[it];
      res += a[it++];
    }
    cout << res << '\n';
  }
}
