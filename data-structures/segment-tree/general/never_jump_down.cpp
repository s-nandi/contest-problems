// backtrack (convert tree problem to array problem), counting # of LIS, (max, # of max) queries
// https://mausa19.kattis.com/problems/nar19.neverjumpdown
// 2019 Mid-Atlantic Regional

#include <bits/stdc++.h>
using namespace std;

constexpr auto MOD = 11092019;
constexpr auto MAXN = 1'000'000 + 1;

struct edge { int to; };
using graph = vector<vector<edge>>;

struct node {
    int mx{0}, cnt{0};

    void init(int v, int c) { mx = v, cnt = c; }
    void modify(int v, int c) { *this = this->combine({v, c}); }

    node combine(const node& o) const {
        if (mx == o.mx) 
            return {mx, (cnt + o.cnt) % MOD};
        else
            return mx < o.mx ? o : *this;
    }
};

struct segment_tree {
    int sz;
    vector<node> elements;

    segment_tree(int sz) : sz{sz}, elements(2 * sz) {}

    void modify(int p, auto update) {
        update(elements[p += sz]);
        for (p >>= 1; p >= 1; p >>= 1) {
            elements[p] = elements[p << 1].combine(elements[p << 1 | 1]);
        }
    }

    node query(int l, int r) {
        node lacc, racc;
        for (l += sz, r += sz; l <= r; ++l >>= 1, --r >>= 1) {
            if (l & 1) lacc = lacc.combine(elements[l]);
            if (!(r & 1)) racc = elements[r].combine(racc);
        }
        return lacc.combine(racc);
    }
};

auto assigner(int v, int c) {return [=](auto& n){n.init(v, c);};}
auto modifier(int v, int c) {return [=](auto& n){n.modify(v, c);};}

void dfs(const auto& g, const auto& labels, int curr, auto& st, auto& sols) {
    auto [old_len, old_ways] = st.query(labels[curr], labels[curr]);
    
    st.modify(labels[curr], modifier(1, 1)); // 'base case' (kinda)
    auto [len, ways] = sols[curr] = st.query(0, labels[curr]); // find # of LIS w/ curr as leaf
    st.modify(labels[curr], assigner(len + 1, ways)); // set longest LIS ending in labels[curr]
    for (auto [to] : g[curr])
        dfs(g, labels, to, st, sols);
    st.modify(labels[curr], assigner(old_len, old_ways)); // backtrack - restore original value
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> labels(n);
    for (auto& elem : labels) {
        cin >> elem;
    }

    graph g(n);
    for (int i = 1; i < n; i++) {
        int par;
        cin >> par;
        g[--par].push_back({i});
    }

    segment_tree st(MAXN);
    vector<node> sols(n);
    dfs(g, labels, 0, st, sols);

    auto [len, ways] = accumulate(begin(sols), end(sols), node{}, mem_fn(&node::combine));
    cout << len << " " << ways << '\n';
}
