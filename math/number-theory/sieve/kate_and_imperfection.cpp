// sieve, greedy, idea: when adding x to set, it forces x/spf[x] to be gcd
// https://codeforces.com/contest/1333/problem/F

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;

#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back

const int MAXN = 500000;
bool cmp[MAXN + 5];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vi res;
    rep(i, 2LL, n + 1) {
        if (cmp[i]) continue;
        res.PB(1);
        for (auto j = i * i; j <= n; j += i) {
            if (!cmp[j]) res.PB(j / i);
            cmp[j] = true;
        }
    }
    sort(all(res));
    trav(i, res) cout << i << " "; cout << '\n';
}
