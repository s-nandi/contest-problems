// amortization, pigeonhole, venice priority queue, if a request for t time is to be removed it must have run for t/k units on 1 of k observatories
// https://codeforces.com/gym/102452/problem/I
// 2020 Hong Kong ICPC Regional

#include <bits/stdc++.h>
using namespace std;
 
using vi = vector<int>;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
 
#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back
#define cauto const auto
 
struct edge{int to;};
using graph = vector<vector<edge>>;
 
template <typename T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
 
const int MAXM = 200'000;
const int MAXK = 3;
const int MAXLOG = 35; // log(MAX_TIME)_{1.5} w/ MAX_TIME = 1e6
const int MAXEVENTS = MAXM * MAXLOG;
 
int last{0};
bool completed[MAXEVENTS + 1];
ll remaining_time[MAXM + 1][MAXK + 1];
 
vi removed;
struct Venice {
  using event = tuple<ll, int, int>; // delta'd time, observer id, event id
  min_queue<event> pq;
  ll delta{0};

  auto actual_time(auto t) const {return t - delta;}
  auto insert(auto t, int id, int eid) {
    pq.push({t + delta, id, eid});
    return t + delta;
  }
  
  auto gather(auto mins) {
    delta += mins;
    removed.clear();
    while (!empty(pq) and actual_time(get<0>(pq.top())) <= 0) {
      auto [tm, id, eid] = pq.top(); pq.pop();
      if (completed[eid]) continue;
      removed.PB(id);
      completed[eid] = true;
    }
  }
};
 
array<int, 3> partition(int val, int cnt) {
  if (cnt == 1) return {val};
  else if (cnt == 2) return {val / 2, (val + 1) / 2};
  else return {val / 3, val / 3, val - (val / 3) - (val / 3)};
}
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
 
  int n, m;
  cin >> n >> m;
 
  int nn = 0, nevents = 0;
  vector<vi> observed_at(m + 5);
  vector<Venice> qs(n);
  rep(it, 0, m) {
    int type;
    cin >> type;
    if (type == 1) {
      auto id = nn++;
      int eid = nevents++;
      
      int y, k;
      cin >> y >> k;
      y ^= last;
      observed_at[id].resize(k);
      trav(i, observed_at[id]) {cin >> i; i ^= last; --i;}      
      
      auto partitions = partition(y, k);
      rep(i, 0, k) {
        auto observatory = observed_at[id][i];
        remaining_time[id][i] = qs[observatory].insert(partitions[i], id, eid);
      }
    } else if (type == 2) {
      int x, y;
      cin >> x >> y;
      x ^= last, y ^= last;
      --x;
 
      qs[x].gather(y); // 'removed' contains observers that need to repartition their remaining time (if any)
 
      vi finished;
      trav(id, removed) {
        ll rem = 0;
        rep(i, 0, sz(observed_at[id])) {
          auto observatory = observed_at[id][i];
          rem += qs[observatory].actual_time(remaining_time[id][i]);
        }
        if (rem <= 0) finished.PB(id);
        else {
          int eid = nevents++;
          auto partitions = partition(rem, sz(observed_at[id]));
          rep(i, 0, sz(observed_at[id])) {
            auto observatory = observed_at[id][i];
            remaining_time[id][i] = qs[observatory].insert(partitions[i], id, eid);
          }
        }
      }
      auto print = [](const auto& a) { // judge is whitespace sensitive
                     cout << sz(a);
                     trav(i, a) cout << " " << (i + 1);
                     cout << '\n';
                   };
      sort(all(finished));
      print(finished);
      last = sz(finished);
    } else assert(false);
  }
}
