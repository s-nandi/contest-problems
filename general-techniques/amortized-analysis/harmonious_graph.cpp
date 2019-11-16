// dsu, amortized analysis (j is only merged with another element once for each j in [0..n - 1])
// https://codeforces.com/contest/1253/problem/D

#include <bits/stdc++.h>
using namespace std;

struct disjoint_set_union {
    int sz;
    vector<int> par, largest;

    disjoint_set_union(int s) : sz{s}, par(sz), largest(sz) {
        iota(begin(par), end(par), 0);
        iota(begin(largest), end(largest), 0);
    }

    int find_root(int i) { return (par[i] == i) ? i : (par[i] = find_root(par[i])); }
    void union_elements(int i, int j) {
        largest[find_root(j)] = max(largest[find_root(j)], largest[find_root(i)]);
        par[find_root(i)] = find_root(j);
    }

    auto largest_in_component(int i) { return largest[find_root(i)]; }
    bool same_component(int i, int j) { return find_root(i) == find_root(j); }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    auto dsu = disjoint_set_union(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        dsu.union_elements(a, b);
    }

    auto sol = 0;
    int upto = 0;
    for (int i = 0; i < n; i++) {
        auto largest = dsu.largest_in_component(i);
        for (int j = max(upto, i); j <= largest; j++) {
            sol += !dsu.same_component(i, j);
            dsu.union_elements(i, j);
        }
        upto = largest;
    }
    cout << sol << '\n';
}
