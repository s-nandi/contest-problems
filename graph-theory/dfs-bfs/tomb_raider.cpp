// dfs (bipartite, simpler 2-sat), light and mirrors
// https://open.kattis.com/problems/tombraider
// 2020 North American Championships

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define PB push_back
using vi = vector<int>;
using ll = long long;

struct edge{int to; bool flipped;};
using graph = vector<vector<edge>>;

const auto INF = 1031231234LL;

auto dx = vector{0, -1, 0, 1};
auto dy = vector{-1, 0, 1, 0};
    
auto fwd = vector{3, 2, 1, 0};
auto bck = vector{1, 0, 3, 2};
auto rev = vector{2, 3, 0, 1};

int n, m;
bool inbounds(int i, int j){return i >= 0 and j >= 0 and i < n and j < m;}
int id(int i, int j){return i * m + j;}

bool isvert(int dir){return dir == 1 or dir == 3;}
bool gargoyle(char c){return c == 'V' or c == 'H';}

pair<int, bool> light(auto& grid, int i, int j, int dir, bool parity = false) {
    if (!inbounds(i, j)) {
        dir = rev[dir];
    } else {
        auto pos = id(i, j);
        if (gargoyle(grid[i][j])) {
            return {pos, parity};
        } else if (grid[i][j] == '#') {
            return {-1, false};
        }
        if (grid[i][j] == '\\') dir = bck[dir], parity ^= true;
        else if (grid[i][j] == '/') dir = fwd[dir], parity ^= true;
    }
    return light(grid, i + dx[dir], j + dy[dir], dir, parity);
}

pair<ll, ll> dfs(auto& g, auto& color, auto& cost, int curr, bool vert = false) {
    if (color[curr] != -1) {
        if (color[curr] != vert) return {INF, INF};
        else return {0, 0};
    }
    color[curr] = vert;
    auto acc = pair{cost[curr][!vert], cost[curr][vert]};
    for (auto [to, f]: g[curr]) {
        auto delta = dfs(g, color, cost, to, vert ^ f);
        acc.first += delta.first; acc.second += delta.second;
    }
    return acc;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;

    auto grid = vector(n, vector<char>(m));
    rep(i, 0, n) {
        rep(j, 0, m) {
            cin >> grid[i][j];
        }
    }
    auto g = graph(n * m);
    auto cost = vector(n * m, vector<ll>(2));
    rep(i, 0, n) {
        rep(j, 0, m) {
            if (!gargoyle(grid[i][j])) continue;
            auto pos = id(i, j);
            rep(v, 0, 2)
                cost[pos][v] = v ^ (grid[i][j] == 'V');
            rep(k, 0, 4) {
                auto [to, par] = light(grid, i + dx[k], j + dy[k], k);
                if (to == -1)
                    cost[pos][isvert(k)] = INF;
                else
                    g[pos].PB({to, par});
            }
        }
    }
    auto total = 0LL;
    auto color = vector(n * m, -1);
    rep(i, 0, n) {
        rep(j, 0, m) {
            if (!gargoyle(grid[i][j])) continue;
            auto pos = id(i, j);
            if (color[pos] != -1) continue;
            auto [possible1, possible2] = dfs(g, color, cost, pos);
            total += min(possible1, possible2);
        }
    }
    cout << (total < INF ? total : -1LL) << '\n';
}
