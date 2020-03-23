// euler walk (undirected), butterfly pattern for stitching, constructive
// https://codeforces.com/gym/102411/problem/C
// 2019 Northwestern Russia Regional

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define sz(a) (int)size(a)
#define PB push_back

struct edge{int to, id;};
using graph = vector<vector<edge>>;

void dfs(int i, auto& g, auto& used, auto& tour, int par = 0) {
    for (auto [to, id]: g[i]) {
        if (used[id] or (id & 1) != par) continue;
        used[id] = true;
        dfs(to, g, used, tour, 1 - par);
    }
    tour.push_front(i);
}

auto feasible = true;
auto eulertour(const graph& g, int st) {
    auto m = 0;
    rep(i, 0, sz(g))
        m += sz(g[i]) / 2;
    deque<int> res;
    vi used(m);
    dfs(st, g, used, res);
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;
    auto grid = vector(n, string(m, ' '));
    rep(i, 0, n) {
        rep(j, 0, m) {
            cin >> grid[i][j];
        }
    }

    auto idx = [&](int i, int j) {return i * (m + 1) + j;};
    auto inv = [&](int i){return pair{i / (m + 1), i % (m + 1)};};

    auto nn = (n + 1) * (m + 1);
    graph g(nn);
    int it = 0;
    int start = -1;
    rep(i, 0, n) {
        rep(j, 0, m) {
            if (grid[i][j] == '.') continue;
            auto tl = idx(i, j);
            auto tr = idx(i, j + 1);
            auto bl = idx(i + 1, j);
            auto br = idx(i + 1, j + 1);
            start = bl; // arbitrary; any X corner will do
            
            // butterfly patter, diagonal edges have even ids
            g[br].PB({tl, it});
            g[tl].PB({br, it++});
            
            g[tl].PB({bl, it});
            g[bl].PB({tl, it++});
            
            g[bl].PB({tr, it});
            g[tr].PB({bl, it++});
            
            g[tr].PB({br,it});            
            g[br].PB({tr, it++});
        }
    }
    auto tour = eulertour(g, start);
    tour.pop_back(); // no need to close the loop
    cout << sz(tour) - 1 << '\n';
    for (auto i: tour) {
        auto [a, b] = inv(i);
        cout << b << " " << a << '\n';
    }
}
