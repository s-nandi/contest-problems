// dp on EV, trie
// https://open.kattis.com/problems/justaquiz

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a);i<(b);++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back

using ll = long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int,int>;

struct edge{int to;};
using graph = vector<vector<edge>>;

constexpr auto dbg = false;

auto split(const auto& s, char delim = ' ') {
  auto it = begin(s);
  vector<string> tokens;
  while (true) {
    auto nit = find(it, end(s), delim);
    tokens.emplace_back(it, nit);
    if (nit != end(s)) it = nit + 1;
    else break;
  }
  return tokens;
}

struct Trie {
  struct Node {
    map<int, int> nxt;
    map<int, int> occ;
    int w;

    int mxcount{-1};
    int getmaxcount() {
      if (mxcount < 0) {
        mxcount = 0;
        for (const auto& [cand, cnt]: occ)
          mxcount = max(mxcount, cnt);
      }
      return mxcount;
    }
  };
  
  vector<Node> a;
  Trie() : a(1) {}
  int make() {
    a.emplace_back();
    return sz(a) - 1;
  }
  
  void add(const vi& v, int ans) {
    int curr = 0;
    trav(i, v) {
      if (!a[curr].nxt.count(i)) {
        int nn = make();
        a[curr].nxt[i] = nn;
      }
      a[curr].occ[ans]++;
      a[curr].w++;
      curr = a[curr].nxt[i];
    }
    a[curr].occ[ans]++;
    a[curr].w++;
  }
};

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << setprecision(11) << fixed;

  int t, n;
  cin >> t >> n;
  cin.ignore();

  map<string, int> indexer;
  auto indexof = [&](const string& s) {
                   if (!indexer.count(s)) {
                     auto res = sz(indexer);
                     indexer[s] = res;
                   }
                   return indexer[s];
                 };
  
  vector<vi> questions(n);
  vi answers(n);
  rep(i, 0, n) {
    string s;
    getline(cin, s);
    auto tokens = split(s);
    rep(j, 0, sz(tokens) - 1) {
      questions[i].PB(indexof(tokens[j]));
    }
    answers[i] = indexof(tokens.back());
  }
  Trie trie{};
  rep(it, 0, n)
    trie.add(questions[it], answers[it]);

  auto dp = vector(t + 1, vector<ld>(sz(trie.a), 0));
  rep(tm, 1, t + 1) {
    rep(curr, 0, sz(trie.a)) {
      auto nlikelihood = trie.a[curr].getmaxcount();
      auto weight = trie.a[curr].w;
      
      auto guess = (ld) nlikelihood / weight + dp[tm - 1][0];
      auto godown = 0.L;
      for (const auto& [ch, to]: trie.a[curr].nxt) {
        auto cweight = trie.a[to].w;
        godown += dp[tm - 1][to] * (ld) cweight / weight;
      }
      dp[tm][curr] = max(guess, godown);
    }
  }
  cout << dp[t][0] << '\n';
}
