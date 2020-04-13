// dp on trees (rerooting)
// https://codeforces.com/contest/1092/problem/F

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;

#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define PB push_back

struct edge{int to;};
using graph = vector<vector<edge>>;

const int MAXN = 200000;
int a[MAXN + 5];
ll dp[MAXN + 5];
ll total[MAXN + 5];

ll predfs(graph& g, int i, int p = -1, int d = 0) {
    auto acc = (ll) a[i] * d;
    total[i] = a[i];
    trav(e, g[i]) {
        if (e.to == p) continue;
        acc += predfs(g, e.to, i, d + 1);
        total[i] += total[e.to];
    }
    return acc;
}

void dfs(graph& g, int i, ll val, int p = -1, ll above = 0) {
    dp[i] = val;    
    auto child_sum = total[i] - a[i];
    trav(e, g[i]) {
        if (e.to == p) continue;
        auto other_children = child_sum - total[e.to];
        auto nabove = above + other_children + a[i];
        auto nval = val + nabove - total[e.to];
        dfs(g, e.to, nval, i, nabove);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    rep(i, 0, n) cin >> a[i];
    graph g(n);
    rep(i, 0, n - 1) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        g[u].PB({v});
        g[v].PB({u});
    }
    auto init = predfs(g, 0);
    dfs(g, 0, init);
    auto best = *max_element(all(dp));
    cout << best << '\n';
}
