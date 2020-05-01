// linearity of expectations, bitmasks
// https://utipc19.kattis.com/problems/utipc19.socialdancers
// 2019 Spring UT Programming Contest

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;
using ld = long double;

#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back

struct edge{int to;};
using graph = vector<vector<edge>>;

int index(const string& s) {
  if (s == "swing") return 1 << 0;
  else if (s == "bachata") return 1 << 1;
  else return 1 << 2;
}

vi readdancers(int cnt) {
  vi res(1 << 3);
  rep(i, 0, cnt) {
    int k;
    cin >> k;
    int bm = 0;
    rep(it, 0, k) {
      string s;
      cin >> s;
      bm |= index(s);
    }
    res[bm]++;
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int l, f; ll m;
  cin >> l >> f >> m;
 
  auto a = readdancers(l);
  auto b = readdancers(f);

  vi by_numbits(4);
  rep(bm, 1, 1 << 3) {
    int nb = __builtin_popcount(bm);
    int cnt = min(a[bm], b[bm]);
    by_numbits[nb] += cnt;
  }
  ld ev = 0;
  rep(nb, 1, 4) {
    ev += nb / 3.L * by_numbits[nb];
  }
  cout << setprecision(11) << fixed << ev * m << '\n';   
}
