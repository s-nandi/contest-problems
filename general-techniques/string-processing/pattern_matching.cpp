// string processing (finding superprefix and supersuffix)
// https://codingcompetitions.withgoogle.com/codejam/round/000000000019fd74/00000000002b3034
// 2020 GCJ 1A

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

bool has_prefix(const string& a, const string& b) {
  if (sz(b) > sz(a)) return false;
  rep(i, 0, sz(b))
    if (a[i] != b[i]) return false;
  return true;
}

int superprefix(const auto& ps) {
  rep(i, 0, sz(ps)) {
    bool good = true;
    rep(j, 0, sz(ps))
      if (!has_prefix(ps[i], ps[j]))
        good = false;
    if (good) return i;
  }
  return -1;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int num_tests;
  cin >> num_tests;
  for (int test_num = 1; test_num <= num_tests; test_num++) {
    int n;
    cin >> n;
    vector<string> a(n);
    vector<string> pref(n), suff(n), mid(n);
    rep(i, 0, n) {
      cin >> a[i];
      int f = sz(a[i]), l = -1;
      rep(j, 0, sz(a[i])) {
        if (a[i][j] == '*') {
          f = min(f, j);
          l = max(l, j);
        }
      }
      rep(j, 0, f) pref[i] += a[i][j];
      rep(j, f, l + 1) mid[i] += a[i][j];
      rep(j, l + 1, sz(a[i])) suff[i] += a[i][j];
      reverse(all(suff[i]));
    }
    string res{};
    int pind = superprefix(pref);
      int sind = superprefix(suff);
      if (pind != -1 and sind != -1) {
        string mids = accumulate(all(mid), ""s);
        reverse(all(suff[sind]));
        res += pref[pind];
        res += mids;
        res += suff[sind];
        res.erase(remove(all(res), '*'), end(res));
      } else res = '*';
      cout << "Case #" << test_num << ": " << res << '\n';
  }
}
