// adhoc (proofy), solve on a line then identify delta from rotation (sliding window), solution on line: sum of every other element, delta: a[(i+2)%n]-a[i]
// https://codeforces.com/contest/1372/problem/D

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
  ll curr = 0;
  deque<int> indices;
  vi a(n);
  rep(i, 0, n) {
    cin >> a[i];
    if (~i & 1) {curr += a[i]; indices.PB(i);}
  }
  
  ll best = curr;
  rep(i, 0, n) {
    auto old = indices[0];
    indices.pop_front();
    auto nw = (old + 1) % n;
    indices.push_back(nw);
    auto delta = a[nw] - a[old];
    curr += delta;
    best = max(best, curr);
  }
  cout << best << '\n';
}
