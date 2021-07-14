// network flow (dinic, minimum vertex cover on bipartite, recovering mvc/min cut), union of rectangles (recovering points), segment tree (lazy propagation)
// https://www.hackerrank.com/contests/university-codesprint-4/challenges/drawing-rectangles

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
typedef pair<int, int> ii;

const int MAXN = 300001;
const int INF = 1231231234;

struct Dinic {
  struct edge{int to, id;};
  using graph = vector<vector<edge>>;
  using flowT = int;
  static constexpr flowT INF = numeric_limits<flowT>::max();
  
  graph g;
  vector<flowT> cap, flow;
  vi lvl, ptr;
  Dinic(int s) : g(s), lvl(s), ptr(s) {}
  void addEdge(int from, int to, flowT capacity) {
    g[from].PB({to, sz(flow)});
    cap.PB(capacity), flow.PB(0);
    g[to].PB({from, sz(flow)});
    cap.PB(0), flow.PB(0);
  }
  flowT residual(int id) { return cap[id] - flow[id]; }
  bool build(int s, int t) {
    queue<int> q;
    q.push(s);
    fill(all(lvl), -1);
    lvl[s] = 0;
    while (!q.empty()) {
      int i = q.front();
      q.pop();
      trav(e, g[i])
        if (lvl[e.to] == -1 and residual(e.id) > 0)
          q.push(e.to), lvl[e.to] = lvl[i] + 1;
    }
    return lvl[t] != -1;
  }
  flowT push(int i, int t, flowT lo = INF) {
    if (i == t) return lo;
    for (; ptr[i] < sz(g[i]); ptr[i]++) {
      edge e = g[i][ptr[i]];
      if (lvl[e.to] == lvl[i] + 1 and residual(e.id) > 0) {
        flowT got = push(e.to, t, min(lo, residual(e.id)));
        if (got > 0) {
          flow[e.id] += got;
          flow[e.id ^ 1] -= got;
          return got;
        }
      }
    }
    return 0;
  }
  flowT calc(int s, int t) {
    flowT res = 0;
    while (build(s, t)) {
      fill(all(ptr), 0);
      while (auto delta = push(s, t)) res += delta;
    }
    return res;
  }
  bool leftOfMinCut(int a) { return lvl[a] != -1; }
};

struct node
{
  int maxVal, lazy, isLazy;
  node *l, *r;

  node(){maxVal = -INF, lazy = isLazy = 0, l = NULL, r = NULL;}
  void init(int i){maxVal = i;}

  node* refresh()
  {
    maxVal = max(l -> maxVal, r -> maxVal);
    return this;
  }

  void pushLazy(int lb, int rb)
  {
    if (isLazy)
    {
      maxVal += lazy;
      if (lb != rb)
        l -> setLazy(lazy), r -> setLazy(lazy);
      resetLazy();
    }
  }
  void setLazy(int v){lazy += v, isLazy = true;}
  void resetLazy(){lazy = 0, isLazy = false;}
};

struct segmentTree
{
  int sz;
  node* root;

  segmentTree(int s)
  {
    root = new node();
    sz = s;
    build(root, 0, sz - 1);
  }

  node combine(node a, node b)
  {
    node acc;
    acc.l = &a, acc.r = &b;
    return *(acc.refresh());
  }

  void build(node* &curr, int l, int r)
  {
    if (l == r) { curr -> init(0); return; }
    int m = (l + r) >> 1;
    curr -> l = new node(), curr -> r = new node();
    build(curr -> l, l, m);
    build(curr -> r, m + 1, r);
    curr -> refresh();
  }

  int query(int l, int r) {return query(root, 0, sz - 1, l, r).maxVal;}
  node query(node* &curr, int l, int r, int ql, int qr)
  {
    curr -> pushLazy(l, r);
    if (l > qr or r < ql) return node();
    if (l >= ql and r <= qr) return *curr;
    int m = (l + r) >> 1;
    return combine(query(curr -> l, l, m, ql, qr), query(curr -> r, m + 1, r, ql, qr));
  }

  void modify(int l, int r, int v) {modify(root, 0, sz - 1, v, l, r);}
  void modify(node* &curr, int l, int r, int v, int ql, int qr)
  {
    curr -> pushLazy(l, r);
    if (l > qr or r < ql) return;
    if (l >= ql and r <= qr)
    {
      curr -> setLazy(v);
      curr -> pushLazy(l, r);
      return;
    }
    int m = (l + r) >> 1;
    modify(curr -> l, l, m, v, ql, qr), modify(curr -> r, m + 1, r, v, ql, qr);
    curr -> refresh();
  }

  vector <int> findNonZeros()
  {
    vector <int> nonZeros;
    findNonZeros(root, 0, sz - 1, nonZeros);
    return nonZeros;
  }
  void findNonZeros(node* &curr, int l, int r, vector <int> &nonZeros)
  {
    curr -> pushLazy(l, r);
    if (curr -> maxVal == 0) return;
    if (l == r) {nonZeros.push_back(l); return;}
    int m = (l + r) >> 1;
    findNonZeros(curr -> l, l, m, nonZeros), findNonZeros(curr -> r, m + 1, r, nonZeros);
  }
};

struct event
{
  int x, y1, y2, isStart;
  bool operator < (const event &o) const
  {
    if (x != o.x) return x < o.x;
    return make_pair(isStart, make_pair(y1, y2)) < make_pair(o.isStart, make_pair(o.y1, o.y2));
  }
};

vector <event> rectangleToEvent(int x1, int y1, int x2, int y2)
{
  return {{x1, y1, y2, true}, {x2 + 1, y1, y2, false}};
}

vector <ii> unionRectangles(vector <event> &events)
{
  segmentTree st(MAXN);
  vector <ii> points;
  sort(events.begin(), events.end());
  for (int i = 0, curr = 0; i < MAXN; i++)
  {
    while(events[curr].x == i)
    {
      st.modify(events[curr].y1, events[curr].y2, events[curr].isStart ? 1 : -1);
      curr++;
    }
    auto nz = st.findNonZeros();
    for (int j: nz) points.push_back({i, j});
  }
  return points;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin>>n;

  vector <event> events;
  for (int i = 0; i < n; i++)
  {
    int x1, y1, x2, y2;
    cin>>x1>>y1>>x2>>y2;
    for (event e: rectangleToEvent(x1, y1, x2, y2)) events.push_back(e);
  }
  auto points = unionRectangles(events);

  Dinic dnc(2 * MAXN + 2);
  vector <bool> created(2 * MAXN);
  int s = 2 * MAXN, t = 2 * MAXN + 1;

  for (ii p: points)
  {
    int v = 2 * p.first + 1, h = 2 * p.second;
    if (!created[v]){dnc.addEdge(s, v, 1), created[v] = true;}
    if (!created[h]){dnc.addEdge(h, t, 1), created[h] = true;}
    dnc.addEdge(v, h, 1);
  }

  int sol = dnc.calc(s, t);

  vector <int> vertical, horizontal;
  for (int i = 0; i < 2 * MAXN; i++)
    if (created[i])
    {
      if (i & 1 and !dnc.leftOfMinCut(i)) vertical.push_back(i / 2);
      else if(!(i & 1) and dnc.leftOfMinCut(i)) horizontal.push_back(i / 2);
    }

  cout<<sol<<'\n';
  cout<<vertical.size()<<'\n';
  for (int i: vertical) cout<<i<<" ";
  cout<<'\n';
  cout<<horizontal.size()<<'\n';
  for (int i: horizontal) cout<<i<<" ";
  cout<<'\n';
}
