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
ptT sweep_x = -INF;
struct circle {
    ptT x, y, r;
    int ind; bool isupper;
    ptT y_at(ptT xpos) const {
        auto dx = xpos - x;
        auto dy = sqrt(r * r - dx * dx);
        return isupper ? y + dy : y - dy;
    }
    bool operator < (const auto& o) const {
        return (ind != o.ind) ? y_at(sweep_x) < o.y_at(sweep_x) : isupper < o.isupper;
    }
};

struct event {
    circle c; ptT x; bool isrmv;
    auto operator < (const auto& o) const {return x < o.x;}
};

graph build_graph(int n, int q, auto& circles) {
    vector<event> events;
    trav(c, circles) {
        events.PB({c, c.x - c.r, false});
        events.PB({c, c.x + c.r, true});
    }
    sort(all(events));
    graph g(n + q + 1);
    vi par(n + q + 1, -1);
    set<circle> slice;
    for (int it = 0; it < sz(events);) {
        sweep_x = events[it].x;
        vector<event> added, removed;
        while (it < sz(events) and events[it].x == sweep_x) {
            if (events[it].isrmv) removed.emplace_back(move(events[it++]));
            else added.emplace_back(move(events[it++]));
        }
        trav(e, removed) rep(upper, 0, 2) {e.c.isupper = !!upper; slice.erase(e.c);}
        trav(e, added) rep(isupper, 0, 2) {
            e.c.isupper = !!isupper;
            auto [it, _] = slice.insert(e.c);
            if (isupper) continue; // avoid duplicating edges in graph
            auto ind = e.c.ind;
            if (next(it) == end(slice) or it == begin(slice)) par[ind] = 0;
            else {
                auto pit = prev(it);
                if (pit -> isupper == isupper) par[ind] = pit -> ind;
                else par[ind] = par[pit -> ind];
                // ^ guaranteed ind != pit -> ind b/c isupper must be false (line 63)
            }
            g[par[ind]].PB({ind});
        }
    }
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
        ptT x, y, r;
        cin >> x >> y >> r;
        circles[i] = {x, y, r, i + 1, true};
    }
    auto g = build_graph(n, q, circles);
    auto dp = vector(2, vi(sz(g)));
    vi sols(q);
    dfs(g, 0, n, q, dp, sols);
    trav(i, sols) cout << i << '\n';
}
