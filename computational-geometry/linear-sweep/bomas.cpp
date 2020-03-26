// sweep (maintain vert order), circle containment, tree dp (propagate up through query nodes)
// https://open.kattis.com/problems/bomas
// 2020 North American Championship

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ld = long double;

#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back

struct edge{int to;};
using graph = vector<vector<edge>>;

constexpr auto INF = 1e14;

using ptT = ld;
struct circle {
    ptT x, y, r;
    int ind;
};
struct event {
    circle c; ptT x;
    bool isrmv;
    auto operator < (const auto& o) const {return x < o.x;}
};

ptT sweep_x = -INF;
struct semicircle {
    circle c; bool isupper;
    ptT y_at(ptT x) const {
        auto dx = x - c.x;
        auto dy = sqrt(c.r * c.r - dx * dx);
        return isupper ? c.y + dy : c.y - dy;
    }
    bool operator < (const auto& o) const {
        return (c.ind != o.c.ind) ? y_at(sweep_x) < o.y_at(sweep_x) : isupper < o.isupper;
    }
};

graph build_graph(int n, int q, auto& circles) {
    vector<event> events;
    trav(c, circles) {
        events.PB({c, c.x - c.r, false});
        events.PB({c, c.x + c.r, true});
    }
    sort(all(events));
    vi par(n + q + 1, -1), sibling(n + q + 1, -1);
    set<semicircle> slice;
    for (int it = 0; it < sz(events);) {
        sweep_x = events[it].x;
        vector<event> added, removed;
        while (it < sz(events) and events[it].x == sweep_x) {
            if (events[it].isrmv) removed.emplace_back(move(events[it++]));
            else added.emplace_back(move(events[it++]));
        }
        trav(e, removed) rep(isupper, 0, 2) slice.erase({e.c, !!isupper});
        trav(e, added) rep(isupper, 0, 2) slice.insert({e.c, !!isupper});
        trav(e, added) {
            int ind = e.c.ind;
            auto top = slice.find({e.c, true});
            auto bottom = slice.find({e.c, false});
            if (next(top) == end(slice) or bottom == begin(slice)) {
                par[ind] = 0;
            } else {
                if (next(top) != end(slice)) {
                    auto [above, isupper] = *next(top);
                    if (isupper) par[ind] = above.ind;
                    else sibling[ind] = above.ind;
                }
                if (bottom != begin(slice)) {
                    auto [below, isupper] = *prev(bottom);
                    if (!isupper) par[ind] = below.ind;
                    else sibling[ind] = below.ind;
                }
            }
        }
    }
    rep(i, 1, n + q + 1) {
        if (par[i] != -1) continue;
        int root;
        for (int curr = i; par[curr] == -1; curr = sibling[curr])
            root = sibling[curr];
        for (int curr = i; par[curr] == -1; curr = sibling[curr])
            par[curr] = par[root];
    }
    graph g(n + q + 1);
    rep(i, 1, n + q + 1)
        g[par[i]].PB({i});
    return g;
}

void dfs(auto& g, int i, int n, int q, auto& dp, auto& sols) {
    dp[0][i] = 0;
    dp[1][i] = 1;
    for (auto [to]: g[i]) {
        dfs(g, to, n, q, dp, sols);
        dp[0][i] += max(dp[1][to], dp[0][to]);
        dp[1][i] += dp[0][to];
    }
    if (i > n) {
        sols[i - n - 1] = max(dp[1][i], dp[0][i]);
        --dp[1][i];
        swap(dp[0][i], dp[1][i]);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<circle> circles(n + q);
    rep(i, 0, n + q) {
        int x, y, r;
        cin >> circles[i].x >> circles[i].y >> circles[i].r;
        circles[i].ind = i + 1;
    }
    auto g = build_graph(n, q, circles);
    auto dp = vector(2, vi(sz(g)));
    vi sols(q);
    dfs(g, 0, n, q, dp, sols);
    trav(i, sols) cout << i << '\n';
}
