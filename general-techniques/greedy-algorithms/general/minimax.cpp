// greedy (best answer always 0, 1 or n - 1), try lexicographically-best construction for each case
// https://codeforces.com/contest/1530/problem/E

#include <bits/stdc++.h>
using namespace std;
 
#define rep(i,a,b) for(auto i=(a);i<(b);++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back
 
using ll = long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int,int>;
 
struct edge{int to;};
using graph = vector<vector<edge>>;
 
constexpr auto dbg = false;
 
const int ALPHA = 26;
using Table = array<int, ALPHA>;
 
int fromchar(char c){return c - 'a';}
char tochar(int i){return 'a' + i;}
 
string sortexcluding(const string& s, const vector<char>& exc) {
  string res;
  copy_if(all(s), back_inserter(res), [&exc](char c){
                                        return find(all(exc), c) == end(exc);
                                      });
  sort(all(res));
  return res;
}
 
string solve(const string& s) {
  Table freq{};
  trav(c, s) freq[fromchar(c)]++;
  
  rep(ch, 'a', 'z' + 1) if (freq[fromchar(ch)] == 1) { // scan achieve f=0; tart with ch, sort remaining
    return ch + sortexcluding(s, {ch});
  }
 
  auto ge0 = [](int v){return v > 0;};
  int a = find_if(all(freq), ge0) - begin(freq);
  int b = find_if(a + 1 + all(freq), ge0) - begin(freq);
  int c = find_if(b + 1 + all(freq), ge0) - begin(freq);
  
  char ach = tochar(a);
  char bch = tochar(b);
  char cch = tochar(c);
  
  string res;
  if (auto nota = sortexcluding(s, {ach}); sz(nota) >= freq[a] - 2) { // start with 2 a's
    res += string(2, ach);
    rep(i, 0, freq[a] - 2) {
      res += nota[i];
      res += ach;
    }
    res += nota.substr(freq[a] - 2, sz(nota) - (freq[a] - 2));
  } else if (c < sz(freq)) { // start with 1 a; have at least a,b,c
    res += ach;
    res += bch;
    res += string(freq[a] - 1, ach);
    res += cch;
    res += string(freq[b] - 1, bch);
    res += string(freq[c] - 1, cch);
    res += sortexcluding(s, {ach, bch, cch});
  } else if (b < sz(freq)) { // start with 1 a; only have a,b
    res += ach;
    res += string(freq[b], bch);
    res += string(freq[a] - 1, ach);
  } else { // only have a's, have to settle for f=n - 1
    res = string(freq[a], ach);
  }
  return res;
}
 
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
 
  int T;
  cin >> T;
  while(T--) {
    string s;
    cin >> s;
    cout << solve(s) << '\n';
  }
}
