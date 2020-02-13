// line sweep, ordered statistics tree, find # of interval sets with intersection length >= k
// https://open.kattis.com/problems/foodcarts
// 2018 ProgNova

#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using vi = vector<int>;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a: x)
#define all(a) begin(a),end(a)

template <typename T>
using os_tree = tree<T, null_type, less<T>, rb_tree_tag,
                                   tree_order_statistics_node_update>;

const int INF = 1'031'231'234;
const ll MOD = 1'000'000'007;
const int MAXN = 200'005;

ll pow2[MAXN + 1];
void precompute(int maxn) {
    pow2[0] = 1;
    rep(i, 1, maxn + 1) {
        pow2[i] = pow2[i - 1] * 2 % MOD;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m; ll k;
    cin >> n >> m >> k;

    precompute(m);

    vi p(n);
    trav(i, p) cin >> i;

    vi left(m);
    vector<vi> added(n + 1), removed(n + 1);
    rep(i, 0, m) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        left[i] = a;
        added[a].push_back(i);
        removed[b].push_back(i);
    }
    
    auto acc = 0LL;
    os_tree<ll> psum;
    rep(i, 0, n) {
        acc += p[i];
        psum.insert(acc);
    }
    
    auto res = 0LL;
    os_tree<pair<int, int>> ost;
    rep(pos, 0, n) {
        trav(id, added[pos]) {
            ost.insert({pos, id});
        }

        auto prefix = *psum.find_by_order(pos);
        // find max ind s.t. sum[ind:pos] >= k => psum[ind - 1] <= psum[pos] - k
        int ind = prefix >= k ? psum.order_of_key(prefix - k + 1) : -1;
        auto num_left_enough = ost.order_of_key({ind, INF}); // cancels out if ind = -1
        trav(id, removed[pos]) {
            ost.erase({left[id], id});
        }
        auto remaining_left_enough = ost.order_of_key({ind, INF});

        if (ind != -1) {
            auto delta = (pow2[num_left_enough] - pow2[remaining_left_enough + MOD) % MOD;
            res = (res + delta) % MOD;
        }
    }
    cout << res << '\n';   
}
