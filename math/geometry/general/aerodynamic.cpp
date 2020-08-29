// geometry (symmetry across origin), finding property: opposite sides must be opposites (follows from, if vector v is in output shape, -v is also in output shape)
// https://codeforces.com/contest/1299/problem/B

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

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);
  
  int n;
  cin >> n;
  vector<pii> a(n);
  trav(p, a) cin >> p.first >> p.second;

  auto sub = [](const pii& a, const pii& b) {return pii{a.first - b.first, a.second - b.second};};
  auto opp = [](const pii& a){return pii{-a.first, -a.second};};
  
  vector<pii> lines(n);
  rep(i, 0, n) lines[i] = sub(a[i], a[(i + 1) % n]);
  bool good = !(n & 1);
  int h = n / 2;
  rep(i, 0, n) good &= opp(lines[i]) == lines[(i + h) % n];
  cout << (good ? "Yes" : "No") << '\n';
}
