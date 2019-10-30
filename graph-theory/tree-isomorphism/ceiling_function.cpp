// binary tree isomorphism (left and right nodes are distinguishable), BST insertion
// https://open.kattis.com/problems/ceiling
// 2016 ICPC World Finals

#include <bits/stdc++.h>
using namespace std;

struct tree {
    int val{-1};
    tree *l{nullptr}, *r{nullptr};

    tree() = default;
    tree(int v) {
        val = v;
        l = r = NULL;
    }

    tree* insert(int v) {
        if (v < val) {
            l = l ? l->insert(v) : new tree(v);
        } else {
            r = r ? r->insert(v) : new tree(v);
        }
        return this;
    }
};

bool isomorphic(tree* a, tree* b) {
    if (!a or !b) return !a and !b;
    return isomorphic(a->l, b->l) and isomorphic(a->r, b->r);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    int sol = 0;
    vector<tree*> trees(n);
    for (int i = 0; i < n; i++) {
        trees[i] = new tree{};
        for (int j = 0; j < k; j++) {
            int val;
            cin >> val;
            trees[i]->insert(val);
        }
        sol += none_of(begin(trees), next(begin(trees), i),
                       [&trees, i](tree* t) { return isomorphic(trees[i], t); });
    }
    cout << sol << '\n';
}
