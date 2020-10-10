// constructive (monovariant: # of blocks [0..i] [i+1..j], ... s.t. each block is continouous/sorted => decreases by 1 each operation [ends at 0])
// https://codeforces.com/contest/1427/problem/D

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

auto solve(int n, vi a) {
  vector<vi> res;
  auto op = // [0, i), [i, k), [k, j], (j, n) s.t. a[j] + 1 == a[i] & values in a[k..j] are contiguous
    [&](int i, int k, int j) {
      
      assert(i < k and k <= j);
      array curr = {i, k - i, j - k + 1, n - j - 1};

      int it = 0;
      vector<vi> blocks;
      res.emplace_back();
      trav(s, curr) if (s > 0) {
        res.back().PB(s);
                  
        blocks.emplace_back();
        rep(i, 0, s) blocks.back().PB(a[it++]);
      }
      assert(it == n);
      reverse(all(blocks)); 
              
      a.clear();
      trav(row, blocks) trav(elem, row) a.PB(elem);
    };
  
  while (!is_sorted(all(a))) {
    vi pos(n);
    rep(i, 0, n) pos[a[i]] = i;
    
    rep(v, 0, n - 1) {
      if (pos[v] > pos[v + 1]) {
        int i = pos[v + 1];
        int j = pos[v];
        
        int k = j;
        auto expected = a[k]; // a[k] == v
        while (k - 1 >= 0 and a[k - 1] == expected - 1) --k, --expected;
        
        op(i, k, j);
        break;
      }
    }
  }
  cout << sz(res) << '\n';
  trav(partition, res) {
    cout << sz(partition) << " ";
    trav(len, partition) cout << len << " "; cout << '\n';
  }
  auto run = vi(n); iota(all(run), 0); assert(run == a); assert(sz(res) <= n);
}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;
  vi a(n);
  trav(i, a) {cin >> i; --i;}
  solve(n, a);
}
