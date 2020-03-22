// mst (cut prop), multi-source dijkstra, bin lift (max edge on path), refill trick
// https://codeforces.com/contest/1253/problem/F

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;

#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back

struct edge{int to; ll w;};
using graph = vector<vector<edge>>;

using state = pair<ll, int>; // w, curr
const ll INF = 1e15;

auto maxx(auto& a, auto b){a = max(a, b);}

auto dijkstra(int n, graph& g, int k) {
    vi visited(n);
    vll dists(n, INF);
    priority_queue<state, vector<state>, greater<state>> pq;
    rep(i, 0, k) {
        dists[i] = 0;
        pq.push({0LL, i});
    }
    while (!pq.empty()) {
        auto [dist, curr] = pq.top();
        pq.pop();
        if (visited[curr]) continue;
        visited[curr] = true;
        for (auto [to, w]: g[curr]) {
            if (dist + w < dists[to]) {
                dists[to] = dist + w;
                pq.push({dist + w, to});
            }
        }
    }
    return dists;
}

struct DSU {
    vi pars;
    DSU(int n) : pars(n) {iota(all(pars), 0);}
    int find(int i) {return (pars[i] == i) ? i : (pars[i] = find(pars[i]));}
    void merge(int a, int b) { pars[find(a)] = find(b); }
};

void mst(int n, graph &g) {
    vector<tuple<ll, int, int>> edges;
    rep(i, 0, n) {
        for (auto& [to, w]: g[i])
            edges.PB({w, i, to});
        g[i].clear();
    }
    sort(all(edges));
    DSU dsu(n);
    for (auto [w, a, b]: edges) {
        auto fa = dsu.find(a), fb = dsu.find(b);
        if (fa != fb) {
            dsu.merge(fa, fb);
            g[a].PB({b, w});
            g[b].PB({a, w});
        }
    }
}

void dfs(int i, int p, graph& g, vi& pars, vll& pdist, vi& depth, ll w = 0, int d = 0) {
    pars[i] = p, pdist[i] = w, depth[i] = d;
    for (auto e: g[i]) if (e.to != p)
        dfs(e.to, i, g, pars, pdist, depth, e.w, d + 1);
}

auto treeJump(vi& P, vll& D){
    int on = 1, d = 1;
    while(on < sz(P)) on *= 2, d++;
    vector<vi> jmp(d, P);
    vector<vll> mx(d, D);
    rep(i,1,d) rep(j,0,sz(P)) {
        jmp[i][j] = jmp[i-1][jmp[i-1][j]];
        mx[i][j] = max(mx[i - 1][j], mx[i-1][jmp[i-1][j]]);
    }
    return move(pair{jmp, mx});
}

auto maxedge(vector<vi>& tbl, vector<vll>& mx, vi& depth, int a, int b) {
    ll acc = 0;
    if (depth[a] < depth[b]) swap(a, b);
    int diff = depth[a] - depth[b];
    rep(i, 0, sz(tbl))
        if (diff & (1 << i)) {
            maxx(acc, mx[i][a]);
            a = tbl[i][a];
        }
    if (a == b) return acc;
    for (int i = sz(tbl); i--;) {
        int c = tbl[i][a], d = tbl[i][b];
        if (c != d) {
            maxx(acc, mx[i][a]);
            maxx(acc, mx[i][b]);
            a = c, b = d;
        }
    }
    return max({acc, mx[0][a], mx[0][b]});
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k, q;
    cin >> n >> m >> k >> q;

    graph g(n);
    rep(i, 0, m) {
        int a, b, w;
        cin >> a >> b >> w;
        --a; --b;
        g[a].PB({b, w});
        g[b].PB({a, w});
    }

    auto distances = dijkstra(n, g, k);
    rep(i, 0, n)
        for (auto& [to, w]: g[i]) {
            w += distances[i] + distances[to];
        }
    mst(n, g);
    
    vi pars(n);
    vll pardists(n);
    vi depth(n);
    dfs(0, 0, g, pars, pardists, depth);
    auto [jmp, jmpmax] = treeJump(pars, pardists);
    rep(i, 0, q) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        auto res = maxedge(jmp, jmpmax, depth, a, b);
        cout << res << '\n';
    }
}
