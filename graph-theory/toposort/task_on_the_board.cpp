// toposort, implicit graph
// https://codeforces.com/contest/1367/problem/D

#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
using vi = vector<int>;
 
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back
 
struct edge{int to;};
using graph = vector<vector<edge>>;
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
 
  int T;
  cin >> T;
  while(T--) {
    string s;
    cin >> s;
    
    int m;
    cin >> m;
    vi a(m);
    trav(i, a) cin >> i;
 
    vi cnt(26);
    trav(c, s)
      cnt[c - 'a']++;
 
    int vis = 0;
    vi visited(m);
    vi step(m);
    vector<vi> layers;
    while (vis < m) {
      vi zeros;
      rep(i, 0, m) if (visited[i] == 0) {
        if (a[i] == 0) {
          visited[i] = true;
          step[i] = sz(layers);
          zeros.PB(i);
          vis++;
        }
      }
      
      layers.PB(zeros);
      trav(i, zeros) {
        rep(j, 0, m) if (visited[j] == 0) {
          assert(a[j] > 0);
          a[j] -= abs(i - j);
          assert(a[j] >= 0);
        }
      }
    }
    
    string t(m, ' ');
    for (int i = 0, j = 25; i < sz(layers); i++) {
      while (j >= 0 and cnt[j] < sz(layers[i])) j--;
      trav(pos, layers[i]) t[pos] = 'a' + j;
      j--;
    }
    cout << t << '\n';
    
  }
}
