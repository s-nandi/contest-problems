// feasibility checking (finding invariant)
// https://codeforces.com/contest/1365/problem/F

#include <bits/stdc++.h>
using namespace std;
 
using vi = vector<int>;
using ll = long long;
using ld = long double;
using ii = pair<int, int>;
 
#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back
 
struct edge{int to;};
using graph = vector<vector<edge>>;
 
ii normalize(int i, int j){
  if (i > j) swap(i, j);
  return {i, j};
}
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
 
  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vi a(n), b(n);
    trav(i, a) cin >> i;
    trav(i, b) cin >> i;
 
    bool bad = false;
    if (n & 1) {
      int mid = n / 2;
      if (a[mid] != b[mid]) {
        bad = true;
      }
    }
    if (!bad) {
      map<ii, int> have;
      rep(i, 0, n / 2) {
        auto j = n - 1 - i;
        have[normalize(a[i], a[j])]++;
      }
      rep(i, 0, n / 2) {
        auto j = n - 1 - i;
        auto need = normalize(b[i], b[j]);
        if (!have.count(need)) {
          bad = true;
          break;
        } else {
          if (--have[need] == 0)
            have.erase(need);
        }
      }
    }
    cout << ((bad) ? "No" : "Yes") << '\n';
  }
}
