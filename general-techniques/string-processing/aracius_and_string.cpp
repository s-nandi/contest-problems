// string processing, fix position of "c" in pattern and check validity if only instance of pattern was centered here
// https://codeforces.com/contest/1379/problem/A
// Note: can be done in O(n + m) for larger haystack/needles

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

const string pattern = "aba";
bool match_aba(const string& s) {
  rep(i, 0, sz(pattern)) {
    if (s[i] != '?' and s[i] != pattern[i])
      return false;
  }
  return true;
}

bool good(const string& s) {
  int cnt = 0;
  rep(i, 0, sz(s) - 6)
    if (s.substr(i, 7) == "abacaba")
      cnt++;
  return cnt == 1;
}
  
optional<string> canget(const string& t) {
  vi cs;
  rep(i, 3, sz(t) - 3)
    if (t[i] == 'c')
      cs.PB(i);
  trav(i, cs) {
    if (match_aba(t.substr(i - 3, 3)) and match_aba(t.substr(i + 1, 3))) {
      auto filled = t;
      copy(all(pattern), begin(filled) + i - 3);
      copy(all(pattern), begin(filled) + i + 1);
      replace(all(filled), '?', 'z');
      if (good(filled)) return {filled};
    }
  }
  return {};
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    string s;
    cin >> s;
    vi qs;
    rep(i, 0, n)
      if (s[i] == '?') qs.PB(i);
    auto initial = canget(s);
    if (initial) {cout << "Yes" << '\n' << *initial << '\n';}
    else {
      string res{};
      trav(q, qs) {
        auto temp = s;
        temp[q] = 'c';
        auto feas = canget(temp);
        if (feas) res = *feas;
      }
      if (empty(res)) cout << "No" << '\n';
      else cout << "Yes" << '\n' << res << '\n';
    }
  }
}
