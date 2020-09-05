// greedy (good bracket sequence: min # of open ('s goes up by 1 for each odd-length prefix => commit to taking max val in pq at each odd step), after sorting by b each ind i p1 takes must have a matching j > i that p2 takes => reduction to ( balancing,
//                                                                                                                                               max(p1_takes(a) - p2_takes(b)) = max(p1_takes(a) + p1_takes(b) - sum(b's)) since p2_takes(b) = sum(b's) - p1_takes(b))
// https://www.hackerearth.com/practice/algorithms/greedy/basics-of-greedy-algorithms/practice-problems/algorithm/interesting-game-4-b6515135/description/
// Note: Problem statement implies that maximizing A is the goal, but the checker is implemented for maximizing A - B [A == score of player a, B == score of player b]

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
  
  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vector<ll> a(n), b(n);
    trav(i, a) cin >> i;
    trav(i, b) cin >> i;
    
    transform(all(a), begin(b), begin(a), plus<>{});
    auto overcount = accumulate(all(b), 0LL);
    
    auto indices = vi(n);
    iota(all(indices), 0);
    sort(all(indices), [&](int i, int j){return b[i] < b[j];});

    ll ascore = 0;
    priority_queue<ll> pq;
    rep(i, 0, sz(indices)) {
      pq.push(a[indices[i]]);
      if ((i + 1) & 1) {
        ascore += pq.top(); pq.pop();
      }
    }
    cout << ascore - overcount << '\n';
  }
}
