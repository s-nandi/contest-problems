// combinatorics (casework?), binary lifting (distance on tree)
// https://open.kattis.com/problems/rootedsubtrees
// 2020 North American Championship
// Note: Proof sketch in comments below, no promises about its accuracy

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define sz(a) (int)size(a)
#define PB push_back

struct edge{int to;};
using graph = vector<vector<edge>>;

struct binary_lift {
    vector<vi> table, depths;
    vi depth;
    binary_lift(const vi& par) {
        int d = 1, on = 1;
        while (on < sz(par)) on <<= 1, d++;
        depths = vector(d, par), table = vector(d, par);        
        rep(i, 0, sz(par)) depths[0][i] = i != par[i];
        rep(i, 1, d) rep(j, 0, sz(par)) {
            table[i][j] = table[i - 1][table[i - 1][j]];
            depths[i][j] = depths[i - 1][j] + depths[i - 1][table[i - 1][j]];
        }
        depth = depths.back();
    }
    auto jump(int curr, int step) {
        rep(i, 0, sz(table))
            if (step & (1 << i))
                curr = table[i][curr];
        return curr;
    }
    auto lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        u = jump(u, depth[u] - depth[v]);
        if (u == v) return u;
        for (int i = sz(table) - 1; i >= 0; i--)
            if (table[i][u] != table[i][v])
                u = table[i][u], v = table[i][v];
        return table[0][u];
    }
    auto dist(int u, int v) {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }
};

void dfs(const graph& g, auto& par, int curr, int prev = -1) {
    for (auto [to]: g[curr])
        if (to != prev) {
            par[to] = curr;
            dfs(g, par, to, curr);
        }
}

auto choose2(int k) {
    return (ll) k * (k - 1) / 2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    graph g(n);
    rep(i, 0, n - 1) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].PB({b});
        g[b].PB({a});
    }
    vi par(n);
    dfs(g, par, 0);
    auto bl = binary_lift(par);
    rep(i, 0, k) {
        int a, b;
        cin >> a >> b;
        auto between = bl.dist(--a, --b) + 1;
        /*
         * Let the root of the left (resp. right) tree be L (resp. R)
         * Let the node chosen for the left (resp. right) tree be u (resp. v)
         * You can create all n subtrees of L (just use v = R)
         * So now, count the number of sets that aren't subtrees of L
         *
         * If u or v are in the strict subtree of A = lca(L, R) from the perspective
         * of their respective roots, the intersection of T_L(u) n T_R(v) is just
         * one of the subtrees of L we already accounted for
         *
         * Thus, we can assume that neither of u/v are in the strict subtree of A
         *
         * We can also note that if u or v are not somewhere on the path between
         * L - ... - A - ... - R, then the intersection is empty or a subtree of L
         *
         * Thus, we assume that both u and v are on the path L <-> A <-> R
         * It can be shown that all distinct pairs of u, v correspond to an
         * intersection that is not a subtree of L (even if u and/or v = A!),
         * but if the assignment of u/v is swapped, the intersection can become empty
         *
         * Therefore, for each of the choose(between, 2) possible pairs, exactly 1
         * ordering corresponds to a new intersection, thus we add this to the n
         * unique intersections we found earlier
         */ 
        auto res = (ll) n + choose2(between);
        cout << res << '\n';
    }
}
