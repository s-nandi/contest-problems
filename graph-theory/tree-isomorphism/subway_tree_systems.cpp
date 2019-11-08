// tree isomorphism (via hashing), reconstruct tree from dfs traversal
// https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=936
// 2003 NWERC

#include <bits/stdc++.h>
using namespace std;

struct edge {
    int to;
};
using graph = vector<vector<edge>>;

int calc_size(const graph& g, vector<int>& sizes, int curr, int prev = -1) {
    sizes[curr] = 1;
    for (auto e : g[curr]) {
        if (e.to == prev) continue;
        sizes[curr] += calc_size(g, sizes, e.to, curr);
    }
    return sizes[curr];
}

void find_centroids(const graph& g, const vector<int>& sizes, int all, vector<int>& res, int curr,
                    int prev = -1) {
    auto is_centroid = true;
    for (auto e : g[curr]) {
        if (e.to == prev) continue;
        is_centroid &= sizes[e.to] <= all / 2;
        if (sizes[e.to] >= all / 2 and all - sizes[e.to] <= all / 2)
            find_centroids(g, sizes, all, res, e.to, curr);
    }
    if (is_centroid) res.push_back(curr);
}

vector<int> centroids(const graph& g) {
    vector<int> centroids, sizes(g.size());
    auto total = calc_size(g, sizes, 0);
    find_centroids(g, sizes, total, centroids, 0);
    return centroids;
}

const int alpha = 37;
const array<int, 2> MOD = {1000000007, 1000000009};

using hashT = int;
using hashesT = pair<vector<hashT>, int>;  // (double/triple hashes, max. distance from leaf)
hashesT tree_hash(const graph& g, const vector<int>& rng, int curr, int prev = -1) {
    int depth = 0;
    vector<hashesT> chs;
    for (auto e : g[curr]) {
        if (e.to == prev) continue;
        chs.push_back(tree_hash(g, rng, e.to, curr));
        depth = max(depth, 1 + chs.back().second);
    }
    assert(depth < rng.size());
    vector<hashT> hs(MOD.size(), 1);
    for (const auto& ch : chs) {
        for (int t = 0; t < MOD.size(); t++) {
            hs[t] = (long long)hs[t] * (rng[depth] + ch.first[t]) % MOD[t];
        }
    }
    return {hs, depth};
}

mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());
bool tree_isomorphic(graph& a, graph& b) {
    auto ac = centroids(a), bc = centroids(b);
    if (a.size() != b.size() or ac.size() != bc.size()) return false;

    vector<int> polynomial(a.size());
    uniform_int_distribution<int> dist(0, MOD[0] - 1);
    generate(begin(polynomial), end(polynomial), [&]() { return dist(gen); });

    auto bh = tree_hash(b, polynomial, bc[0]);
    return any_of(begin(ac), end(ac), [&](int r) { return tree_hash(a, polynomial, r) == bh; });
}

graph make_tree(const string& s) {
    int curr = 0;
    vector<int> pars(1);
    for (char c : s) {
        if (c == '0') {
            int child = pars.size();
            pars.push_back(curr);
            curr = child;
        } else {
            curr = pars[curr];
        }
    }
    graph g(pars.size());
    for (int i = 1; i < g.size(); i++) {
        auto a = i, b = pars[i];
        g[a].push_back({b});
        g[b].push_back({a});
    }
    return g;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        string s, t;
        cin >> s >> t;

        auto g1 = make_tree(s), g2 = make_tree(t);
        auto same = tree_isomorphic(g1, g2);
        if (same) {
            cout << "same" << '\n';
        } else {
            cout << "different" << '\n';
        }
    }
}
