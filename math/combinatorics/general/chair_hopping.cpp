// Combinatorics, Permutation Cycles, Fast Exponentiation, Cannot self-merge even period perms
// https://open.kattis.com/problems/chairhopping
// 2020 ProgNova

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)

using ll = long long;
using vi = vector<int>;

const int MOD = 1000000007;
const int MAXN = 100000 + 5;

struct ff_int {
    static constexpr auto mod = MOD;
    ll val;
    ff_int(ll val = 0) : val(val) {}
    ff_int operator + (const ff_int& o) const {return (val + o.val) % mod;}
    ff_int operator - (const ff_int& o) const {return (val - o.val + mod) % mod;}
    ff_int operator * (const ff_int& o) const {return (val * o.val) % mod;}
    ff_int pow(auto p) const {
        ff_int acc = 1, v = *this;
        for (; p; p >>= 1)
        {
            if (p & 1) acc = acc * v;
            v = v * v;
        }
        return acc;
    }
    ff_int operator / (const ff_int& o) const {return *this * o.pow(mod - 2);}
    operator int() {return val;}
};

auto dfs(const vi& nxt, int i, vi& vis) {
    if (vis[i]) return 0;
    vis[i] = true;
    return 1 + dfs(nxt, nxt[i], vis);
}

ff_int numpairs[MAXN + 1];
ff_int factorial[MAXN + 1];
void precompute(int maxn) {
    factorial[0] = factorial[1] = 1;
    numpairs[0] = numpairs[1] = numpairs[2] = 1;
    rep(i, 2, maxn + 1) factorial[i] = ff_int{i} * factorial[i - 1];
    rep(i, 3, maxn + 1) numpairs[i] = ff_int{i - 1} * numpairs[i - 2];
}

auto choose(int n, int k) {
    return factorial[n] / (factorial[n - k] * factorial[k]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute(MAXN);

    int n;
    cin >> n;
    vi t(n + 1);
    rep(i, 1, n + 1) {
        cin >> t[i];
    }

    vi vis(n + 1);
    map<int, int> cnt;
    rep(i, 1, n + 1) {
        if (vis[i]) continue;
        auto component_sz = dfs(t, i, vis);
        cnt[component_sz]++;
    }

    ff_int sol{1};
    for (auto& [period, num]: cnt) {
        auto acc = ff_int{0};
        // p = number of paired components
        for (int paired = 0; paired <= num; paired += 2) {
            // Even period => Cannot pair with self => Need all to be paired
            if (period % 2 == 0 and paired < num) continue;
            auto choose_paired = choose(num, paired);
            auto ways_to_pair = numpairs[paired];
            auto matchings = ff_int{period}.pow(paired / 2);

            auto possible = choose_paired * ways_to_pair * matchings;
            acc = acc + possible;
        }
        sol = sol * acc;
    }
    cout << sol << '\n';
}
