// trie, lca of range = lca of extremes (for sorted elements, LCP idea from suffix array), sliding window
// https://open.kattis.com/problems/pokegene
// 2018 North Central NA Regional

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
using ll = long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int,int>;

constexpr bool dbg = false;

struct edge{int to;};
using graph = vector<vector<edge>>;

struct Trie {
  using T = char;
  static int toindex(T c) { return c - 'a'; }
  static constexpr int alpha = 26;
  struct Node {
    array<int, alpha> to{}, cnt{};
  };
  
  vector<Node> t;
  vi endat;
  Trie() : t(1) {}
  void add(const basic_string<T>& s, int ind) {
    int i = 0;
    trav(ch, s) {
      int c = toindex(ch);
      if (!t[i].to[c]) {
        t[i].to[c] = sz(t);
        t.emplace_back();
      }
      t[i].cnt[c]++;
      i = t[i].to[c];
    }
    if (ind >= sz(endat)) endat.resize(ind + 1);
    endat[ind] = i;
  }
};

void dfs(const Trie& trie, int i, auto& depth, auto& adj, int dep = 0) {
  depth[i] = dep;
  trav(j, trie.t[i].to) if (j) {
    adj[i].PB(j);
    dfs(trie, j, depth, adj, dep + 1);
  }
}

template<class T>
struct RMQ {
  vector<vector<T>> jmp;
  RMQ(const vector<T>& V) : jmp(1, V) {
    for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
      jmp.emplace_back(sz(V) - pw * 2 + 1);
      rep(j,0,sz(jmp[k]))
        jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
    }
  }
  T query(int a, int b) {
    assert(a < b);
    int dep = 31 - __builtin_clz(b - a);
    return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
  }
};

struct LCA {
  int T = 0;
  vi time, path, ret;
  RMQ<int> rmq;

  LCA(vector<vi>& C) : time(sz(C)), rmq((dfs(C,0,-1), ret)) {}
  void dfs(vector<vi>& C, int v, int par) {
    time[v] = T++;
    for (int y : C[v]) if (y != par) {
        path.push_back(v), ret.push_back(time[v]);
        dfs(C, y, v);
      }
  }

  int lca(int a, int b) {
    if (a == b) return a;
    tie(a, b) = minmax(time[a], time[b]);
    return path[rmq.query(a, b)];
  }
};

int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n, q;
  cin >> n >> q;
  vector<string> a(n);
  trav(i, a) cin >> i;

  vi inds(n);
  iota(all(inds), 0);
  sort(all(inds), [&](int i, int j) {
                    return a[i] < a[j];
                  });

  vi position(n);
  rep(i, 0, n) position[inds[i]] = i;

  Trie trie{};
  trav(i, inds)
    trie.add(a[i], i);

  vi depth(sz(trie.t));
  vector<vi> adj(sz(trie.t));
  dfs(trie, 0, depth, adj);

  LCA lca(adj);
  rep(it, 0, q) {
    int k, l;
    cin >> k >> l;
    vi subset(k);
    trav(i, subset) {cin >> i; --i;}
    sort(all(subset), [&](int i, int j) {
                        return position[i] < position[j];
                      });
    
    auto getnode = [&](int i) { return trie.endat[subset[i]]; };
    
    int res = 0;
    rep(i, 0, k - l + 1) {
      int j = i + l - 1;
      auto a = getnode(i);
      auto b = getnode(j);
      auto x = i - 1 >= 0 ? getnode(i - 1) : -1;
      auto y = j + 1 < k ? getnode(j + 1) : -1;
      
      auto anc = lca.lca(a, b);
      auto panc = ~x ? lca.lca(x, b) : 0;
      auto nanc = ~y ? lca.lca(a, y) : 0;
      res += depth[anc] - max(depth[panc], depth[nanc]);
    }
    cout << res << '\n';
  }
}
