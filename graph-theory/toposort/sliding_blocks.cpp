// Toposort, creating dependency graph
// https://open.kattis.com/problems/slidingblocks
// 2018 Singapore Regional

#include <bits/stdc++.h>
using namespace std;

constexpr auto MAXN = 400'000 + 5;

vector dx = {0, -1, 0, 1};
vector dy = {-1, 0, 1, 0};

struct edge {
    int to;
};
using graph = vector<vector<edge>>;

struct direction {
    char ch{' '};
    int index{-1};
};

struct block {
    int r, c;

    auto neighbors(const block &o) const {
        auto dx = r - o.r;
        auto dy = c - o.c;
        return ((dx == 0) ^ (dy == 0)) and abs(dx) <= 1 and abs(dy) <= 1;
    }

    auto direction_to(const block &o) const -> direction {
        auto dx = r - o.r;
        auto dy = c - o.c;
        if (dx == -1) {
            return {'v', c};
        } else if (dx == 1) {
            return {'^', c};
        } else if (dy == -1) {
            return {'>', r};
        } else if (dy == 1) {
            return {'<', r};
        }
        assert(false);
    }

    auto operator<(const auto &o) const { return tie(r, c) < tie(o.r, o.c); }
};

enum color { white, black, grey };
auto has_cycle(graph &g, int curr, auto &colors, auto &topo) {
    if (colors[curr] != white) return colors[curr] == grey ? true : false;
    colors[curr] = grey;
    for (auto [to] : g[curr]) {
        if (has_cycle(g, to, colors, topo)) {
            return true;
        }
    }
    colors[curr] = black;
    topo.push_front(curr);
    return false;
}

auto toposort(graph &g) {
    deque<int> topo;
    vector<color> colors(g.size(), white);
    for (int i = 0; i < g.size(); i++) {
        if (has_cycle(g, i, colors, topo)) {
            return pair{false, topo};
        }
    }
    return pair{true, topo};
}

void get_constraints(const auto &g, auto &blocks, int curr, auto &constraints, auto &dirs, int prev = -1) {
    if (prev != -1) {
        dirs[curr] = blocks[curr].direction_to(blocks[prev]);
        constraints[prev].push_back({curr});
    }
    for (auto [to] : g[curr]) {
        if (to == prev) continue;
        get_constraints(g, blocks, to, constraints, dirs, curr);
    }
}

auto find_first_after(const auto &vec, const auto &elem) {
    auto it = upper_bound(begin(vec), end(vec), elem);
    return (it != end(vec)) ? optional(*it) : nullopt;
}

auto find_first_before(const auto &vec, const auto &elem) {
    auto it = lower_bound(begin(vec), end(vec), elem);
    return (it != begin(vec)) ? optional(*prev(it)) : nullopt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int r, c, b;
    cin >> r >> c >> b;

    vector<block> blocks(b);
    map<block, int> mapping;
    for (int i = 0; i < b; i++) {
        int x, y;
        cin >> x >> y;

        blocks[i] = {x, y};
        mapping[{x, y}] = i;
    }

    graph g(b);
    for (int i = 0; i < b; i++) {
        auto [x, y] = blocks[i];
        for (int k = 0; k < dx.size(); k++) {
            auto nx = x + dx[k];
            auto ny = y + dy[k];
            if (mapping.count({nx, ny})) {
                auto j = mapping[{nx, ny}];
                g[i].push_back({j});
            }
        }
    }

    vector<vector<pair<int, int>>> sorted_rows(MAXN), sorted_cols(MAXN);
    for (int i = 0; i < b; i++) {
        auto [r, c] = blocks[i];
        sorted_rows[r].push_back({c, i});
        sorted_cols[c].push_back({r, i});
    }
    for (auto &row : sorted_rows) {
        sort(begin(row), end(row));
    }
    for (auto &col : sorted_cols) {
        sort(begin(col), end(col));
    }

    vector<direction> dirs(b);
    graph constraints(b);
    get_constraints(g, blocks, 0, constraints, dirs, -1);

    for (int i = 1; i < b; i++) {
        auto [r, c] = blocks[i];
        auto [dir, ind] = dirs[i];
        optional<pair<int, int>> later_block;
        if (dir == '>') {
            later_block = find_first_before(sorted_rows[r], pair{c, i});
        } else if (dir == '<') {
            later_block = find_first_after(sorted_rows[r], pair{c, i});
        } else if (dir == 'v') {
            later_block = find_first_before(sorted_cols[c], pair{r, i});
        } else if (dir == '^') {
            later_block = find_first_after(sorted_cols[c], pair{r, i});
        }
        if (later_block) {
            auto [pos, j] = *later_block;
            if (!blocks[i].neighbors(blocks[j])) {
                constraints[i].push_back({j});
            }
        }
    }

    auto [no_cycle, ordering] = toposort(constraints);
    if (!no_cycle) {
        cout << "impossible" << '\n';
    } else {
        cout << "possible" << '\n';
        for (auto i : ordering) {
            if (i == 0) continue;
            cout << dirs[i].ch << " " << dirs[i].index << '\n';
        }
    }
}
