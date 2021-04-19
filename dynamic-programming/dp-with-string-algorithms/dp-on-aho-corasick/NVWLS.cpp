// dp on aho corasick
// https://open.kattis.com/problems/nvwls
// 2019 North American Qualifier

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
#define cauto const auto
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using vi = vector<int>;

struct edge{int to;};
using graph = vector<vector<edge>>;

constexpr auto INF = 1031231234;

struct AhoCorasick {
  enum {alpha = 26, first = 'A'}; // change this!
  struct Node {
    // (nmatches is optional)
    int back, next[alpha], start = -1, end = -1, nmatches = 0;
    Node(int v) { memset(next, v, sizeof(next)); }
  };
  vector<Node> N;
  vi backp;
  void insert(string& s, int j) {
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
    N[n].nmatches++;
  }
  AhoCorasick(vector<string>& pat) : N(1, -1) {
    rep(i,0,sz(pat)) insert(pat[i], i);
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
          N[ed].nmatches += N[y].nmatches;
          q.push(ed);
        }
      }
    }
  }
  vi find(string word) {
    int n = 0;
    vi res; // ll count = 0;
    for (char c : word) {
      n = N[n].next[c - first];
      res.push_back(N[n].end);
      // count += N[n].nmatches;
    }
    return res;
  }
  vector<vi> findAll(vector<string>& pat, string word) {
    vi r = find(word);
    vector<vi> res(sz(word));
    rep(i,0,sz(word)) {
      int ind = r[i];
      while (ind != -1) {
        res[i - sz(pat[ind]) + 1].push_back(ind);
        ind = backp[ind];
      }
    }
    return res;
  }
  int next(int state, char c) const { return N[state].next[c - first];}
  int match(int state) const {return N[state].end;}
  int suffixMatch(int state) const { return backp[state];}
};

const string vowels = "AEIOU";
bool isvowel(char c){return find(all(vowels), c) != end(vowels);}

auto maxx(auto& a, auto b){a = max(a, b);}

int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;
  vector<string> a(n), b(n);
  trav(s, a) cin >> s;

  map<string, pii> mapping; // trimmed string => (# vowels, index)
  rep(i, 0, n) {
    b[i] = a[i];
    auto& trimmed = b[i];
    auto vowel_it = stable_partition(all(trimmed), [](char c){return !isvowel(c);});
    auto nvowels = (int)(end(trimmed) - vowel_it);
    trimmed.erase(vowel_it, end(trimmed));

    auto possible = pair{nvowels, i};
    if (!mapping.count(trimmed)) mapping[trimmed] = possible;
    else mapping[trimmed] = max(mapping[trimmed], possible);
  }
  vector<string> kept;
  vi vals;
  vi indices;
  for (const auto& [trimmed, best]: mapping) {
    const auto& [nvowels, index] = best;
    kept.PB(b[index]);
    vals.PB(nvowels);
    indices.PB(index);
  }
  AhoCorasick ac(kept);

  string message;
  cin >> message;
  auto dp = vector(sz(message) + 1, pair{-INF, -1});
  dp[0] = {0, -1};
  auto it = 0;
  rep(i, 1, sz(message) + 1) {
    it = ac.next(it, message[i - 1]);
    for (auto en = ac.match(it); en != -1; en = ac.suffixMatch(en)) {
      auto len = sz(kept[en]);
      auto val = vals[en];
      maxx(dp[i], pair{dp[i - len].first + val, en});
    }
  }
  vi res;
  for (int i = sz(message); i > 0; i -= sz(b[res.back()]))
    res.PB(indices[dp[i].second]);
  reverse(all(res));
  trav(i, res) cout << a[i] << " "; cout << '\n';
}
