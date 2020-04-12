// coloring, constructive proof
// https://codeforces.com/contest/1338/problem/B

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define PB push_back

struct edge{int to;};
using graph = vector<vector<edge>>;

void color(graph& g, int i, vi& col, int p = -1, int c = 0) {
    col[i] = c;
    trav(e, g[i])
        if (e.to != p) 
            color(g, e.to, col, i, 1 - c);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    graph g(n);
    vi deg(n);
    rep(i, 0, n - 1) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].PB({b});
        g[b].PB({a});
        deg[a]++;
        deg[b]++;
    }
    vi leaf(n);
    rep(i, 0, n)
        leaf[i] = (deg[i] == 1);

    vi col(n);
    color(g, 0, col);
    int leaf_color = -1;
    bool evens = true;
    rep(i, 0, n) {
        if (!leaf[i]) continue;
        if (leaf_color == -1)
            leaf_color = col[i];
        evens &= (col[i] == leaf_color);
    }
    int mn = min(evens ? 1 : 3, n - 1);
    
    int mx = n - 1;
    rep(i, 0, n) {
        int nl = 0;
        trav(e, g[i])
            nl += leaf[e.to];
        mx -= max(0, nl - 1);
    }
    cout << mn << " " << mx << '\n';    
}
