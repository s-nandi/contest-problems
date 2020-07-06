// randomization, max # of nested submask operations is <= # bits, frequency of #'s with i-th bit off is >= 1/2 in a permutation
// https://codeforces.com/contest/1364/problem/E

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
 
const int MAXB = 11;
const int FULL = (1 << MAXB) - 1;
const int ITERS = 14;
const int MAXN = 2048;
 
int n;
mt19937 gen;
uniform_int_distribution<int> dist;
 
int ask(int i, int j) {
  if (i == j) return FULL;
  cout << "? " << (i + 1) << " " << (j + 1) << endl;
  int res;
  cin >> res;
  if (res == -1) exit(0);
  return res;
}
 
void answer(vi res) {
  cout << "! "; trav(i, res) cout << i << " "; cout << endl;
}
 
int get(int i) {
  int res = FULL;
  rep(it, 0, ITERS) {
    auto ind = dist(gen);
    res &= ask(i, ind);
  }
  return res;
}
 
int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);
 
  unsigned seed = chrono::high_resolution_clock::now().time_since_epoch().count();
  gen = mt19937{seed};
  
  cin >> n;
  dist = uniform_int_distribution{0, n - 1};
 
  int curr = dist(gen);
  int mask = get(curr);
  rep(ind, 0, n) {
    if (ask(curr, ind) == mask) { // triggers <= [# bits] times
      curr = ind;
      mask = get(curr);
    }
  }
  assert(mask == 0);
  vi res(n);
  rep(i, 0, n)
    res[i] = (i == curr) ? 0 : ask(curr, i);
  answer(res);
}
