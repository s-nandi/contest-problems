// aho-corasick (store sum of values for each match), greedy (can always take pref of A and suff of B)
// https://www.codechef.com/problems/TWOSTRS

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a);i<(b);++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back
using ll = long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int,int>;

constexpr auto dbg = false;
constexpr auto check = false;
constexpr auto custom = false;

struct edge{int to;};
using graph = vector<vector<edge>>;

const int MAXS = 27;

struct AhoCorasick {
  enum {alpha = 26, first = 'a'};
  struct Node {
    int back, next[alpha], start = -1, end = -1;
    int sum = 0;
    Node(int v) { memset(next, v, sizeof(next)); }
  };
  vector<Node> N;
  vi backp;
  void insert(string& s, int j, int value) {
    assert(!s.empty());
    int n = 0;
    for (char c : s) {
      int& m = N[n].next[c - first];
      if (m == -1) { n = m = sz(N); N.emplace_back(-1); }
      else n = m;
    }
    if (N[n].end == -1) N[n].start = j;
    backp.push_back(N[n].end);
    N[n].end = j;
    N[n].sum += value;
  }
  AhoCorasick(vector<pair<string, int>>& pat) : N(1, -1) {
    rep(i,0,sz(pat)) insert(pat[i].first, i, pat[i].second);
    N[0].back = sz(N);
    N.emplace_back(0);

    queue<int> q;
    for (q.push(0); !q.empty(); q.pop()) {
      int n = q.front(), prev = N[n].back;
      rep(i,0,alpha) {
        int &ed = N[n].next[i], y = N[prev].next[i];
        if (ed == -1) ed = y;
        else {
          N[ed].back = y;
          (N[ed].end == -1 ? N[ed].end : backp[N[ed].start])
            = N[y].end;
          N[ed].sum += N[y].sum;
          q.push(ed);
        }
      }
    }
  }
  int next(int state, char c) const { return N[state].next[c - first];}
  int match(int state) const {return N[state].end;}
  int suffixMatch(int state) const { return backp[state];}
  int valueof(int state){return N[state].sum;}
};

int32_t main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;
  while(T--) {
    string a, b;
    cin >> a >> b;
    int n = sz(a), m = sz(b);
    int k;
    cin >> k;
    vector<pair<string, int>> qs(k);
    trav(q, qs) {
      cin >> q.first >> q.second;
    }

    AhoCorasick ac(qs);
    trav(q, qs) reverse(all(q.first));
    AhoCorasick ac2(qs);
    
    vector<ll> apref(n);
    vi astate(n);
    {
      int curr = 0;
      rep(i, 0, n) {
        curr = ac.next(curr, a[i]);
        apref[i] = ac.valueof(curr);
        astate[i] = curr;
        if (i - 1 >= 0) apref[i] += apref[i - 1];
      }
    }
    vector<ll> bsuff(m);
    {
      int curr = 0;
      for (int i = m - 1; i >= 0; i--) {
        curr = ac2.next(curr, b[i]);
        bsuff[i] = ac2.valueof(curr);
        if (i + 1 < m) bsuff[i] += bsuff[i + 1];
      }
    }

    ll best = 0;
    rep(i, 0, n) {
      rep(j, 0, m) { // A[0..i] & B[j..m - 1]
        int curr = astate[i];
        int curr0 = 0;
        ll val = 0;
        ll val0 = 0;

        rep(it, j, min(j + MAXS, m)) {
          curr = ac.next(curr, b[it]);
          curr0 = ac.next(curr0, b[it]);
          val += ac.valueof(curr);
          val0 += ac.valueof(curr0);
        }
        ll got = apref[i] + bsuff[j] + val - val0;
        best = max(best, got);
      }
    }
    cout << best << '\n';    
  }
}
