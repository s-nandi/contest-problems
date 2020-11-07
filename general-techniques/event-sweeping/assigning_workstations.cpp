// event queue ('dynamic' line sweep -- some events are created during sweep), greedy (earliest released server first -- exchange argument)
// https://open.kattis.com/problems/workstations
// 2015 Northwestern Europe Regional

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
#define cauto const auto&
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using vi = vector<int>;

struct edge{int to;};
using graph = vector<vector<edge>>;

constexpr auto dbg = true;

template <typename T>
using min_queue = priority_queue<T, vector<T>, greater<>>;

struct event {
  int tm;
  enum etype {machine_free, researcher_arrive} type; // 0: machine becomes free, 1 : researcher comes
  int id; // researcher id iff query type 1, invalid (or -1) otherwise
  bool operator < (const auto& o) const {return tie(tm, type, id) < tie(o.tm, o.type, o.id);} // if machine becomes free as researcher arrives, machine becoming free comes first
                                                                                              // since statement says "lock if unused for MORE than m minutes"
  bool operator > (const auto& o) const {return o < (*this);}
};

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m;

  int unlocks = 0;
  min_queue<int> unused; // stores release time, choose machine w/ earliest release time (min rem time) first
  min_queue<event> events;

  vi a(n), s(n);
  rep(i, 0, n) {
    cin >> a[i] >> s[i];
    events.push({a[i], event::researcher_arrive, i});
  }
  while (!empty(events)) {
    auto [tm, type, id] = events.top(); events.pop();
    if (type == event::machine_free) unused.push(tm);
    else { assert(type == event::researcher_arrive);
      while (!empty(unused) and tm - unused.top() > m) // trim machines that are now locked due to inactivity; see above coment for why > and not .=
        unused.pop();
      
      if (empty(unused)) unlocks++;
      else unused.pop();
      events.push({tm + s[id], event::machine_free, -1});
    }
  }
  cout << (n - unlocks) << '\n';
}
