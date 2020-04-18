// prefix function (longest match in kmp)
// https://codeforces.com/contest/1200/problem/E

#include <bits/stdc++.h>
using namespace std;
 
using vi = vector<int>;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define sz(x) (int)(x).size()
 
vi prefix_function(const string &s) {
  vi pf(sz(s));
  rep(i, 1, sz(s)) {
    int j = pf[i - 1];
    while (j > 0 and s[i] != s[j]) j = pf[j - 1];
    pf[i] = (s[i] == s[j]) ? j + 1 : 0;
  }
  return pf;
}
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int n;
  cin >> n;
  string acc;
  rep(it, 0, n) {
    string s;
    cin >> s;
    int len = min(sz(s), sz(acc));
    string suff = acc.substr(sz(acc) - len, len);
    string pref = s.substr(0, len);
    auto pf = prefix_function(pref + "*" + suff);
    int matched_len = pf.back();
    acc += s.substr(matched_len, sz(s) - matched_len);
  }
  cout << acc << '\n';
}
