// invariant (game can continue iff >= 3 distinct characters => ending state has even or odd parity based on start==end; # of viable moves has parity equal to (startparity - endparity))
// https://open.kattis.com/problems/joylessgame
// 2018 Vietname ICPC National Programming Contest

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using vi = vector<int>;

struct edge{int to;};
using graph = vector<vector<edge>>;

const std::string firstplayer = "Chikapu";
const std::string secondplayer = "Bash";

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;
  while(T--) {
    string s;
    cin >> s;
    int endparity = s[0] == s.back();
    if ((sz(s) & 1) == endparity) cout << secondplayer << '\n';
    else cout << firstplayer << '\n';
  }
}
