// dp, process creates recursive structure, proofy (should take root in i-th step iff i % 3 == 2 -- why?)
// https://codeforces.com/contest/1369/problem/D

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using ii = pair<int, int>;
using vi = vector<int>;

#define rep(i, a, b) for(auto i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back

struct edge{int to;};
using graph = vector<vector<edge>>;

const int MAXN = 2000000;
const int MOD = 1000000007;

int add(int a, int b){return ((ll) a + b) % MOD;}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  vi taken(MAXN + 5), nottaken(MAXN + 5), best(MAXN + 5);  
  rep(i, 2, MAXN + 5) {
    taken[i] = add(1, add(nottaken[i - 1], add(nottaken[i - 2], nottaken[i - 2])));
    nottaken[i] = add(best[i - 1], add(best[i - 2], best[i - 2]));
    best[i] = (i % 3 == 2) ? taken[i] : nottaken[i];
  }
  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    --n;
    cout << (4LL * best[n]) % MOD << '\n';
  }
}
