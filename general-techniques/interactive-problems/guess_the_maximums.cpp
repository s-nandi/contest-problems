// interactive, binary search
// https://codeforces.com/contest/1363/problem/D

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back

vi getindices(const auto& ps, int l, int r) {
  vi res;
  rep(i, l, r + 1) {
    trav(j, ps[i])
      res.PB(j);
  }
  return res;
}

int ask(const auto& vec) {
  cout << "? " << sz(vec) << " ";
  trav(i, vec) cout << i << " "; cout << endl;
  int res;
  cin >> res;
  if (res == -1) exit(0);
  return res;
}

void answer(const auto& vec) {
  cout << "! ";
  trav(i, vec) cout << i << " "; cout << endl;
  string res;
  cin >> res;
  if (res != "Correct") exit(0);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  while(T--) {
    int n, k;
    cin >> n >> k;
    vector<vi> ps(k);
    trav(row, ps) {
      int s;
      cin >> s;
      row.resize(s);
      trav(i, row) cin >> i;
    }
    auto allind = vi(n);
    iota(all(allind), 1);
    int mx = ask(allind);
    int lo = 0, hi = k - 1;
    while (lo < hi) {
      int mid = (lo + hi) / 2;
      if (ask(getindices(ps, lo, mid)) == mx) {
        hi = mid;
      } else {
        lo = mid + 1;
      }
    }
    assert(lo == hi);
    
    vi res(k);
    rep(i, 0, lo) res[i] = mx;
    rep(i, hi + 1, k) res[i] = mx;
    
    set<int> exclude;
    rep(i, 1, n + 1) exclude.insert(i);
    trav(i, ps[lo]) exclude.erase(i);
    
    res[lo] = ask(exclude);
    answer(res);
  }
}
