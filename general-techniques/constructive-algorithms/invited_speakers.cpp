// constructive (nested spirals, note this only works b/c unique x, y)
// https://codeforces.com/group/ZFgXbZSjvp/contest/274852
// 2020 NAPC 4

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back

using ptT = ll;
struct pt {
  ptT x, y;
  auto operator < (const auto& o) const {return tie(y, x) > tie(o.y, o.x);}
};
ostream& operator << (ostream& os, const pt& p) {
  return os << p.x << " " << p.y;
}

using path = vector<pt>;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

    int T;
    cin >> T;
    while(T--) {
      int n;
      cin >> n;
      vector<pt> a(n), b(n);
      rep(i, 0, n) {
        cin >> a[i].x >> a[i].y;
      }
      rep(i, 0, n) {
        cin >> b[i].x >> b[i].y;
      }
      sort(all(a)); sort(all(b));
      vector<path> sol;
      rep(i, 0, n) { // all intermediate points are unique to this path
        int delta = 101 + i;
        pt p1 = a[i];
        pt p2{delta, a[i].y};
        pt p3{delta, delta};
        pt p4{-delta, delta};
        pt p5{-delta, b[i].y};
        pt p6 = b[i];
        sol.PB({p1, p2, p3, p4, p5, p6});
      }
      trav(p, sol) {
        cout << sz(p) << '\n';
        trav(elem, p)
          cout << elem << '\n';
      }
    }
}
